#!/bin/bash
gcc -o 2d-transform `pkg-config --cflags --libs cairo` -lm 2d-transform.c
