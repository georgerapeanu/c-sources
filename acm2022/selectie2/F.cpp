#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > my_2k_special_swap(vector<pair<int,int>> &swaps, int position, int length){
  vector<pair<int, int> > answer;
  if(length > 1){
    answer.push_back({position + 1, position + 2 * length - 2});
  }
  answer.push_back({position, position + 1});
  if(length > 1){
    answer.push_back({position + 1, position + 2 * length - 2});
  }
  swaps.push_back({position, position + length});

  return answer;
}

vector<pair<int, int> > my_2k_swap(int n, vector<pair<int, int>> &swaps, int position, int length){
  if(position + length * 2 <= n){
    return my_2k_special_swap(swaps, position, length);
  }
  length >>= 1;
  vector<pair<int, int> > answer;
  while(true){
    vector<pair<int, int> > tmp;
    tmp = my_2k_special_swap(swaps, position, length);
    for(auto it:tmp){
      answer.push_back(it);
    }
    position += length;
    if(position + 2 * length <= n){
      tmp = my_2k_special_swap(swaps, position, length);
      for(auto it:tmp){
        answer.push_back(it);
      }
      return answer;
    }
    length >>= 1;
  }
}

vector<pair<int, int> > from_0_to_pos(int n, vector<int> &positions, int position, bool rev){
  int tmp = position;
  if(position == 0){
    return vector<pair<int,int>>();
  }
  vector<int> lengths;
  while(position){
    lengths.push_back(position & (-position));
    position ^= lengths.back();
  }
  int current = 0;
  vector<pair<int, int> > answer = {};
  vector<pair<int, int> > swaps;
  for(int i = (int)lengths.size() - 1;i >= 0;i--){
    int current_length = lengths[i];
    vector<pair<int, int> > tmp = my_2k_swap(n, swaps, current, current_length);
    for(auto it:tmp){
      answer.push_back(it);
    }
    current += current_length;
  }
  if(rev){
    reverse(answer.begin(), answer.end());
    reverse(swaps.begin(), swaps.end());
  }
  //cerr << "attempt for " << tmp << "\n";
  for(auto it:swaps){
    swap(positions[it.first], positions[it.second]);
   // cerr << "swapping " << it.first << " " << it.second << "\n";
  }
  //for(auto it:answer){
  //  cerr << "answer is " << it.first << " " << it.second << "\n";
  //}
  return answer;
}

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);
    vector<int> values(n, 0);
    vector<int> positions(n, 0);
    for(auto &it:values){
      scanf("%d", &it);
      it--;
    }
    for(int i = 0;i < n;i++){
      positions[values[i]] = i;
    }

    vector<pair<int, int> > answer;

    for(int i = n;i >= 1;i--){
      int pos = positions[i - 1];
      if(i - 1 == pos){
        continue;
      }
      vector<pair<int, int> > tmp;
      tmp = from_0_to_pos(n, positions, pos, true);    
      for(auto it:tmp){
        answer.push_back(it);
      }
      tmp = from_0_to_pos(n, positions, i - 1, false);    
      for(auto it:tmp){
        answer.push_back(it);
      }
  //    cerr << "values: ";
  //    for(auto it:values){
  //      cerr << it << " ";
  //    }
  //    cerr << "\n";
    }

    printf("%d\n", (int)answer.size());
    for(auto it:answer){
      printf("%d %d\n", it.first, it.second);
    }

  }

  return 0;
}
