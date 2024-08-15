#!/usr/bin/perl
#
# Copyright (c) 2024 Piotr Stolarz
# CRaC: C++17 Cyclic Redundancy Check (CRC) template library.
#
# Distributed under the 2-clause BSD License (the License)
# see accompanying file LICENSE for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#
use strict;
use warnings;

if (@ARGV <= 0) {
    print(STDERR "Usage: gen_c_bind.pl CRC_LIST\n");
    exit(1);
}

my $crcs = \@ARGV;
my @rtypes = ();

foreach my $crc (@$crcs) {
    ((my $sz) = $crc =~ m/CRC([0-9]+)/) or die "Invalid CRC specified: " . $crc;
    my $rtype = ($sz <= 8 ? "uint8_t" :
        ($sz <= 16 ? "uint16_t" :
            ($sz <= 32 ? "uint32_t" :
                ($sz <= 64 ? "uint64_t" :
                    "__uint128_t"))));

    push(@rtypes, $rtype);
}

sub subst_tmpl
{
    my $in = $_[0];
    my $out = $_[1];
    my $api_off = 0;
    my $crc_i = 0;

    while (my $l = <$in>) {
        if ($api_off == 0) {
            if ($l =~ m/^[ \t]*__SUBST_START__[ \t]*$/) {
                $api_off = tell($in);
            } else {
                print($out $l);
            }
        } else {
            if ($l =~ m/^[ \t]*__SUBST_END__[ \t]*$/) {
                $crc_i++;

                if ($crc_i < scalar(@$crcs)) {
                    seek($in, $api_off, 0);
                } else {
                    $api_off = 0;
                    $crc_i = 0;
                }
            } else {
                $l =~ s/__CRC__/@$crcs[$crc_i]/g;
                $l =~ s/__CRCTYPE__/$rtypes[$crc_i]/g;

                print($out $l);
            }
        }
    }

}

open(my $fht, "<", "crac_c.h.tmpl") or die "Can't open crac_c.h.tmpl: " . $!;
open(my $fcppt, "<", "crac_c.cpp.tmpl") or die "Can't open crac_c.cpp.tmpl: " . $!;
open(my $fh, ">", "crac_c.h") or die "Can't create crac_c.h: " . $!;
open(my $fcpp, ">", "crac_c.cpp") or die "Can't create crac_c.cpp: " . $!;

subst_tmpl($fht, $fh);
subst_tmpl($fcppt, $fcpp);

END {
    close($fcpp) if defined($fcpp);
    close($fh) if defined($fh);
    close($fcppt) if defined($fcppt);
    close($fht) if defined($fht);
}
