#include "logger.h"
#include <iomanip>
#include <thread>

namespace lab1
{
  logger::logger()
  : log_file_(log_file_name_)
  {
    start = std::chrono::system_clock::now();
    log_file_ << std::fixed << std::setprecision(9) << std::left;
  }

  void logger::log(const std::string& id, const std::string& msg)
  {
    std::lock_guard<std::mutex> lock(mtx_);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> now = end - start;

    log_file_ << now.count() << " | " << id << " | " << msg << std::endl;
  }

  logger* logger::get_instance()
  {
    static logger instance_;

    return &instance_;
  }
}