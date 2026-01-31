#!/usr/bin/env python3 
import os 
import sys 

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue 
    parts = line.split(',')

    filepath = os.environ.get('mapreduce_map_input_file','')

    if 'students' in filepath.lower():
        if len(parts) == 3:
            student_id, name, course_id = parts 
            print(f'{course_id}\tSTU:{student_id},{name}')
    elif 'courses'  in filepath.lower():
        if len(parts) == 3:
            course_id, course_name, sem = parts 
            print(f'{course_id}\tCRS:{course_name},{sem}')