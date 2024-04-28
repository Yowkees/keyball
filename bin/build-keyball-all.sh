#!/bin/sh

set -u

id=$(date "+%Y%m%d_%H%M%S")
logdir=tmp/build_log/${id}

keyboards=()
keyboards+=(keyball44)

keymaps=()
keymaps+=(test)
keymaps+=(default)
keymaps+=(via)

mkdir -p ${logdir}

for kb in "${keyboards[@]}" ; do
  tmpmaps=(${keymaps[@]})
  for km in "${tmpmaps[@]}" ; do
    ( make SKIP_GIT=yes KEEP_BIN=true COLOR=false "keyball/${kb}:${km}" 2>&1 | tee "${logdir}/${kb}-${km}.log" | LANG=C.utf-8 ts "[${kb}:${km}]" ) &
  done
done

wait

$(dirname "$0")/hexsize.sh keyball_*.hex | tee "${logdir}/size.tsv"
