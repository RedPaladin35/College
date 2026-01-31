#!/usr/bin/env python3
import sys 
import os 
import re 

filepath = os.environ.get('mapreduce_map_input_file', 'unknown')
doc_id = os.path.basename(filepath).split('.')[0]

for line in sys.stdin:
    line = line.strip().lower()
    words = re.findall(r'\w+', line)

    for word in words:
        if word:
            print(f'{word.capitalize()}\t{doc_id}')