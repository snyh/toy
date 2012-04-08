#!/usr/bin/perl
use warnings;
use strict;
my $one="0x00,0x80,0x80,0x80,\n";
my $zero="0x00,0x80,\n";
my $ptn=0x01;

print ("0x00\n" x 19);
print ("0x80\n" x 9);


print $zero x 8;
print $one x 8;

print $zero,$zero,$zero,$zero, $zero,$zero,$one, $zero;
print $one, $one, $one, $one, $one, $one, $zero, $one;

print "0x80,\n" x (1024-32*3-19-9);
