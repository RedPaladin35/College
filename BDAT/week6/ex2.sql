-- create table 

CREATE TABLE movie_ratings (
    movie_id INT,
    title STRING,
    genre STRING,
    release_year INT,
    user_id INT,
    rating DOUBLE,
    review_timestamp TIMESTAMP
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ','
TBLPROPERTIES ("skip.header.line.count"="1");

-- load data
LOAD DATA INPATH '/user/230968078/week6/movie_ratings.csv' INTO TABLE movie_ratings;

-- top 5 highest rated movies
SELECT title, AVG(rating) as avg_rating
FROM movie_ratings
GROUP BY title
ORDER BY avg_rating DESC
LIMIT 5;

-- find the most popular genre
SELECT genre, COUNT(*) as review_count
FROM movie_ratings
GROUP BY genre
ORDER BY review_count DESC
LIMIT 1;

-- extract yearly trends
SELECT YEAR(review_timestamp) as review_year, COUNT(*) as total_reviews
FROM movie_ratings
GROUP BY YEAR(review_timestamp);

-- create a partitioned table by genre
CREATE TABLE movie_partitioned (
    movie_id INT,
    title STRING,
    release_year INT,
    user_id INT,
    rating DOUBLE,
    review_timestamp TIMESTAMP
)
PARTITIONED BY (genre STRING);

-- insert and retrieve data
SET hive.exec.dynamic.partition = true;
SET hive.exec.dynamic.partition.mode = nonstrict;

INSERT INTO TABLE movie_partitioned PARTITION(genre)
SELECT movie_id, title, release_year, user_id, rating, review_timestamp, genre 
FROM movie_ratings;

SELECT * FROM movie_partitioned WHERE genre = 'Sci-Fi';

-- create bucketed table
CREATE TABLE movie_bucketed (
    movie_id INT,
    title STRING,
    genre STRING,
    release_year INT, 
    user_id INT,
    rating DOUBLE,
    review_timestamp TIMESTAMP
)
CLUSTERED BY (release_year) INTO 4 BUCKETS;

-- inserting data
-- Forcing Hive to respect bucketing during insert
SET hive.enforce.bucketing = true; 

INSERT OVERWRITE TABLE movie_bucketed 
SELECT movie_id, title, genre, release_year, user_id, rating, review_timestamp 
FROM movie_ratings;

SELECT * FROM movie_bucketed WHERE release_year = 2019;