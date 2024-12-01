with left_col as (
    select 
        row_number() over (order by left_value) as row_id,
        left_value
    from day1.input
), right_col as (
    select right_value, count(right_value)
    from day1.input
    group by right_value
)
select sum(l.left_value * coalesce(r.count, 0))
from left_col l
left join right_col r on l.left_value = r.right_value

