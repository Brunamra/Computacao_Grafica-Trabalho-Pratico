#!/bin/bash
cd build
option="$1"
case ${option} in
    "phase_1")
        # Phase 1
        ./generator cone 1 2 4 3 cone_1_2_4_3.3d
        ./generator cone 2 4 10 9 cone_2_4_10_9.3d
        ./generator sphere 1 10 10 sphere_1_10_10.3d
        ./generator box 2 3 box_2_3.3d
        ./generator box 3 8 box_3_8.3d
        ./generator plane 2 3 plane_2_3.3d
    ;;
    "phase_2")
        # Phase 2
        ./generator box 2 3 box_2_3.3d
        ./generator cone 1 2 4 3 cone_1_2_4_3.3d
        ./generator sphere 1 8 8 sphere_1_8_8.3d
        ./generator sphere 1 20 20 planet.3d
        ./generator ring 6.5 8 20 ring.3d
    ;;
    "phase_3")
        # Phase 3
        ./generator sphere 1 20 20 planet.3d
        ./generator ring 6.5 8 20 ring.3d
        ./generator patch ../tests_phase_3/teapot.patch 10 bezier_10.3d
    ;;
    "phase_4")
        # Phase 3
        ./generator box 2 3 box_2_3.3d
        ./generator plane 2 3 plane_2_3.3d
        ./generator cone 1 2 4 3 cone_1_2_4_3.3d
        ./generator sphere 1 8 8 sphere_1_8_8.3d
        ./generator patch ../tests_phase_4/teapot.patch 10 bezier_10.3d
        ./generator ring 6.5 8 100 ring.3d
        ./generator sphere 1 20 20 planet.3d
        ./generator sphere 2 100 100 sphere_2_100_100.3d
    ;;
    "clean")
        rm *.3d
    ;;
esac