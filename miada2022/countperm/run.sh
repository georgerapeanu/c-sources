for i in `ls *.in | grep -v countperm`;do cp $i countperm.in;time ./_countperm;cp countperm.out ${i%.*}.ok;done
