import csv
import random

def generate_datasets(records=1000):
    categories = ['Electronics', 'Furniture', 'Home Decor', 'Clothing', 'Books']
    products = {
        'Electronics': ['Laptop', 'Phone', 'Monitor', 'Headphones', 'Tablet'],
        'Furniture': ['Chair', 'Desk', 'Shelf', 'Sofa', 'Table'],
        'Home Decor': ['Lamp', 'Rug', 'Vase', 'Mirror', 'Clock'],
        'Clothing': ['Jacket', 'Shirt', 'Jeans', 'Shoes', 'Hat'],
        'Books': ['Novel', 'Textbook', 'Journal', 'Comic', 'Atlas']
    }
    cities = ['Manipal', 'Bangalore', 'Mumbai', 'Delhi', 'Chennai', 'Hyderabad']
    names = ['Arjun', 'Aditi', 'Rohan', 'Sanya', 'Vikram', 'Ananya', 'Rahul', 'Priya']

    with open('sales.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        for i in range(1, records + 1):
            category = random.choice(categories)
            product = random.choice(products[category])
            amount = random.randint(500, 100000)
            writer.writerow([1000 + i, product, category, amount])

    with open('customers.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        for i in range(1, records + 1):
            name = random.choice(names)
            city = random.choice(cities)
            writer.writerow([1000 + i, name, city])

    print(f"Successfully generated {records} records in sales.csv and customers.csv")

if __name__ == "__main__":
    generate_datasets(1000) 