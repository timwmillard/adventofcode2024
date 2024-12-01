with right_col as (
    select right_value, count(right_value)
    from day1.input
    group by right_value
)
select sum(input.left_value * coalesce(r.count, 0))
from day1.input
left join right_col r on input.left_value = r.right_value

