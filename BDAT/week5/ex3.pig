sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

sorted_sales = ORDER sales by amount DESC;
DUMP sorted_sales;

STORE sorted_sales INTO '/user/230968078/week5/result3' USING PigStorage(',');