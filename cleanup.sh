#!/usr/bin/bash
for i in $(find .); do
  if [ -x $i ] && [ -f $i ] && echo $i | grep -q -v -E '(cpp$)|(sh$)|(c$)|(py$)|([.]git)' 2> /dev/null; then 
      rm $i;
  fi
done
