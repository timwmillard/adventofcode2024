
with num as (
    select regexp_matches(line, 'mul\((\d+)\,(\d+)\)', 'g') as pair
    from day3.raw_input
)
select
    sum(pair[1]::int * pair[2]::int)
from num;

