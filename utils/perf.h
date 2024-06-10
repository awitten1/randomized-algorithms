#pragma once

#include <condition_variable>
#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <stdexcept>
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>
#include <thread>


class PerfEvents {
public:

    explicit PerfEvents();

    void start();
    void shutdown();

    int64_t poll() {
      int64_t count;
      (void)read(fd_, &count, sizeof(count));
      return count;
    }

    ~PerfEvents() {
      close(fd_);
      shutdown();
      t_.join();
    }
private:
    int fd_;

    std::condition_variable cv_;
    std::mutex m_;
    bool shutdown_ = false;
    std::thread t_;
};

