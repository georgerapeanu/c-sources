#!/bin/bash -v

if [[ $# -ne 2 ]]; then 
  echo "Usage: $0 POLYGON_ARCHIVE_PATH PROBLEM_NAME"
  echo "\tPROBLEM_NAME should be the same as the name from pbinfo's input/output files"
  exit 1
fi

if ! ([[ -e $1 ]] &&  [[ $1 =~ \$linux.zip$ ]]); then
  echo "File $1 does not exist or is not the linux version of the polygon package"
fi 

if [[ $2 =~ "[ ]" ]]; then 
  echo "PROBLEM_NAME should not contain spaces"
fi

if ! [[ -d "tmp" ]]; then 
  mkdir tmp 
fi 

echo "A" | unzip "$1" -d tmp

if [[ -e "tmp/archive" ]] || [[ -d "tmp/archive" ]]; then 
  rm -rf tmp/archive 
fi 

mkdir tmp/archive
mkdir tmp/archive/tests
touch tmp/archive/tests/tests.txt

last_points=0
total_tests=`ls "tmp/tests" | grep -Ev "\.a$" | wc -l`
for i in `ls "tmp/tests" | grep -Ev "\.a$"`; do
    test_number=$((`echo $i | sed -E "s/^0*//"`-1))
    final_name="$test_number-$2"
    cp "tmp/tests/$i" "tmp/archive/tests/$final_name.in"
    cp "tmp/tests/$i.a" "tmp/archive/tests/$final_name.ok"
    echo "How many points for test $i/$total_tests?(suggested: $last_points, leave empty for this)"
    while true; do
      read answer
      if [[ $answer =~ ^(0|([1-9][0-9]*))$ ]]; then 
        last_points=$((`echo $answer | sed -E "s/^0*//"`))
        echo "selected $last_points"
        break
      elif [[ -z "$answer" ]]; then
        echo "selected by default $last_points"
        break
      else 
        echo "Selected value is either not an int or not valid as a points value, please try again"
      fi
    done
    echo "$test_number $last_points" >> tmp/archive/tests/tests.txt
done

if [[ -e archive.zip ]]; then 
  rm -rf archive.zip 
  echo ""
fi

curr_dir=$(pwd)
cd tmp/archive && zip -r archive.zip tests && cd $curr_dir;

mv tmp/archive/archive.zip .
rm tmp/ -rf
echo "Finished exporting, please double check(points especially)"


