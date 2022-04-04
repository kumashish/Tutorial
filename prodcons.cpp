#include <thread>
#include <iostream>
#include <deque>
#include <mutex>
#include <condition_variable>

using namespace std;

struct Buffer
{
    void add(int num) {
        while(true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this](){ return dqi.size() < size; });
            dqi.push_back(num);
            cv.notify_all();
        }
    }
    void remove() {
        while(true) {
           unique_lock<mutex> lock(m);
           cv.wait(lock, [this](){ return dqi.size() > size; });
           int i = dqi.front();
           dqi.pop_front();
           cout<<"removed "<<i<<endl;
           cv.notify_all();
        }
    }
    deque<int> dqi;
    const int size = 10;
    mutex m;
    condition_variable cv;
};

class Producer {
    Producer(Buffer &b) : pb(b) {}
    void run() {
        for(int i= 0; i < 10;++i) { 
            pb.add(i);
            cout<<"Added "<<i<<endl;
        }
    }
    Buffer& pb;
};
class Consumer {
    Consumer(Buffer &b) : pb(b) {}
    void run() {
        pb.remove();
        }
    }
    Buffer& pb;
};
int
main ()
{
  Buffer b;
  Producer p (b);
  Consumer c (&b);

  thread prod_thd(Producer::run (), &p);
  thread cons_thd(Consumer::run(), &c);
  prod_thd.join();
  cons_thd.join();
  
  getchar();
  return 0;
}
