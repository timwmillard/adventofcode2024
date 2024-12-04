
with num as (
    select regexp_matches(line, 'mul\((\d+)\,(\d+)\)|(don\''t\(\))|(do\(\))', 'g') as pair
    from day3.raw_input
)
select
    pair[1]::int,
    pair[2]::int,
    pair[3],
    pair[4],
    pair[3] is null,
    pair[4] is not null

from num;

