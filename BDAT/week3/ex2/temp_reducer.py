#!usr/bin/env python3 
import sys 

current_year = None 
max_temp = -float('inf')

for line in sys.stdin:
    line = line.strip() 
    try:
        year, temp = line.split('\t', 1)
        temp = float(temp)
    except ValueError:
        continue 

    if current_year == year:
        if temp > max_temp:
            max_temp = temp 
    else:
        if current_year:
            print(f'{current_year}\t{max_temp}')
        current_year = year 
        max_temp = temp 

if current_year:
    print(f'{current_year}\t{max_temp}')