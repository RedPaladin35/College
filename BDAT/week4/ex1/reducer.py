#!/usr/bin/env python3 
import sys 

current_course = None 
students = []
courses = []

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue 

    course_id, value = line.split('\t', 1)

    if current_course and current_course != course_id:
        if students and courses:
            for s in students:
                for c in courses:
                    print(f'{s},{c}')
        students = []
        courses = []
    current_course = course_id

    if value.startswith('STU:'):
        students.append(value[4:])
    elif value.startswith('CRS:'):
        courses.append(value[4:])

if current_course and students and courses:
    for s in students:
        for c in courses:
            print(f'{s},{c}')