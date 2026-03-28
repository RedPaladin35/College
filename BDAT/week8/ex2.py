from pyspark.sql import SparkSession 
from pyspark.sql.functions import col 

def main():
    spark = SparkSession.builder.appName('JSONDataProcessor').getOrCreate()

    input_path = 'hdfs://localhost:9000/user/230968078/week8/ex2/users.json'
    output_path = 'hdfs://localhost:9000/user/230968078/week8/ex2/output'

    df = spark.read.option('multiline', 'true').json(input_path)

    print('==========Original Data=============')
    df.show()

    print('====Selected fields -> (Name, City)====')
    df.select('name', 'city').show()

    print('====Users olders than 30====')
    filtered_df = df.filter(col('age')>30)
    filtered_df.show()

    print('====Group by city====')
    grouped_df = df.groupBy('city').count()
    grouped_df.show()

    filtered_df.write.mode('overwrite').json(output_path)
    spark.stop()

if __name__ == '__main__':
    main()