#include <thread>
#include <iostream>
#include <mutex>

class OddEvenMonitor {
public:
  static const bool ODD_TURN = true;
  static const bool EVEN_TURN = false;

  OddEvenMonitor(): turn(ODD_TURN) {}

  void WaitTurn(bool old_turn) {
    std::unique_lock<std::mutex> lock(mx);
    while(turn != old_turn) {
      cond.wait(lock);
    }
  }

  void ToggleTurn() {
    std::lock_guard<std::mutex> lock(mx);
    turn = !turn;
    cond.notify_one();
  }

private:
  bool turn;
  std::condition_variable cond;
  std::mutex mx;
};

void OddThread(OddEvenMonitor & monitor) {
  for(int i = 1; i <= 100; i += 2) {
    monitor.WaitTurn(OddEvenMonitor::ODD_TURN);
    std::cout << i << std::endl;
    monitor.ToggleTurn();
  }
}

void EvenThread(OddEvenMonitor & monitor) {
  for(int i = 2; i <= 100; i += 2) {
    monitor.WaitTurn(OddEvenMonitor::EVEN_TURN);
    std::cout << i << std::endl;
    monitor.ToggleTurn();
  }
}

int main() {
  OddEvenMonitor monitor;
  std::thread t1(OddThread, std::ref(monitor));
  std::thread t2(EvenThread, std::ref(monitor));

  t1.join();
  t2.join();
}

#ifdef WRONG_ATTEMPT
std::mutex increment_mutex;
std::mutex print_mutex;

void print_numbers(int tid, int & count) {
  while(true) {
    increment_mutex.lock();
    count++;
    if(count > 100) {
      increment_mutex.unlock();
      break;
    }
    print_mutex.lock();
    increment_mutex.unlock();
    std::cout<< "Thread " << tid << " count " << count << std::endl;
    print_mutex.unlock();
  }
}

int main(int argc, char * argv[]) {
  int count = 0;
  std::thread t1(print_numbers, 1, std::ref(count));
  std::thread t2(print_numbers, 2, std::ref(count));

  t1.join();
  t2.join();
}
#endif