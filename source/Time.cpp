#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <format>
#include <memory>
#include <renderd7/Time.hpp>
#include <string>

std::string RenderD7::GetTimeStr(void) {
  time_t unixTime;
  struct tm timeStruct;
  time(&unixTime);
  localtime_r(&unixTime, &timeStruct);
  return std::format("{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}",
                     timeStruct.tm_year + 1900, timeStruct.tm_mon + 1,
                     timeStruct.tm_mday, timeStruct.tm_hour, timeStruct.tm_min,
                     timeStruct.tm_sec);
}
