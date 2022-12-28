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
jamshedu@nid004431:~> perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./Chem281P2 --loop --threads 4
runMode set to loop
number of threads set to 4
number of threads=4
Time loop 30356071

 Performance counter stats for './Chem281P2 --loop --threads 4':

    28,135,372,927      cache-references:u
       386,881,492      cache-misses:u            #    1.375 % of all cache refs
   349,677,341,803      cycles:u
   110,678,755,082      instructions:u            #    0.32  insn per cycle
    18,928,354,924      branches:u
             2,758      faults:u
                 0      migrations:u

      31.465745249 seconds time elapsed

     100.000627000 seconds user
       0.187963000 seconds sys
```

## Best tile
```console
jamshedu@nid004431:~> perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4
runMode set to tiled
runMode TILED, row_tile set to 512
runMode TILED, col_tile set to 512
runMode TILED, inner_tile set to 512
number of threads set to 4
number of threads=4
Time slice 3668195

 Performance counter stats for './Chem281P2 --tiled --row_tile 512 --col_tile 512 --inner_tile 512 --threads 4':

    21,364,040,605      cache-references:u
     3,215,530,374      cache-misses:u            #   15.051 % of all cache refs
    46,986,727,341      cycles:u
   114,150,802,838      instructions:u            #    2.43  insn per cycle
    19,514,080,029      branches:u
             2,747      faults:u
                 0      migrations:u

       4.619709977 seconds time elapsed

      13.477414000 seconds user
       0.044004000 seconds sys
```

## Blas
```console
jamshedu@nid004431:~> perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./Chem281P2 --blas --threads 4
runMode set to blas
number of threads set to 4
number of threads=4
Time blas 2716706

 Performance counter stats for './Chem281P2 --blas --threads 4':

     2,005,755,760      cache-references:u
       271,147,924      cache-misses:u            #   13.518 % of all cache refs
    12,782,620,015      cycles:u
    39,337,255,501      instructions:u            #    3.08  insn per cycle
     2,053,857,774      branches:u
             2,989      faults:u
                 0      migrations:u

       3.665232067 seconds time elapsed

       3.639149000 seconds user
       0.043893000 seconds sys
```