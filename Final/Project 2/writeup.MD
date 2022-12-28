# See Chem281P2.cpp for the complete code

# Experiments were done locally originally due to perlmutter issues and then re-tested on perlmutter once they were resolved.

# 1) Local experiments using 512 x 512 matrices. The code scales decently with more threads, with 8x as many threads yielding a difference of 2.4x. These results are using the fastest configuration where we parallelize the first loop, and no other loops inside even though we could parallelize the last loop as well (no issues with data dependencies), but doing so took longer.

| Threads     | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 1           | 422795        | -             |
| 2           | 301607        | 1.4x          |
| 4           | 219494        | 1.9x          |
| 6           | 182153        | 2.3x          |
| 8           | 176281        | 2.4x          |

# 1) On perlmutter using 4096 x 4096 matrices.

| Threads     | Time          |
| ----------- |  -----------  |
| 1           | 17889047      |
| 2           | 16265612      |
| 4           | 20375219      |
| 6           | 31458831      |
| 8           | 28976094      |

# 2) On Perlmutter using 4096 x 4096 matrices, with tile size of 128. As the number of threads increases, the duration of time taken for the code to run drops from 15 seconds to 2.5 seconds, which is a significant improvement. This code scales much better than the looped implementation because the difference with different number of threads is greater.

| Threads     | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 1           | 15556699      | -             |
| 2           | 9075611       | 1.7x          |
| 4           | 4697657       | 3.3x          |
| 6           | 2932261       | 5.3x          |
| 8           | 2461152       | 6.3x          |

# Comparing different tile sizes on perlmutter with 4096 x 4096 matrices with 8 threads.

| Tile size   | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 2           | 36880087      | -             |
| 4           | 25465816      | 1.4x          |
| 8           | 6385368       | 5.8x          |
| 16          | 4246257       | 8.7x          |
| 32          | 3296934       | 11.2x         |
| 64          | 3124640       | 11.8x         |
| 128         | 2512080       | 14.7x         |
| 256         | 2209295       | 16.7x         |
| 512         | 1831821       | 20.1x         |
| 1024        | 3272274       | 11.3x         |
| 2048        | 10683198      | 3.4x          |

# The best tile size is 512. As tile size increasesfrom 2 to 512 time decreases as shown by the difference. However, past 512 tile size the time increases.

# 3) Ran on Perlmutter using 4096 x 4096 matrices.

```console
jamshedu@nid004679:~> ./Chem281P2 --blas --threads 1
runMode set to blas
number of threads set to 1
number of threads=1
Time blas 2716553
```

# 4) Performance Analysis

## For --loop with 4 threads
```console
jamshedu@nid004679:~> srun -n 1 perf stat ./Chem281P2 --loop --threads 4
runMode set to loop
number of threads set to 4
number of threads=4
Time loop 23580336

 Performance counter stats for './Chem281P2 --loop --threads 4':

         88,750.36 msec task-clock:u              #    3.617 CPUs utilized
                 0      context-switches:u        #    0.000 /sec
                 0      cpu-migrations:u          #    0.000 /sec
             2,747      page-faults:u             #   30.952 /sec
   310,817,016,197      cycles:u                  #    3.502 GHz                      (83.33%)
       702,903,902      stalled-cycles-frontend:u #    0.23% frontend cycles idle     (83.34%)
        27,066,313      stalled-cycles-backend:u  #    0.01% backend cycles idle      (83.34%)
   110,640,104,500      instructions:u            #    0.36  insn per cycle
                                                  #    0.01  stalled cycles per insn  (83.34%)
    18,928,374,822      branches:u                #  213.277 M/sec                    (83.33%)
        43,819,686      branch-misses:u           #    0.23% of all branches          (83.33%)

      24.537800653 seconds time elapsed

      88.722069000 seconds user
       0.027993000 seconds sys
```

## For --tiled with 4 threads and optimal tiling size of 512
```console
jamshedu@nid004676:~> srun -n 1 perf stat ./Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4
runMode set to tiled
runMode TILED, row_tile set to 512
runMode TILED, col_tile set to 512
runMode TILED, inner_tile set to 512
number of threads set to 4
number of threads=4
Time slice 3599011

 Performance counter stats for './Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4':

         14,299.46 msec task-clock:u              #    3.124 CPUs utilized
                 0      context-switches:u        #    0.000 /sec
                 0      cpu-migrations:u          #    0.000 /sec
             2,755      page-faults:u             #  192.665 /sec
    49,786,922,799      cycles:u                  #    3.482 GHz                      (83.32%)
       167,853,048      stalled-cycles-frontend:u #    0.34% frontend cycles idle     (83.36%)
        12,544,208      stalled-cycles-backend:u  #    0.03% backend cycles idle      (83.36%)
   114,158,525,307      instructions:u            #    2.29  insn per cycle
                                                  #    0.00  stalled cycles per insn  (83.33%)
    19,530,774,362      branches:u                #    1.366 G/sec                    (83.33%)
       161,395,124      branch-misses:u           #    0.83% of all branches          (83.32%)

       4.577342843 seconds time elapsed

      14.257712000 seconds user
       0.043968000 seconds sys
```

## For --blas
```console
jamshedu@nid004679:~> srun -n 1 perf stat ./Chem281P2 --blas
runMode set to blas
number of threads=256
Time blas 2721708

 Performance counter stats for './Chem281P2 --blas':

          8,371.54 msec task-clock:u              #    2.245 CPUs utilized
                 0      context-switches:u        #    0.000 /sec
                 0      cpu-migrations:u          #    0.000 /sec
             3,970      page-faults:u             #  474.226 /sec
    26,416,748,572      cycles:u                  #    3.156 GHz                      (84.28%)
       144,500,248      stalled-cycles-frontend:u #    0.55% frontend cycles idle     (81.71%)
        22,599,720      stalled-cycles-backend:u  #    0.09% backend cycles idle      (80.60%)
    41,672,808,768      instructions:u            #    1.58  insn per cycle
                                                  #    0.00  stalled cycles per insn  (81.33%)
     2,412,998,814      branches:u                #  288.238 M/sec                    (85.64%)
        25,779,135      branch-misses:u           #    1.07% of all branches          (87.73%)

       3.728916788 seconds time elapsed

       8.031241000 seconds user
       0.074020000 seconds sys
```

# Performing cache misses examination

## Best loop
```console
jamshedu@nid004431:~> srun -n 1 perf stat -e L1-dcache-load-misses,dTLB-load-misses,l2_pf_hit_l2,l2_pf_miss_l2_hit_l3 ./Chem281P2 --loop --threads 4
runMode set to loop
number of threads set to 4
number of threads=4
Time loop 16130991

 Performance counter stats for './Chem281P2 --loop --threads 4':

    17,391,437,485      L1-dcache-load-misses:u
            18,847      dTLB-load-misses:u
    15,916,972,095      l2_pf_hit_l2:u
     1,706,488,857      l2_pf_miss_l2_hit_l3:u

      17.108746064 seconds time elapsed

      61.806121000 seconds user
       0.039991000 seconds sys
```

## Best tile
```console
jamshedu@nid004431:~> srun -n 1 perf stat -e L1-dcache-load-misses,dTLB-load-misses,l2_pf_hit_l2,l2_pf_miss_l2_hit_l3 ./Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4
runMode set to tiled
runMode TILED, row_tile set to 512
runMode TILED, col_tile set to 512
runMode TILED, inner_tile set to 512
number of threads set to 4
number of threads=4
Time slice 3391913

 Performance counter stats for './Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4':

     9,543,251,267      L1-dcache-load-misses:u
            17,433      dTLB-load-misses:u
     3,388,007,186      l2_pf_hit_l2:u
     9,612,889,715      l2_pf_miss_l2_hit_l3:u

       4.501977406 seconds time elapsed

      12.764877000 seconds user
       0.175901000 seconds sys
```

## Blas
```console
jamshedu@nid004431:~> srun -n 1 perf stat -e L1-dcache-load-misses,dTLB-load-misses,l2_pf_hit_l2,l2_pf_miss_l2_hit_l3 ./Chem281P2 --blas
runMode set to blas
number of threads=256
Time blas 2718682

 Performance counter stats for './Chem281P2 --blas':

     1,203,277,069      L1-dcache-load-misses:u
           334,824      dTLB-load-misses:u
     1,331,616,998      l2_pf_hit_l2:u
       326,356,463      l2_pf_miss_l2_hit_l3:u

       3.718707812 seconds time elapsed

       7.970108000 seconds user
       0.069590000 seconds sys
```

## Cache misses summary

| Criteria                 | Loop           | Tiled         | Blas         |
| ------------------------ |  -----------   | ------------- | ------------ |
| L1-dcache-load-misses:u  | 17,391,437,485 | 9,543,251,267 | 1,203,277,069|
| dTLB-load-misses:u       | 18,847         | 17,433        | 334,824      |
| l2_pf_hit_l2:u           | 15,916,972,095 | 3,388,007,186 | 1,331,616,998|
| l2_pf_miss_l2_hit_l3:u   | 1,706,488,857  | 9,612,889,715 | 326,356,463  |

## Examining the cache misses we see that the loop implementation has the highest l1 cache misses and the highest l2 prefetch and hit in l2. This explains why it takes the longest time because for every piece of data it is missing in the l1 cache it must check the l2 cache to retrieve it, if it is there. These misses add a ton of time to the program. In the tiled implementation our cache misses are fewer which saves us time but most of our hits if we miss the l1 cache are in the l3 cache and not in the l2 cache which takes more time to access but since we have less misses overall we are still seeing improvement. For Blas we see the fewest l1 cache misses but greater TLB misses.