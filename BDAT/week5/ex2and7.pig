sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

high_value = FILTER sales by amount > 5000;
DUMP high_value;

STORE high_value INTO '/user/230968078/week5/result2' USING PigStorage(',');