#!usr/bin/env python3 
import sys 

for line in sys.stdin:
    line = line.strip() 
    if not line:
        continue 
    try:
        year, temp = line.split(',')
        print(f'{year}\t{temp}')
    except ValueError:
        continue 
    