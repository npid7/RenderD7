#pragma once
#include <3ds.h>

#include <atomic>
#include <functional>
#include <renderd7/parameter.hpp>

using CTRU_Thread = Thread;

constexpr static uint64_t THREAD_STACK_SIZE = 4 * 1024;

namespace RenderD7 {
class Thread {
 public:
  Thread();
  Thread(std::function<void(RenderD7::Parameter)> f,
         RenderD7::Parameter arg = nullptr, bool autostart = false,
         bool detached = false, uint64_t stack_szs = THREAD_STACK_SIZE);
  virtual ~Thread();
  void Init(std::function<void(RenderD7::Parameter)> f,
            RenderD7::Parameter arg = nullptr, bool autostart = false,
            bool detached = false, uint64_t stack_szs = THREAD_STACK_SIZE);
  void SetStackSize(uint64_t stack_szs);
  void Start(bool detached = false);
  void Kill();
  void Join(long long unsigned int timeout = U64_MAX);
  bool IsRunning();
  static void Sleep();
  static void Sleep(int millis);

 private:
  struct ThreadData {
    RenderD7::Parameter Arg;
    std::function<void(RenderD7::Parameter)> Self;
    std::atomic<bool>* Running;
  };

  static void ThreadFunc(void* data);
  int m_prio = 0, m_stack_size = 0;
  bool m_started = false;
  std::atomic<bool> m_running = false;
  RenderD7::Thread::ThreadData m_data;
  CTRU_Thread m_thread;
};
}  // namespace RenderD7
