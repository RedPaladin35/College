from pyspark import SparkContext, SparkConf
import re

def main():
    conf = SparkConf().setAppName('LogAnalyzer')
    sc = SparkContext(conf=conf)

    # Using the triple slash URI
    input_path = 'hdfs://localhost:9000/user/230968078/week8/ex1/server_logs.txt'
    output_base_path = 'hdfs://localhost:9000/user/230968078/week8/ex1/output/'

    logs_rdd = sc.textFile(input_path)
    log_pattern = re.compile(r'^(\S+) .* ".*" (\d{3}) \d+')

    def parse_logs(line):
        match = log_pattern.match(line)
        if match:
            return (match.group(1), match.group(2))
        return None 
    
    parsed_logs = logs_rdd.map(parse_logs).filter(lambda x: x is not None).cache()

    status_counts = parsed_logs.map(lambda x: (x[1], 1)).reduceByKey(lambda a, b: a + b)
    ip_counts = parsed_logs.map(lambda x: (x[0], 1)).reduceByKey(lambda a, b: a + b).sortBy(lambda x: x[1], ascending=False)

    error_logs = parsed_logs.filter(lambda x: x[1].startswith(('4', '5')))
    total_error_count = error_logs.count()
    error_count_rdd = sc.parallelize([f'Total Error Logs (4xx/5xx): {total_error_count}'])

    status_counts.saveAsTextFile(output_base_path + 'status_counts')
    ip_counts.saveAsTextFile(output_base_path + 'ip_counts')
    error_count_rdd.saveAsTextFile(output_base_path + 'error_total')

    print('Processing complete. Results saved to HDFS.')
    sc.stop()

if __name__ == '__main__':
    main()
