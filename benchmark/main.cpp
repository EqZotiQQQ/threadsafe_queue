#include "benchmark/benchmark.h"

#include <algorithm>
#include <thread>

#include "../ThreadsafeQueue/headers/ThreadsafeQueue.h"
#include "../ThreadsafeQueue/src/ThreadsafeQueue.cpp"

template<class T>
void push_element(T& q, int n = 1) {
    for(int i = 0; i < n; i++) {
        q.push(rand() % 10000);
    }
}

void thread_safe_queue(benchmark::State& state) {
    ThreadsafeQueue<int> queue;
    int n = state.range(0);
    while (state.KeepRunning()) {
        push_element(queue, n);
    }
}

void default_queue(benchmark::State& state) {
    std::queue<int> queue;
    int n = state.range(0);
    while (state.KeepRunning()) {
        push_element(queue, n);
    }
}

//  kNanosecond, kMicrosecond, kMillisecond, kSecond
BENCHMARK(thread_safe_queue)->Arg(5000)->Unit(benchmark::kNanosecond);
BENCHMARK(default_queue)->Arg(5000)->Unit(benchmark::kNanosecond);

// -----------------------------------------------------------------
// Benchmark                       Time             CPU   Iterations
// -----------------------------------------------------------------
// thread_safe_queue/5000    1055046 ns      1054706 ns          668
// default_queue/5000         168885 ns       168861 ns         4212

//simple queue works 6.2x faster cuz of lock_guard shared_ptrs

BENCHMARK_MAIN();