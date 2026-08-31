#pragma once

#include <3ds.h>

#include <mutex>
#include <renderd7/core/noncopyable.hpp>

namespace RenderD7 {
class Mutex : public NonCopyable {
 public:
  Mutex() { LightLock_Init(&pLock); }

  void lock() { LightLock_Lock(&pLock); }
  void unlock() { LightLock_Unlock(&pLock); }
  bool try_lock() { return !LightLock_TryLock(&pLock); }

 private:
  LightLock pLock;
};
}  // namespace RenderD7