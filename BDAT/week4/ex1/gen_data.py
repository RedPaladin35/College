import csv

students = [
    ['101', 'Alice', 'C01'],
    ['102', 'Bob', 'C02'],
    ['103', 'Charlie', 'C01'],
    ['104', 'David', 'C03'],
]

courses = [
    ['C01', 'Computer Science', 'Sem1'],
    ['C02', 'Mathematics', 'Sem3'],
    ['C04', 'Physics', 'Sem2'], 
]

with open('students.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(students)

with open('courses.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(courses)