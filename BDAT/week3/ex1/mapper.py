#!usr/bin/env python3 
import sys 

for line in sys.stdin:
    line = line.rstrip('\n')
    for char in line:
        if char == " ":
            char = "SPACE"
        elif char == "\t":
            char = "TAB"
        print(f'{char}\t1')