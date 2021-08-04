<pre>
----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------

thread_safe_queue/5000    1055046 ns      1054706 ns          668

default_queue/5000         168885 ns       168861 ns         4212
</pre>

simple queue works 6.2x faster cuz of lock_guard shared_ptrs. But default stl queue isn't thread safe.
