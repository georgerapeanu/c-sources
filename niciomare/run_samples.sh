#!/bin/bash
for x in `seq 1 9`;do cp sample$x.in niciomare.in;./_$1;md5sum niciomare.$2 sample$x.out;done
