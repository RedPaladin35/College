from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg, count 
from pyspark.ml.feature import StringIndexer, VectorAssembler, OneHotEncoder
from pyspark.ml import Pipeline
from pyspark.ml.classification import RandomForestClassifier
from pyspark.ml.regression import LinearRegression
from pyspark.ml.evaluation import MulticlassClassificationEvaluator, RegressionEvaluator
import matplotlib.pyplot as plt

spark = SparkSession.builder.appName('EmployeeRetentionAnalysis').getOrCreate()

df = spark.read.csv('hdfs://localhost:9000/user/230968078/week10/ex1/employee_attrition.csv', header=True, inferSchema=True)

cat_cols = ['Gender', 'Department', 'JobRole', 'Education', 'OverTime', 'MaritalStatus']
num_cols = ['Age', 'ExperienceYears', 'JobSatisfaction', 'WorkLifeBalance', 'PerformanceRating', 'NumProjects', 'DistanceFromHome']

indexers = [StringIndexer(inputCol=col, outputCol=f'{col}_idx') for col in cat_cols]
encoders = [OneHotEncoder(inputCol=f'{col}_idx', outputCol=f'{col}_vec') for col in cat_cols]

attrition_indexer = StringIndexer(inputCol='Attrition', outputCol='label_attrition')

assembler = VectorAssembler(
    inputCols=[f'{col}_vec' for col in cat_cols] + num_cols,
    outputCol='features'
)

prep_pipeline = Pipeline(stages=indexers + encoders + [attrition_indexer, assembler])
processed_df = prep_pipeline.fit(df).transform(df)

df.select('Age', 'ExperienceYears', 'MonthlyIncome', 'DistanceFromHome').describe().show()

df.groupBy('Attrition').agg(
    avg('MonthlyIncome').alias('Avg_Income'),
    avg('JobSatisfaction').alias('Avg_Satisfaction'),
    count('EmployeeID').alias('Employee_Count')
).show() 

df.groupBy('Department', 'Attrition').count().orderBy('Department').show()

train_df, test_df = processed_df.randomSplit([0.8, 0.2], seed=42)

rf = RandomForestClassifier(featuresCol='features', labelCol='label_attrition', numTrees=100)
rf_model = rf.fit(train_df)

class_predictions = rf_model.transform(test_df)

evaluator = MulticlassClassificationEvaluator(labelCol='label_attrition', metricName='accuracy')
accuracy = evaluator.evaluate(class_predictions)
print('=============================================')
print(f'Attrition Prediction Accurary: {accuracy:.2f}')
print('=============================================')

lr = LinearRegression(featuresCol='features', labelCol='MonthlyIncome')
lr_model = lr.fit(train_df)

reg_predictions = lr_model.transform(test_df)

reg_evaluator = RegressionEvaluator(labelCol='MonthlyIncome', metricName='r2')
r2 = reg_evaluator.evaluate(reg_predictions)
print('=============================================')
print(f'Salary prediction R2 Score: {r2:.2f}')
print('=============================================')

attrition_counts = df.groupBy('Attrition').count().toPandas()
attrition_counts.plot(kind='bar', x='Attrition', y='count', color=['skyblue', 'salmon'])
plt.title('Employee Attrition Disbtribution')
plt.show()

