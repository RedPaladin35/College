#!/bin/bash 

JAR_PATH="/usr/local/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.4.1.jar"

INPUT_PATH="/user/230968078/week3/input1.txt"
OUTPUT_PATH="/user/230968078/week3/result1"

hdfs dfs -put -f input1.txt /user/230968078/week3/

echo "Starting hadoop job..."
hadoop jar $JAR_PATH \
    -file mapper.py -mapper "python3 mapper.py" \
    -file reducer.py -reducer "python3 reducer.py" \
    -input $INPUT_PATH \
    -output $OUTPUT_PATH

echo "Job complete. Results:" 
hdfs dfs -cat $OUTPUT_PATH/part*
