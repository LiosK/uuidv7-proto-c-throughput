all: uuidv7_rand.out uuidv7_zero.out ts48cnt12_rand.out ts48cnt12_zero.out ts48cnt12_msec_rand.out ts48cnt12_msec_zero.out

clean:
	$(RM) *.out

%_rand.out: %.c
	$(CC) -Wall -Wextra -O -o $@ $<

%_zero.out: %.c
	$(CC) -DZERO_START_COUNTER -Wall -Wextra -O -o $@ $<
