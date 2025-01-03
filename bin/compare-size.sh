#!/bin/sh

set -u

before=$1 ; shift
after=$1 ; shift
format=markdown

sqlite3 ':memory:' \
  ".mode tabs" \
  ".import ${before} b" \
  ".import ${after} a" \
  ".mode ${format}" \
  "select b.name as name, format('%,d', b.size) as before, format('%,d', a.size) as after, format('%+,d', a.size - b.size) as diff, case when a.size > 28672 then 'X' else '' end as oversized from b join a on a.name = b.name;" \
  ".print ''" \
  "select format('%+g', avg(a.size - b.size)) as 'avg(diff)' from b join a on a.name = b.name;"
  
