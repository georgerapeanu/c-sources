task=$1;for test in {1..5};do echo $task|./_gen > jumpy_${task}_${test}.in;time ./_best < jumpy_${task}_${test}.in > jumpy_${task}_${test}.ok;time ./_tinca-good-matching < jumpy_${task}_${test}.in > jumpy_${task}_${test}.out;md5sum jumpy_${task}_${test}.out jumpy_${task}_${test}.ok;done;


