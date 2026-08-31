#pragma once

namespace RenderD7 {
class NonCopyable {
 public:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

}  // namespace RenderD7