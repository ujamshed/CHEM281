# These timing measurements were done on matrix sizes 512 x 512 on my local computer which has 4 physical cores, due to issues with Perlmutter.
# See Chem281P2.cpp for the complete code

# 1) The code scales decently with more threads, with 8x as many threads yielding a difference of 2.4x. These results are using the fastest configuration where we parallelize the first loop, and no other loops inside even though we could parallelize the last loop as well (no issues with data dependencies), but doing so took longer.

| Threads     | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 1           | 422795        | -             |
| 2           | 301607        | 1.4x          |
| 4           | 219494        | 1.9x          |
| 6           | 182153        | 2.3x          |
| 8           | 176281        | 2.4x          |

# 2) The tiling code also scales decently well with more threads, with 8x as many threads yielding a difference of 2.4x. These results are the base configuration where the tiling is equal to the size of the matrices (512 for each parameter).

| Threads     | Time          | Difference    |
| ----------- |  -----------  | ------------- |
| 1           | 447611        | -             |
| 2           | 293610        | 1.5x          |
| 4           | 219341        | 2.0x          |
| 6           | 195747        | 2.3x          |
| 8           | 185957        | 2.4x          |

# When comparing which tile sizes yield the best benefit, the size equivalent to the size of the matrix dimensions was the best. All results were done on one thread. However, past a tile size of 128, the difference become less pronounced.

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


# 3) 

# 4)