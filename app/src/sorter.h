#ifndef SORTER_H
#define SORTER_H

#include "logger.h"

#include <string>
#include <thread>
#include <vector>
#include <functional>

class sorter {
  public:
    class sorter_instance {
      public:
        friend class sorter;

        void await() {
          if (worker_.joinable()) {
            worker_.join();
          }
        }

        ~sorter_instance() {
          if (worker_.joinable()) {
            worker_.join();
          }
        }
      
      private:
        sorter_instance(std::thread&& catch_thr) : worker_(std::move(catch_thr)) {}

        sorter_instance() = delete;
        sorter_instance(const sorter_instance& other) = delete;
        sorter& operator=(const sorter_instance& other) = delete;

        std::thread worker_;
    };

    sorter() : logger_(lab1::logger::get_instance()) {
      logger_->log("sorter", "init success");
    }

    template<typename Type>
    sorter_instance async_sort(std::vector<Type>& sequence, std::function<void(void*)> callback, void* args) {
      return sorter_instance(std::move(std::thread(&sorter::heap_sort<Type>, this, std::ref(sequence), callback, args)));
    }

  private:
    template<typename Type>
    void heap_sort(std::vector<Type>& sequence, std::function<void(void*)> callback, void* args)
    {
      int n = sequence.size();

      logger_->log("sorter", "fist heapify");
      for (int i = n / 2 - 1; i >= 0; i--)
        heapify(sequence, n, i);

      for (int i=n-1; i>=0; i--)
      {
        logger_->log("sorter", "swap 0 <==>" + std::to_string(i));
        std::swap(sequence[0], sequence[i]);
        
        heapify(sequence, i, 0);
      }

      logger_->log("sorter", "done");

      callback(args);
    }

    template<typename Type>
    void heapify(std::vector<Type>& sequence, int n, int i)
    {
      int largest = i;
      int l = 2*i + 1;
      int r = 2*i + 2;

      if (l < n && sequence[l] > sequence[largest])
        largest = l;

      if (r < n && sequence[r] > sequence[largest])
        largest = r;

      if (largest != i)
      {
        std::swap(sequence[i], sequence[largest]);

        heapify(sequence, n, largest);
      }
    }

    lab1::logger* logger_ = nullptr;
};

#endif // !SORTER_H