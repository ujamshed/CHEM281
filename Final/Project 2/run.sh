#!/bin/bash
g++ Chem281P2.cpp -o p2 -fopenmp

./Chem281P2 --tiled --row_tile 128 --col_tile 128 --inner_tile 128 --threads 1
./Chem281P2 --tiled --row_tile 128 --col_tile 128 --inner_tile 128 --threads 2
./Chem281P2 --tiled --row_tile 128 --col_tile 128 --inner_tile 128 --threads 4
./Chem281P2 --tiled --row_tile 128 --col_tile 128 --inner_tile 128 --threads 6
./Chem281P2 --tiled --row_tile 128 --col_tile 128 --inner_tile 128 --threads 8
