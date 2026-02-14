-- creating table
CREATE TABLE weblogs (
    log_id INT,
    ip_address STRING,
    url STRING,
    status_code INT,
    response_time STRING,
    log_date STRING
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
TBLPROPERTIES ("skip.header.line.count"="1");

-- loading data from hdfs
LOAD DATA INPATH '/user/230968078/week6/weblogs.csv' INTO TABLE weblogs;

-- most visited urls
SELECT url, COUNT(*) as visit_count
FROM weblogs
GROUP BY url
ORDER BY visit_count DESC;

-- peak traffic hours
SELECT log_date, COUNT(*) as daily_hits
FROM weblogs
GROUP BY log_date
ORDER BY daily_hits DESC;

-- find 404 erros
SELECT * FROM weblogs 
WHERE status_code = 404;

-- create partitioned hive table
CREATE TABLE weblogs_partitioned (
    log_id INT,
    ip_address STRING,
    url STRING,
    status_code INT,
    response_time STRING
)
PARTITIONED BY (log_date STRING);

-- insert data
SET hive.exec.dynamic.partition = true;
SET hive.exec.dynamic.partition.mode = nonstrict;

INSERT INTO TABLE weblogs_partitioned PARTITION(log_date)
SELECT log_id, ip_address, url, status_code, response_time, log_date 
FROM weblogs;

-- created bucketed table 
CREATE TABLE weblogs_bucketed (
    log_id INT,
    ip_address STRING,
    url STRING,
    status_code INT,
    response_time STRING,
    log_date STRING
)
CLUSTERED BY (status_code) INTO 4 BUCKETS;

-- retrieve 404 errors
INSERT OVERWRITE TABLE weblogs_bucketed 
SELECT * FROM weblogs;

SELECT * FROM weblogs_bucketed 
WHERE status_code = 404;