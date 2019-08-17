#!/bin/bash
for x in `seq 1 7`;do cp sample$x.in palatulvoltaic.in;./_$1;md5sum palatulvoltaic.$2 sample$x.out;done
