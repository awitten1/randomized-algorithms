#pragma once

#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <stdexcept>
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>


class PerfEvents {
public:

    explicit PerfEvents();

    int64_t poll() {
      int64_t count;
      read(fd_, &count, sizeof(count));
      return count;
    }

    ~PerfEvents() {
      close(fd_);
    }
private:
    int fd_;

};

