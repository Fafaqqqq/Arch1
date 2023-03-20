#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
#include <memory>
#include <fstream>
#include <string>

namespace lab1
{
  class logger
  {
    public:
      static logger* get_instance();
      void log(const std::string& msg);

    private:
      logger();
      logger(const logger& other) = delete;
      logger(logger&& other) = delete;
      logger& operator=(const logger& other) = delete;
      logger& operator=(logger&& other) = delete;

      
      std::mutex mtx_;

      const char*   log_file_name_{"log.txt"};
      std::ofstream log_file_;
      std::chrono::system_clock::time_point start;
  };
}

#endif