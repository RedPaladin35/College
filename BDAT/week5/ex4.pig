sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

grouped_cat = GROUP sales by category;
total_per_cat = FOREACH grouped_cat GENERATE group AS category, SUM(sales.amount) as total_amount;
DUMP total_per_cat;

STORE total_per_cat INTO '/user/230968078/week5/result4' USING PigStorage(',');