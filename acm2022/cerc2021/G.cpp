#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000000;
const int MOD = 1000003;

int is_composite[NMAX + 5];
int mobius[NMAX + 5];
int mobius_times_d[NMAX + 5]; 
int mobius_times_d2[NMAX + 5]; 

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}

int f(int n, int k){
  vector<pair<int, int> > ranges;

  int max_d = 0;
  for(int d = 1; 1LL * d * d < n;d++){
    ranges.push_back({d, d});
    max_d = d;
  }
  for(int d = 1; 1LL * d * d < n;d++){
    ranges.push_back({(n - 1)  / (d + 1) + 1, (n - 1) / d});
    if(ranges.back().first <= max_d){
      ranges.back().first = max_d + 1;
      if(ranges.back().second < ranges.back().first){
        ranges.pop_back();
        break;
      }
    }
  }

  int answer = 0;
  if(k < n){
    answer = add(answer, mult(4, mult(n % MOD, sub(n % MOD, k))));
  }

  for(auto it:ranges){
    int value0 = 1;
    int value1 = ((n - 1) / (it.first * k)) % MOD;
    int value2 = mult(value1, value1);
    int value3 = mult(value1, value2);
    int value4 = mult(value2, value2);

    int coef_mobius_0 = sub(mobius[it.second], mobius[it.first - 1]);
    int coef_mobius_1 = sub(mobius_times_d[it.second], mobius_times_d[it.first - 1]);
    int coef_mobius_2 = sub(mobius_times_d2[it.second], mobius_times_d2[it.first - 1]);

    int local_answer = 0;

    local_answer = add(local_answer, mult(mult(n % MOD, n % MOD), mult(value2, coef_mobius_0)));

    local_answer = sub(local_answer, mult(mult(1, n % MOD), mult(value3, mult(k, coef_mobius_1))));
    local_answer = sub(local_answer, mult(mult(1, n % MOD), mult(value2, mult(k, coef_mobius_1))));

    local_answer = add(local_answer, mult(mult(MOD /2 + 1, MOD / 2 + 1), mult(value4, mult(mult(k, k), coef_mobius_2))));
    local_answer = add(local_answer, mult(mult(MOD /2 + 1, MOD / 2 + 1), mult(mult(value3, 2), mult(mult(k, k),coef_mobius_2))));
    local_answer = add(local_answer, mult(mult(MOD /2 + 1, MOD / 2 + 1), mult(value2, mult(mult(k, k), coef_mobius_2))));

    answer = add(answer, add(local_answer, local_answer));
    answer = add(answer, add(local_answer, local_answer));

 //   cerr << "debug_inside " << value1 << " " << local_answer << "\n";

//    answer = add(answer, mult(mult(4, mult(n, n)), mult(value2, coef_mobius_0)));
   // answer = add(answer, mult(mult(4, mult(n, n)), mult(value1, coef_mobius_0)));
  //  answer = add(answer, mult(mult(1, mult(n, n)), mult(value0, coef_mobius_0)));
    
//    answer = sub(answer, mult(mult(8, n), mult(value3, coef_mobius_1)));
 //   answer = sub(answer, mult(mult(8, n), mult(value2, coef_mobius_1)));
 //   answer = sub(answer, mult(mult(2, n), mult(value1, coef_mobius_1)));
    
 //   answer = add(answer, mult(4, mult(value4, coef_mobius_2)));
  //  answer = add(answer, mult(4, mult(value3, coef_mobius_2)));
  //  answer = add(answer, mult(1, mult(value2, coef_mobius_2)));
  }
  return answer;
}

int main(){

  for(int i = 1;i <= NMAX;i++){
    mobius[i] = 1;
    is_composite[i] = false;
  }

  for(int i = 2;i <= NMAX;i++){
    if(is_composite[i]){
      continue;
    }
    for(int j = i;j <= NMAX;j += i){
      mobius[j] *= -1;
    }
    if(1LL * i * i <= NMAX){
      for(int j = i * i; j <= NMAX;j += i * i){
        mobius[j] = 0;
      }
    }
  }

  for(int i = 1;i <= NMAX;i++){
    if(mobius[i] < 0){
      mobius[i] = MOD + mobius[i];
    }
    mobius_times_d[i] = mult(i, mobius[i]);
    mobius_times_d2[i] = mult(i, mobius_times_d[i]);
    mobius[i] = add(mobius[i - 1], mobius[i]);
    mobius_times_d[i] = add(mobius_times_d[i - 1], mobius_times_d[i]);
    mobius_times_d2[i] = add(mobius_times_d2[i - 1], mobius_times_d2[i]);
  }
  
  int q;
  scanf("%d", &q);

  while(q--){
    int n;
    scanf("%d", &n);

    if(n == 1){
      printf("%d\n", 0);
      continue;
    }
   
  //  cerr << "debug " << f(n, 1) << " " << f(n, 2) << "\n";
    printf("%d\n", mult(sub(f(n, 1), f(n, 2)), MOD / 2 + 1));
  }

  return 0;
}
