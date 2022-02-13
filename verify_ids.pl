#!/usr/bin/env perl

my $prev = "";
while (<>) {
  die "wrong format: $_" unless /^[0-9a-f]{8}-[0-9a-f]{4}-7[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/;
  die 'broken monotonicity' unless $prev lt $_;
  $prev = $_;
}
