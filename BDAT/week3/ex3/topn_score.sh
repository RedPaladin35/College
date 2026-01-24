#!/bin/bash 

JAR_PATH="/usr/local/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.4.1.jar"

INPUT_PATH="/user/230968078/week3/scores.csv"
OUTPUT_PATH="/user/230968078/week3/result3"

hdfs dfs -put -f scores.csv /user/230968078/week3/

echo "Starting hadoop job..."
hadoop jar $JAR_PATH \
    -file score_mapper.py -mapper "python3 score_mapper.py" \
    -file score_reducer.py -reducer "python3 score_reducer.py" \
    -input $INPUT_PATH \
    -output $OUTPUT_PATH

echo "Job complete. Results:" 
hdfs dfs -cat $OUTPUT_PATH/part*