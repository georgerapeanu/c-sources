for i in *.in;do echo $i;echo $1;time ./$1 < $i > ${i%%.*}.out;echo $2;time ./$2 < $i > ${i%%.*}.out;done
