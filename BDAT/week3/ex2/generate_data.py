import csv 
import random 

years = [2020, 2021, 2022, 2023, 2024, 2025]

with open('weather.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    for _ in range(100):
        year = random.choice(years)
        temp = random.randint(-10, 45)
        writer.writerow([year, temp])
        