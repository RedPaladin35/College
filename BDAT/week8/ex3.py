from pyspark.sql import SparkSession 
from pyspark.sql.functions import col, sum as _sum, desc 

def main():
    spark = SparkSession.builder.appName('SalesDataProcessor').getOrCreate()

    input_path = 'hdfs://localhost:9000/user/230968078/week8/ex3/sales_data.csv'
    output_path = 'hdfs://localhost:9000/user/230968078/week8/ex3/output'

    df = spark.read.csv(input_path, header=True, inferSchema=True)

    df_with_revenue = df.withColumn('Revenue', col('Price') * col('Quantity'))

    highest_selling = df_with_revenue.orderBy(col('Revenue').desc()).first()

    high_value_sales = df_with_revenue.filter(col('Revenue')>500)
    
    category_revenue = df_with_revenue.groupBy('Category').agg(_sum('Revenue').alias('TotalCategoryRevenue'))

    print("--- Data with Revenue Column ---")
    df_with_revenue.show()

    print(f"--- Highest Selling Product: {highest_selling['Product']} (Revenue: {highest_selling['Revenue']}) ---")

    print("--- Transactions Above $500 ---")
    high_value_sales.show()

    print("--- Revenue per Category ---")
    category_revenue.show()

    category_revenue.write.mode('overwrite').option('header', 'true').csv(output_path)
    spark.stop()

if __name__ == '__main__':
    main()


