- `uuidv7_rand.out`: 52-bit (~15 microsecond precision) timestamp and 14-bit random-starting counter
- `uuidv7_zero.out`: 52-bit (~15 microsecond precision) timestamp and 14-bit zero-starting counter
- `ts48cnt12_rand.out`: 48-bit (~0.25 millisecond precision) timestamp and 12-bit random-starting counter
- `ts48cnt12_zero.out`: 48-bit (~0.25 millisecond precision) timestamp and 12-bit zero-starting counter
- `ts48cnt12_msec_rand.out`: 48-bit millisecond-precision timestamp and 12-bit random-starting counter
- `ts48cnt12_msec_zero.out`: 48-bit millisecond-precision timestamp and 12-bit zero-starting counter

```bash
$ uname -a
Darwin mymacbook.local 21.3.0 Darwin Kernel Version 21.3.0: Wed Jan  5 21:37:58 PST 2022; root:xnu-8019.80.24~20/RELEASE_X86_64 x86_64
$
$ tmp=tmp.65d57e89
$ mkdir "$tmp"
$
$ exe=uuidv7_rand;         timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[ 421MiB/s]
    2524 tmp.65d57e89/uuidv7_rand
INFO: counter limit reached
$ exe=uuidv7_zero;         timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[ 431MiB/s]
       0 tmp.65d57e89/uuidv7_zero
$ exe=ts48cnt12_rand;      timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[ 272MiB/s]
   10140 tmp.65d57e89/ts48cnt12_rand
INFO: counter limit reached
$ exe=ts48cnt12_zero;      timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[ 418MiB/s]
       0 tmp.65d57e89/ts48cnt12_zero
$ exe=ts48cnt12_msec_rand; timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[71.2MiB/s]
    3501 tmp.65d57e89/ts48cnt12_msec_rand
INFO: counter limit reached
$ exe=ts48cnt12_msec_zero; timeout 3.5s ./$exe.out 2> "$tmp/$exe" | pv -r > /dev/null; wc -l "$tmp/$exe"; sort "$tmp/$exe" | uniq
[ 144MiB/s]
    3500 tmp.65d57e89/ts48cnt12_msec_zero
INFO: counter limit reached
```
