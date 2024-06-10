
#include "perf.h"
#include <chrono>
#include <mutex>
#include <iostream>
#include <sstream>

using namespace std::literals;

void PerfEvents::start() {
  t_ = std::thread([this]() {
    for(;;) {
      std::unique_lock<std::mutex> lk(m_);
      cv_.wait_for(lk, 1s, [this]() {
        return shutdown_;
      });
      if (shutdown_) {
        break;
      }
      int64_t cycles = poll();
      std::cout << cycles << std::endl;
    }
  });

}

void PerfEvents::shutdown() {
  std::lock_guard<std::mutex> lk(m_);
  shutdown_ = true;
  cv_.notify_one();
}

PerfEvents::PerfEvents() {
    // pid = 0 => current process, cpu == -1 => any cpu
    // https://man7.org/linux/man-pages/man2/perf_event_open.2.html
    struct perf_event_attr attr;
    memset(&attr, 0, sizeof(struct perf_event_attr));
    attr.type = PERF_TYPE_HARDWARE;
    attr.size = sizeof(struct perf_event_attr);

    // studying user space code.
    attr.exclude_kernel = 1;
    attr.exclude_hv = 1;

    // counter is initially disabled.  enabled later is fcntl or prctl.
    attr.disabled = 1;
    attr.config = PERF_COUNT_HW_CPU_CYCLES;

    // for now disable this
    // attr.read_format = PERF_FORMAT_GROUP;

    pid_t pid = 0;
    int cpu = -1;
    int group_fd = -1; // i don't know what this does right now.

    fd_ = syscall(SYS_perf_event_open, &attr,
                pid, cpu, group_fd, 0);

    if (fd_ < 0) {
        std::stringstream ss;
        ss << "perf_event_open returned an error: " << strerror(errno);
        throw std::runtime_error{ss.str()};
    }

    // reset the counter.
    ioctl(fd_, PERF_EVENT_IOC_RESET, 0);

    // enable the counter.
    ioctl(fd_, PERF_EVENT_IOC_ENABLE, 0);
}
