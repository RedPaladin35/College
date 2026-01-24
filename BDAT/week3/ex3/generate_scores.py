import csv 
import random 

students = ["Arjun", "Neha", "Rahul", "Priya", "Amit", "Sonal", "Karan", "Anjali", "Vijay", "Deepa"]

with open('scores.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    for _ in range(50):
        name = random.choice(students)
        score = random.randint(50, 100)
        writer.writerow([name, score])
    