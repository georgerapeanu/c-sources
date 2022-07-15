for file in *.in;do echo $file;./_$1 < $file > ${file%.*}.out;cp ${file%.*}.in in;cp ${file%.*}.out out;cp ${file%.*}.ok ok;./_checker;done
