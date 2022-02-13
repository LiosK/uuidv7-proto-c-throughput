/**
 * uuidv7.c - Experimental throughput-oriented UUIDv7 implementation
 *
 * This version employs 48-bit (~0.25 millisecond precision) timestamp and
 * 12-bit random-starting (or zero-starting #ifdef ZERO_START_COUNTER) counter.
 *
 * Copyright 2022 LiosK
 *
 * Licensed under the Apache License, Version 2.0
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void get_timestamp(uint64_t *out) {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  *out = (uint64_t)tp.tv_sec << 12;
  *out |= ((uint64_t)tp.tv_nsec << 12) / 1000000000;
}

/**
 * @param out uint8_t id[16]
 * @warning This function is not thread safe.
 */
void uuidv7_generate(uint8_t *out) {
#define RAND_BUFFER_SIZE (1024)
  static uint8_t rand_buf[RAND_BUFFER_SIZE];
  static int rand_cursor = RAND_BUFFER_SIZE;
  if (rand_cursor >= RAND_BUFFER_SIZE - 2 - 8) {
    arc4random_buf(&rand_buf, RAND_BUFFER_SIZE);
    rand_cursor = 0;
  }

#define MAX_COUNTER ((1 << 12) - 1)
#ifdef ZERO_START_COUNTER
#define MAX_COUNTER_START (0)
#else
#define MAX_COUNTER_START ((1 << 12) - 1)
#endif
  static struct State {
    uint_fast64_t timestamp; // 48-bit timestamp
    uint_fast16_t counter;   // 12-bit counter
  } st;

  uint_fast64_t now;
  get_timestamp(&now);
  if (st.timestamp < now) {
    st.timestamp = now;
    st.counter = rand_buf[rand_cursor++] << 8;
    st.counter |= rand_buf[rand_cursor++];
    st.counter &= MAX_COUNTER_START;
  } else {
    if (++st.counter > MAX_COUNTER) {
      fprintf(stderr, "INFO: counter limit reached\n");
      uint_fast32_t n_trials = 0;
      do {
        get_timestamp(&now);
        if (n_trials++ > 1000000) {
          fprintf(stderr, "WARN: clock did not move; monotonicity broken\n");
          break;
        }
      } while (st.timestamp >= now);
      st.timestamp = now;
      st.counter = rand_buf[rand_cursor++] << 8;
      st.counter |= rand_buf[rand_cursor++];
      st.counter &= MAX_COUNTER_START;
    }
  }

  out[0] = st.timestamp >> 40;
  out[1] = st.timestamp >> 32;
  out[2] = st.timestamp >> 24;
  out[3] = st.timestamp >> 16;
  out[4] = st.timestamp >> 8;
  out[5] = st.timestamp;
  out[6] = 0x70 | (st.counter >> 8); // version bits 0b0111
  out[7] = st.counter;
  out[8] = 0x80 | (rand_buf[rand_cursor++] & 0x3F); // variant bits 0b10
  for (int i = 9; i < 16; i++) {
    out[i] = rand_buf[rand_cursor++];
  }
}

/**
 * @param id uint8_t id[16]
 * @param out char text[37]
 */
void uuidv7_to_string(const uint8_t *id, char *out) {
  static const char digits[16] = "0123456789abcdef";

  char *p = out;
  for (int i = 0; i < 16; i++) {
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      *p++ = '-';
    }
    *p++ = digits[id[i] >> 4];
    *p++ = digits[id[i] & 0xF];
  }
  *p = '\0';
}

int main() {
  uint8_t id[16];
  char buffer[512] = {0};

  while (1) {
    for (int i = 0; i < 512 / 37; i++) {
      uuidv7_generate(id);
      uuidv7_to_string(id, &buffer[i * 37]);
      buffer[i * 37 + 36] = '\n';
    }
    fputs(buffer, stdout);
  }
  return 0;
}
