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

# 2) Local experiments using 512 x 512 matrices. The tiling code also scales decently well with more threads, with 8x as many threads yielding a difference of 2.4x. These results are the base configuration where the tiling is equal to the size of the matrices (512 for each parameter).

| Threads     | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 1           | 447611        | -             |
| 2           | 293610        | 1.5x          |
| 4           | 219341        | 2.0x          |
| 6           | 195747        | 2.3x          |
| 8           | 185957        | 2.4x          |

# 2) On Perlmutter using 4096 x 4096 matrices.

| Threads     | Time          |
| ----------- |  -----------  |
| 1           | 17712725      |
| 2           | 16558543      |
| 4           | 21508879      |
| 6           | 30168110      |
| 8           | 28977283      |

# Locally comparing tile sizes (512 x 512). When comparing which tile sizes yield the best benefit, the size equivalent to the size of the matrix dimensions was the best. All results were done on one thread. However, past a tile size of 128, the difference become less pronounced.

| Tile size   | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 2           | 7805458       | -             |
| 4           | 1496202       | 5.2x          |
| 8           | 654304        | 11.9x         |
| 16          | 502953        | 15.5x         |
| 32          | 485872        | 16.1x         |
| 64          | 469540        | 16.6x         |
| 128         | 468883        | 16.6x         |
| 256         | 462785        | 16.9x         |
| 512         | 451060        | 17.3x         |


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

## For --tiled with 4 threads and tiling size of 4096
```console
jamshedu@nid004679:~> srun -n 1 perf stat ./Chem281P2 --tiled --threads 4
runMode set to tiled
number of threads set to 4
number of threads=4
Time slice 23451826

 Performance counter stats for './Chem281P2 --tiled --threads 4':

         87,976.13 msec task-clock:u              #    3.600 CPUs utilized
                 0      context-switches:u        #    0.000 /sec
                 0      cpu-migrations:u          #    0.000 /sec
             2,757      page-faults:u             #   31.338 /sec
   306,824,291,167      cycles:u                  #    3.488 GHz                      (83.34%)
       713,539,403      stalled-cycles-frontend:u #    0.23% frontend cycles idle     (83.33%)
        12,322,179      stalled-cycles-backend:u  #    0.00% backend cycles idle      (83.34%)
   110,611,402,813      instructions:u            #    0.36  insn per cycle
                                                  #    0.01  stalled cycles per insn  (83.34%)
    18,934,885,091      branches:u                #  215.228 M/sec                    (83.33%)
        43,750,006      branch-misses:u           #    0.23% of all branches          (83.33%)

      24.435614356 seconds time elapsed

      87.916141000 seconds user
       0.055984000 seconds sys
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