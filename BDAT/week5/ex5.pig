customers = LOAD '/user/230968078/week5/customers.csv' USING PigStorage(',') AS (order_id:int, name:chararray, city:chararray);
sales = LOAD '/user/230968078/week5/sales.csv' USING PigStorage(',') AS (order_id:int, product:chararray, category:chararray, amount:int);

joined_data = JOIN sales BY order_id, customers BY order_id;
DUMP joined_data;

STORE joined_data INTO '/user/230968078/week5/result5' USING PigStorage(',');