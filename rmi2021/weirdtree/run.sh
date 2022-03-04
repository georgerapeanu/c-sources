for i in *.in;do echo $i;time ./$1 < $i > ${i%%.*}.out;md5sum ${i%%.*}.ok ${i%%.*}.out;done
