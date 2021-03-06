
#include "tm.h"

#include <chrono>
#include <ctime>

namespace Tm {

static std::time_t startTime = now();

std::time_t start() {
  return startTime;
}

std::time_t now() {
   return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); 
}

std::time_t wallclock() {
  return now() - start();
}

}; // Tm
