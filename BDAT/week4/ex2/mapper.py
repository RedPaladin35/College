#!/usr/bin/env python3 
import sys 
import re 

STOP_WORDS = {'to', 'the', 'by', 'with', 'from', 'like', 'in', 'of', 'and'}

for line in sys.stdin:
    line = line.strip().lower()
    words = re.findall(r'\w+', line)
    
    for word in words:
        if word not in STOP_WORDS:
            print(f'{word.capitalize()}\t1')