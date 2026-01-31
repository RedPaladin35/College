#!/bin/bash 

JAR_PATH="/usr/local/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.4.1.jar"

INPUT_STUDENTS="/user/230968078/week4/ex1/students.csv"
INPUT_COURSES="/user/230968078/week4/ex1/courses.csv"
OUTPUT_PATH="/user/230968078/week4/result1"

hdfs dfs -put -f students.csv /user/230968078/week4/ex1
hdfs dfs -put -f courses.csv /user/230968078/week4/ex1

echo "Starting hadoop job..."
hadoop jar $JAR_PATH \
    -file mapper.py -mapper "python3 mapper.py" \
    -file reducer.py -reducer "python3 reducer.py" \
    -input $INPUT_STUDENTS \
    -input $INPUT_COURSES \
    -output $OUTPUT_PATH

echo "Job complete. Results:" 
hdfs dfs -cat $OUTPUT_PATH/part*