
with query as (
    select 
        report,
        lag(value) over (partition by report),
        value,
        lead(value) over (partition by report)
    from day2.input
    order by report
), next as (
    select 
        report,
        abs(lag - value) as diff,
        lag, value, lead,
        lag - value < 0 as inc,
        lag - value > 0 as dec,
        lag - value = 0 as equal
    from query
), total as (
    select
        report,
        count(distinct inc) = 1 as inc,
        count(distinct dec) = 1 as dec,
        count(equal) filter (where equal) < 1 as equal,
        count(diff) filter (where diff > 3) < 1 as diff
    from next
    group by report
)
select
    count(report)
from total
where inc and dec and equal and diff

