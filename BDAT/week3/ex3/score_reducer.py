#!usr/bin/env python3 
import sys 

N = 3 
global_top = []

for line in sys.stdin:
    line = line.strip() 
    try:
        key, data = line.split('\t', 1)
        score, name = data.split(',')
        score = int(score)
        global_top.append((score, name))
        global_top.sort(reverse=True)
        global_top = global_top[:N]
    except ValueError:
        continue 

for score, name in global_top:
    print(f'{name}\t{score}')