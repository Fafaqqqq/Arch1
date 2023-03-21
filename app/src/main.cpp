#include "logger.h"
#include "sorter.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>


int main()
{
  sorter sorter;
  auto logger = lab1::logger::get_instance();

  std::vector<int> vec = {1, 4, 2, 1, 6, 19, 20, 11, 13, 48, 19, 81, 48,
                          1, 4, 2, 1, 6, 19, 20, 11, 13, 48, 19, 81, 48,
                          1, 4, 2, 1, 6, 19, 20, 11, 13, 48, 19, 81, 48};

  auto sort_instance = sorter.async_sort(vec, [](void* args) {
    std::vector<int>& sorted = *(std::vector<int>*)args;

    for (auto& item : sorted) {
      std::cout << item << " ";
    }

    std::cout << std::endl;
  }, (void*)&vec);
  
  int count = 100;
  while (count--) {
    logger->log("main", "iteration " + std::to_string(100 - count));
  }

  return 0;
}
