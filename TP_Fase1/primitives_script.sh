#!/bin/bash
cd build
./generator cone 1 2 4 3 cone_1_2_4_3.3d
./generator cone 2 4 10 9 cone_2_4_10_9.3d
./generator sphere 1 10 10 sphere_1_10_10.3d
./generator box 2 3 box_2_3.3d
./generator box 3 8 box_3_8.3d
./generator plane 2 3 plane_2_3.3d