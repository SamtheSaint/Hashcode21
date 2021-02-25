#!/bin/bash

g++ main.cpp -o a.out

cat inputs/a.txt | ./a.out > outputs/a.txt
cat inputs/b.txt | ./a.out > outputs/b.txt
cat inputs/c.txt | ./a.out > outputs/c.txt
cat inputs/d.txt | ./a.out > outputs/d.txt
cat inputs/e.txt | ./a.out > outputs/e.txt
cat inputs/f.txt | ./a.out > outputs/f.txt