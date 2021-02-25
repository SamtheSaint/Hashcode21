#!/bin/bash

g++ main.cpp -o a.out

cat inputs/a.txt | ./a.out > outputs/a.txt 2> debug/a.txt
cat inputs/b.txt | ./a.out > outputs/b.txt 2> debug/b.txt
cat inputs/c.txt | ./a.out > outputs/c.txt 2> debug/c.txt
cat inputs/d.txt | ./a.out > outputs/d.txt 2> debug/d.txt
cat inputs/e.txt | ./a.out > outputs/e.txt 2> debug/e.txt
cat inputs/f.txt | ./a.out > outputs/f.txt 2> debug/f.txt