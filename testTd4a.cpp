#include "PosixThread.hpp"
#include <iostream>

int main (int argc, char *argv[])
{
  std::cout << "posixThread1" << std::endl;
  PosixThread posixThread1();
  
  // std::cout << "posixId" << std::endl;
  // pthread_t posixId;
  // std::cout << "posixThread2" << std::endl;
  // PosixThread posixThread2(posixId);
  
  // try
  // {
  //   std::cout << "posixId" << std::endl;
  //   pthread_t posixId;
  //   std::cout << "posixThread2" << std::endl;
  //   PosixThread posixThread2(posixId);
  //   std::cout << "after posixThread2" << std::endl;
  // }
  // catch(PosixThread::Exception &err)
  // {
  //   std::cout << "what" << std::endl;
  //   // std::cerr << "ERROR :" << err.what() << std::endl;
  //   return 1;
  // }
  
  
  // std::cout << "posixThread3" << std::endl;
  // PosixThread posixThread3(10);


  
  return 0;
}