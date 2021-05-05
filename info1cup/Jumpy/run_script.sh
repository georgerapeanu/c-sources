for file in jumpy_$2_*.in;do
echo "doing " $file
time ./$1 < $file > ${file%.*}.ok
done;

