#!/bin/bash
notangle -R2d-transform.c 2d-transform.nw > 2d-transform.c
noweave -delay 2d-transform.nw > 2d-transform.tex
pdflatex 2d-transform.tex 
./compile.sh
