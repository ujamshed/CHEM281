# 1) The overhead incurred by parallelization is the difference between the time taken to run the program sequentially and the time taken for the program to run on one thread. From 1_thread.txt this is 5850-2636 = 3214 microsecs.

# 2) As more threads are added the time taken decreases until after 8 threads where the time taken to complete the program starts to increase again. The table below shows the time taken for each run serially and parallelly. After 8 threads, increasing the number of threads does not yield any further benefit because we do not have enough computing power to have more than 8 threads running in parallel. As such there will be threads waiting for others to finish before they can start, and so the idle time for certain threads increases and since we have barriers in place to wait for all threads to finish their tasks, this increases the time taken for the program. This shows that this algorithm is compute bound.

| Threads     | Serial      | Parallel      |
| ----------- | ----------- | ------------- |
| 1           | 2636        | 5850          |
| 2           | 2387        | 2798          |
| 4           | 2445        | 1745          |
| 6           | 2380        | 1489          |
| 8           | 2386        | 1254          |
| 10          | 2401        | 2043          |
| 12          | 2594        | 2134          |

# 3) Algorithm is compute bound as explained above.