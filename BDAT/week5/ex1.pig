sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

first_10 = LIMIT sales 10;
DUMP first_10;

STORE first_10 INTO '/user/230968078/week5/result1' USING PigStorage(',');