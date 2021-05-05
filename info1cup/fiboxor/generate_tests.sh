#!/bin/bash
for i in {1..4};do for j in {1..1};do echo $i | ./_gen > fiboxor_${i}_${j}.in;cp fiboxor_${i}_${j}.in fiboxor.in;time ./_fiboxor;mv fiboxor.out fiboxor_${i}_${j}.ok;rm fiboxor.in;done;done;

