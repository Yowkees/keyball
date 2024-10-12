#!/bin/sh

set -eu

max=28672

echo "name	size	diff	check"
for f in "$@" ; do
  size=$(cut -c 2,3 "$f" | awk '{s+=strtonum("0x"$1)}END{print s}')
  check=$(if [ $size -gt $max ] ; then echo "X" ; else echo "O" ; fi)
  sign=$(if [ $size -gt $max ] ; then echo "+" ; else echo "" ; fi)
  diff=$(expr $size - $max)
  echo "$f	$size	$sign$diff	$check"
done
