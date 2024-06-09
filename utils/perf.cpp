
#include "perf.h"

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

    uint64_t event_id;

    pid_t pid = 0;
    int cpu = -1;
    int group_fd = -1; // i don't know what this does right now.

    fd_ = syscall(SYS_perf_event_open, &attr,
                pid, cpu, group_fd, 0);

    if (fd_ < 0) {
        throw std::runtime_error{"perf_event_open returned an error"};
    }

    // reset the counter.
    ioctl(fd_, PERF_EVENT_IOC_RESET, 0);

    // enable the counter.
    ioctl(fd_, PERF_EVENT_IOC_ENABLE, 0);
}