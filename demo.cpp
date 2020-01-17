// demo.cpp
#include <iostream>
#include "permutation.h"

int main()
{

  uint p1_array[] = {6, 2, 1, 5, 4, 3};
  Permutation p1 = Permutation(p1_array, 6);
  std::cout << "This is an example of a permutation (call it p1): " << std::endl; 
  std::cout << p1.to_string();
  std::cout << "This is the cycle decomposition of p1: ";
  std::cout << p1.decomposition() << std::endl;
  std::cout << "This is the inverse of p1: " << std::endl;
  std::cout << p1.inverse().to_string();
  std::cout << "This is the order of p1: ";
  std::cout << p1.order() << std::endl;

  std::string p2_cycle = "(1 5)(2 3)";
  Permutation p2 = Permutation(p2_cycle, 6);
  std::cout << "This is an example of a permutation (call it p2): ";
  std::cout << p2.to_string();
  std::cout << "This is the cycle decomposition of p2: ";
  std::cout << p2.decomposition() << std::endl;
  std::cout << "This is the inverse of p2: " << std::endl;
  std::cout << p2.inverse().to_string();
  std::cout << "This is the order of p2: ";
  std::cout << p2.order() << std::endl;

  std::cout << "This is p1 * p2: " << std::endl;
  std::cout << (p1 * p2).to_string();
  std::cout << "This is p2 * p1: " << std::endl;
  std::cout << (p2 * p1).to_string();
}
