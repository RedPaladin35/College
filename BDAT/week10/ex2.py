from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, count 
from pyspark.ml.feature import StringIndexer, VectorAssembler, OneHotEncoder
from pyspark.ml import Pipeline
from pyspark.ml.classification import RandomForestClassifier
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
import matplotlib.pyplot as plt

spark = SparkSession.builder.appName('EmployeePromotionPrediction').getOrCreate()

path = 'hdfs://localhost:9000/user/230968078/week10/ex2/employee_promotion.csv'
df = spark.read.csv(path, header=True, inferSchema=True)

df = df.withColumnRenamed("KPIs_met >80%", "KPIs_met_80") \
       .withColumnRenamed("awards_won?", "awards_won")

df = df.fillna({'previous_year_rating': 0, 'education': 'Unknown'})

print("--- Data Summary Statistics ---")
df.select('no_of_trainings', 'age', 'previous_year_rating', 'length_of_service', 'avg_training_score').describe().show()

print("--- Promotion Metrics by Rating and Tenure ---")
df.groupBy('is_promoted').agg(
    avg('previous_year_rating').alias('Avg_PreviousYearRating'),
    avg('length_of_service').alias('Avg_LengthOfService'),
    count('employee_id').alias('Employee_Count')
).show() 

print("--- Promotion count by Department ---")
df.groupBy('department', 'is_promoted').count().orderBy('department').show()

print("--- Promotion count by Education ---")
df.groupBy('education', 'is_promoted').count().orderBy('education').show()

cat_cols = ['department', 'region', 'education', 'gender', 'recruitment_channel']
num_cols = ['no_of_trainings', 'age', 'previous_year_rating', 'length_of_service', 'KPIs_met_80', 'awards_won', 'avg_training_score']

indexers = [StringIndexer(inputCol=c, outputCol=f'{c}_idx', handleInvalid="keep") for c in cat_cols]
encoders = [OneHotEncoder(inputCol=f'{c}_idx', outputCol=f'{c}_vec') for c in cat_cols]

assembler = VectorAssembler(
    inputCols=[f'{c}_vec' for c in cat_cols] + num_cols,
    outputCol='features'
)

prep_pipeline = Pipeline(stages=indexers + encoders + [assembler])
pipeline_model = prep_pipeline.fit(df)
processed_df = pipeline_model.transform(df)

train_df, test_df = processed_df.randomSplit([0.8, 0.2], seed=42)

rf = RandomForestClassifier(featuresCol='features', labelCol='is_promoted', numTrees=100)
rf_model = rf.fit(train_df)

predictions = rf_model.transform(test_df)

evaluator = MulticlassClassificationEvaluator(labelCol='is_promoted', metricName='accuracy')
accuracy = evaluator.evaluate(predictions)

print('=============================================')
print(f'Promotion Prediction Accuracy: {accuracy:.2%}')
print('=============================================')

promotion_counts = df.groupBy('is_promoted').count().toPandas()
promotion_counts['is_promoted'] = promotion_counts['is_promoted'].map({0: 'Not Promoted', 1: 'Promoted'})

promotion_counts.plot(kind='bar', x='is_promoted', y='count', color=['salmon', 'skyblue'], legend=False)
plt.title('Employee Promotion Distribution')
plt.ylabel('Number of Employees')
plt.xlabel('Status')
plt.xticks(rotation=0)
plt.show()