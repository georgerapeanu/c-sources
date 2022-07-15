#!/usr/bin/bash -x

curr="01";./_random_gen -n 8 -q 3 -vmax 10 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="02";./_random_gen -n 1000 -q 1000 -vmax 1000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="03";./_random_gen -n 100000 -q 100000 -vmax 1000000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="04";./_random_gen -n 99000 -q 100000 -vmax 1000000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="05";./_random_gen -n 99441 -q 100000 -vmax 1000000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="06";./_random_gen -n 99508 -q 100000 -vmax 1000000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="07";./_random_gen -n 99999 -q 100000 -vmax 1000000000 > ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="08";./_random_gen -n 100000 -q 100000 -vmax 1000000000 asgsatastastsatastga> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="09";./_random_gen -n 100000 -q 100000 -vmax 1000000000 a5qtgsgasdherjdh> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="10";./_random_gen -n 100000 -q 100000 -vmax 1000000000 abdhagssagasyesuduj> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="11";./_random_gen -n 100000 -q 100000 -vmax 1000000000 a5yfjdystsxdgsxzgsd> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="12";./_random_gen -n 100000 -q 100000 -vmax 1000000000 assgsgb7a86iuty> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="13";./_random_gen -n 100000 -q 100000 -vmax 1000000000 byqetaehyesyesy> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="14";./_random_gen -n 100000 -q 100000 -vmax 1000000000 ojoiniunoipkoni> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="15";./_random_gen -n 100000 -q 100000 -vmax 1000000000 ojoniubniuojmnkn> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="16";./_random_gen -n 100000 -q 100000 -vmax 1000000000 yueitningsdjknm> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="17";./_random_gen -n 100000 -q 100000 -vmax 1000000000 ihnrtojgmfkhfdmb> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="18";./_random_gen -n 100000 -q 100000 -vmax 1000000000 qitmndoskndgksdlmg> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="19";./_random_gen -n 100000 -q 100000 -vmax 1000000000 lkjhgbvgyuik,mn> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
curr="20";./_random_gen -n 100000 -q 100000 -vmax 1000000000 vioeuahtqiugtiusagui> ./tests/$curr.in;./_arbore-x-y < ./tests/$curr.in > ./tests/$curr.ans;
