#include <renderd7/thread.hpp>
namespace RenderD7 {
Thread::Thread() : m_started(false), m_running(false) { /* do nothing */ }

Thread::Thread(std::function<void(RenderD7::Parameter)> t_function,
               RenderD7::Parameter t_parameter, bool t_autostart,
               bool t_detached, unsigned long long int t_stackSize)
    : m_started(false), m_running(false) {
  Init(t_function, t_parameter, t_autostart, t_detached, t_stackSize);
}

Thread::~Thread() {
  Join();

  if (m_started) threadFree(m_thread);
}

void Thread::Init(std::function<void(RenderD7::Parameter)> t_function,
                  RenderD7::Parameter t_parameter, bool t_autostart,
                  bool t_detached, unsigned long long int t_stackSize) {
  m_stack_size = t_stackSize;
  m_data.Arg = t_parameter;
  m_data.Self = t_function;
  m_data.Running = &m_running;

  if (t_autostart) {
    Start(t_detached);
  }
}

void Thread::SetStackSize(unsigned long long int t_stackSize) {
  m_stack_size = t_stackSize;
}

void Thread::Start(bool t_detached) {
  if (!m_running) {
    m_started = true;
    m_running = true;
    s32 prio;
    svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
    m_thread = threadCreate(ThreadFunc, &m_data, m_stack_size, prio + 1, -2,
                            t_detached);
  }
}

void Thread::Kill() {
  threadDetach(m_thread);
  m_running = false;
  m_started = false;
}

void Thread::Join(long long unsigned int t_timeout) {
  if (m_running) {
    threadJoin(m_thread, t_timeout);
    threadFree(m_thread);
    m_running = false;
    m_started = false;
  }
}

bool Thread::IsRunning() { return m_running; }

void Thread::Sleep() { svcSleepThread(0); }

void Thread::Sleep(int t_milliseconds) {
  svcSleepThread(1000000 * t_milliseconds);
}

// private methods
void Thread::ThreadFunc(void* data) {
  auto d = static_cast<RenderD7::Thread::ThreadData*>(data);
  d->Self(d->Arg);
  *d->Running = false;
}
}  // namespace RenderD7
