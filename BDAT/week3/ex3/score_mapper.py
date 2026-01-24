#!usr/bin/env python3 
import sys 

N = 3 
local_top = []

for line in sys.stdin:
    line = line.strip() 
    try:
        name, score = line.split(',')
        score = int(score)
        local_top.append((score,name))

        local_top.sort(reverse=True)
        local_top = local_top[:N]
    except ValueError:
        continue 

for score, name in local_top:
    print(f'TOP\t{score},{name}')