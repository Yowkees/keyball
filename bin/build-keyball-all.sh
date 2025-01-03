#!/bin/sh

set -u

id=$(date "+%Y%m%d_%H%M%S")
logdir=tmp/build_log/${id}

keyboards=()
keyboards+=(keyball39)
keyboards+=(keyball44)
keyboards+=(keyball46)
keyboards+=(keyball61)
keyboards+=(one47)

keymaps=()
keymaps+=(test)
keymaps+=(default)
keymaps+=(via)

mkdir -p ${logdir}

for kb in "${keyboards[@]}" ; do
  tmpmaps=(${keymaps[@]})
  # Add special keymaps for keyball46
  if [ $kb = keyball46 ] ; then
    tmpmaps+=(test_Left test_Both)
    tmpmaps+=(via_Left via_Both)
  fi
  for km in "${tmpmaps[@]}" ; do
    ( make SKIP_GIT=yes KEEP_BIN=true COLOR=false "keyball/${kb}:${km}" 2>&1 | tee "${logdir}/${kb}-${km}.log" | LANG=C.utf-8 ts "[${kb}:${km}]" ) &
  done
done

wait

$(dirname "$0")/hexsize.sh keyball_*.hex | tee "${logdir}/size.tsv"
