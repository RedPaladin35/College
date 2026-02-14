-- create table
CREATE TABLE flight_data (
    flight_id STRING,
    airline STRING,
    flight_number STRING,
    origin STRING,
    destination STRING,
    departure_date STRING,
    departure_time STRING,
    arrival_time STRING,
    delay_minutes INT,
    status STRING
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
STORED AS TEXTFILE
TBLPROPERTIES ("skip.header.line.count"="1");

-- load data
LOAD DATA INPATH '/user/230968078/week6/flight_data.csv' OVERWRITE INTO TABLE flight_data;

-- airline with the most delays
SELECT airline, COUNT(*) as delay_count
FROM flight_data
WHERE status = 'Delayed'
GROUP BY airline
ORDER BY delay_count DESC
LIMIT 1;

-- show flight count by status
SELECT status, COUNT(*) as flight_count
FROM flight_data
GROUP BY status;

-- average delay per airline 
SELECT airline, AVG(delay_minutes) as avg_delay
FROM flight_data
GROUP BY airline;

-- create partitioned table
CREATE TABLE flights_partitioned (
    flight_id STRING,
    airline STRING,
    flight_number STRING,
    origin STRING,
    destination STRING,
    departure_time STRING,
    arrival_time STRING,
    delay_minutes INT,
    status STRING
)
PARTITIONED BY (departure_date STRING)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ',';

-- load data into paritioned table
INSERT INTO TABLE flights_partitioned PARTITION(departure_date)
SELECT 
    flight_id, 
    airline, 
    flight_number, 
    origin, 
    destination, 
    departure_time, 
    arrival_time, 
    delay_minutes, 
    status, 
    departure_date 
FROM flight_data;

-- created bucketed table
CREATE TABLE flights_bucketed (
    flight_id STRING,
    airline STRING,
    flight_number STRING,
    origin STRING,
    destination STRING,
    departure_date STRING,
    departure_time STRING,
    arrival_time STRING,
    delay_minutes INT,
    status STRING
)
CLUSTERED BY (airline) INTO 3 BUCKETS
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ',';

-- insert and retrieve from bucketed table
INSERT OVERWRITE TABLE flights_bucketed 
SELECT * FROM flight_data;

SELECT * FROM flights_bucketed WHERE airline = 'Delta';