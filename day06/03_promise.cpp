// promiseFuture.cpp

#include <future>
#include <iostream>
#include <thread>
#include <utility>

void product(std::promise<int>&& intPromise, int a, int b) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  intPromise.set_value(a*b);
}

struct Div{

  void operator() (std::promise<int>&& intPromise, int a, int b) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    intPromise.set_value(a/b);
  }

};

int main() {
  std::cout << std::endl << std::endl << " START " <<  " Promise !!! " << std::endl;
  std::cout << "------------------------------------------------------- " << std::endl;

  int a = 20;
  int b = 10;

  std::cout << std::endl;

  // define the promises
  std::promise<int> prodPromise;
  std::promise<int> divPromise;

  // get the futures
  std::future<int> prodResult = prodPromise.get_future();
  std::future<int> divResult = divPromise.get_future();

  // calculate the result in a separate thread
  std::thread prodThread(product, std::move(prodPromise), a, b);
  Div div;
  std::thread divThread(div, std::move(divPromise), a, b);

  // get the result
  std::cout << "20*10 = " << prodResult.get() << std::endl;
  std::cout << "20/10 = " << divResult.get() << std::endl;

  prodThread.join();
  
  divThread.join();

  std::cout << "------------------------------------------------------- " << std::endl << std::endl ; 
  std::cout << "------------------------------------------------------- " << std::endl << std::endl ;
  return 0;
}
