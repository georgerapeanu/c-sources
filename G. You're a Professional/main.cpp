#!/usr/bin/env perl
use strict;
use warnings;
my ($h, $w, $t)=split(/\s+/,<>);my @s=<>;my $ans=0;for(my $j=0;$j<$w;++$j){my $cnt=0;for(my $i=0;$i<$h;++$i){if(substr($s[$i],$j,1)eq'Y'){++$cnt;}}if($cnt>=$t){++$ans;}}print "$ans\n";
#kitten#
