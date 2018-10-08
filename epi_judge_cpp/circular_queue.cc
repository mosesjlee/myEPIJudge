#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <memory>
class Queue {
  int * array;
  size_t size;
  size_t my_capacity;
  int head;
  int tail;
public:
  Queue(size_t capacity) {
    my_capacity = capacity;
    array = new int[my_capacity];
    size = 0;
    head = 0;
    tail = 0;
  }

  ~Queue() {
    delete [] array;
  }

  void Enqueue(int x) {
    // TODO - you fill in here.
    //The resizing
    if(size == my_capacity) {
      int * temp = new int [my_capacity*2];

      //Need to reset the positions of the elements
      int tracker = head; 
      for(int i = 0; i < size; i++) {
        temp[i] = array[tracker];
        tracker = (tracker + 1) % my_capacity;
      }
      delete [] array;
      array = temp;
      my_capacity *= 2;

      //Reset head and tail
      head = 0; tail = size;
    }
    array[tail] = x;
    tail = ((tail + 1) % my_capacity);
    ++size;
  }

  int Dequeue() {
    // TODO - you fill in here.
    int retval = array[head];
    head = (head + 1) % my_capacity;
    --size;
    return retval;
  }
  int Size() const {
    // TODO - you fill in here.
    return size;
  }
};
struct QueueOp {
  enum { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = kConstruct;
    } else if (op_string == "dequeue") {
      op = kDequeue;
    } else if (op_string == "enqueue") {
      op = kEnqueue;
    } else if (op_string == "size") {
      op = kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case kEnqueue:
        q.Enqueue(argument);
        break;
      case kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
