#include <bits/stdc++.h>

using namespace std;

mt19937 rng;

vector<int> generate_completely_random(int n){
  vector<int> perm(n, 0);
  for(int i = 0;i < n;i++){
    perm[i] = i + 1;
  }
  shuffle(perm.begin(), perm.end(), rng);
  return perm;
}

vector<int> generate_buckets_sqrt(int n){
  vector<int> perm(n, 0);
  for(int i = 0;i < n;i++){
    perm[i] = i + 1;
  }
  int target = sqrt(n);
  int idx = 0;

  while(idx < n){
    shuffle(perm.begin() + idx, perm.end(), rng);
    sort(perm.begin() + idx, perm.begin() + min(idx + target, n));
    if(rng() & 1){
      reverse(perm.begin() + idx, perm.begin() + min(idx + target, n));
    }
    idx += target;
  }

  return perm;
}

long long generate_random_ll(){
  return (((long long)rng()) << 32) | rng();
}

vector<int> generate_special(int n,int a,int b, int x, int y, int z){
  
  assert(n == a + b);

  vector<int> perm(n, 0);
  for(int i = 0;i < n;i++){
    perm[i] = i + 1;
  }
  shuffle(perm.begin(),perm.end(), rng);

  vector<vector<int> > asc_sequences(x, vector<int>());
  vector<vector<int> > desc_sequences(y, vector<int>());

  for(int i = 0;i < n;i++){
    if(i < a){
      asc_sequences[rng() %  (int)asc_sequences.size()].push_back(perm[i]);
    }else{
      desc_sequences[rng() %  (int)desc_sequences.size()].push_back(perm[i]);
    }
  }

  vector<int> asc_sequence;
  vector<int> desc_sequence;

  for(auto &sequence:asc_sequences){
    sort(sequence.begin(), sequence.end());
    for(auto it:sequence){
      asc_sequence.push_back(it);
    }
  }
  
  for(auto &sequence:desc_sequences){
    sort(sequence.begin(), sequence.end());
    reverse(sequence.begin(), sequence.end());
    for(auto it:sequence){
      desc_sequence.push_back(it);
    }
  }

  vector<int> merge_types;

  for(int i = 0;i < n;i++){
    merge_types.push_back(i < a);
  }

  shuffle(merge_types.begin(), merge_types.end(), rng);

  vector<long long> merge_order;

  int nxt_a = 0;
  int nxt_b = 0;

  for(int i = 0;i < n;i++){
    if(merge_types[i]){
       merge_order.push_back(asc_sequence[nxt_a++]);
    }else{
       merge_order.push_back(desc_sequence[nxt_b++]);
    }
  }

  for(int i = 0;i < n;i++){
    if(int(rng() % 100) < z){
      merge_order[i] = generate_random_ll();
    }
  }

  map<long long, int> last_id;
  for(auto it:merge_order){
    last_id[it]++;
  }

  int cnt_less = 1;
  for(auto &it:last_id){
    cnt_less += it.second;
    it.second = cnt_less - it.second;
  }
  
  vector<int> final_order;
  for(auto it:merge_order){
    final_order.push_back(last_id[it]++);
  }

  return final_order;
}

int main(){
  vector<pair<int,int>> tests = {
    {2, 50},
    {2, 700},
    {2, 2000},
    {2, 4000}
  };
  rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

  int last_test_id = 0;

  for(auto it:tests){
    for(int k = 0;k < it.first;k++){
      last_test_id++;
      char* filename = (char*)malloc(100);
      sprintf(filename, "grader_test%d.in", last_test_id);
      FILE *g = fopen(filename, "w");
    
      vector<int> perm;

      int a = (rng() % (it.second + 1));
      perm = generate_special(it.second, a, it.second - a, (rng() % 9) + 2, (rng() % 9) + 2, (rng() % 11) + 10);
      
      fprintf(g,"%d\n", (int)perm.size());
      for(auto it:perm){
        fprintf(g, "%d ", it);
      }
      fprintf(g, "\n");

      fclose(g);
      free(filename);
    }
  }

/*
  vector<pair<int,int>> samples = {
    {1, 7},
    {1, 12},
  };
  int last_sample_id = 0;

  for(auto it:samples){
    while(it.first--){
      last_sample_id++;
      char* filename = (char*)malloc(100);
      sprintf(filename, "sample_test%d.in", last_sample_id);
      FILE *g = fopen(filename, "w");
    
      vector<int> perm;

      if(rng() & 1){
        perm = generate_completely_random(it.second);
      }else{
        perm = generate_buckets_sqrt(it.second);
      }
      
      fprintf(g,"%d\n", (int)perm.size());
      for(auto it:perm){
        fprintf(g, "%d ", it);
      }
      fprintf(g, "\n");

      fclose(g);
      free(filename);
    }
  }
  */

  return 0;
}
