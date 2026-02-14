sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

sorted_sales = ORDER sales by amount DESC;
top_3_exp = LIMIT sorted_sales 3;
DUMP top_3_exp;

STORE top_3_exp INTO '/user/230968078/week5/result6' USING PigStorage(',');