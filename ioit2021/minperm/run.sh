for file in *.in;do ./_main < $file > ${file%.*}.ok;done
