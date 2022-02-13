#!/bin/bash

set -x
tmp=tmp.65d57e89
mkdir "$tmp"

exe=uuidv7_rand;         timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
exe=uuidv7_zero;         timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
exe=ts48cnt12_rand;      timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
exe=ts48cnt12_zero;      timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
exe=ts48cnt12_msec_rand; timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
exe=ts48cnt12_msec_zero; timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq

if [ $1 = "--verify" ]; then
  timeout 1s ./uuidv7_rand.out         > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
  timeout 1s ./uuidv7_zero.out         > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
  timeout 1s ./ts48cnt12_rand.out      > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
  timeout 1s ./ts48cnt12_zero.out      > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
  timeout 1s ./ts48cnt12_msec_rand.out > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
  timeout 1s ./ts48cnt12_msec_zero.out > "$tmp/verify" 2> /dev/null; ./verify_ids.pl "$tmp/verify"
fi
