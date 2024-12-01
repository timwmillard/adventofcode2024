with left_col as (
    select 
        row_number() over (order by left_value) as row_id,
        left_value
    from day1.input
), right_col as (
    select 
        row_number() over (order by right_value) as row_id,
        right_value
    from day1.input
)
select sum(abs(left_value - right_value))
from left_col
join right_col using (row_id);

