#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 1;

vector<int> id;
pair<int,int> my_min(pair<int, int> a, pair<int, int> b){
  if(a.first != b.first){
    return a.first < b.first ? a:b;
  }
  return id[a.second] > id[b.second] ? a:b;
}

class LightSegmentTree{
  int n;
  vector<pair<int, int>> aint;
public:

  LightSegmentTree(int n){
    this->n = n;
    this->aint = vector<pair<int, int>>(2 * n, make_pair(inf, 0));
  }

  void update(int pos, int value){
  //  cerr << "update on " << this << " "  << pos << " with " << value << "\n";
    int b_pos = pos;
    for(aint[pos += n] = make_pair(value, b_pos);pos > 1;pos >>= 1){
      aint[pos >> 1] = my_min(aint[pos], aint[pos ^ 1]);
    }
  }

  pair<int, int> query(int l, int r){
    pair<int, int> answer = make_pair(inf, 0);
    int b_l = l;
    int b_r = r;
    for(l += n, r += n;l < r;l >>=1, r>>= 1){
      if(l & 1){
        answer = my_min(answer, aint[l++]); 
      }
      if(r & 1){
        answer = my_min(answer, aint[--r]);
      }
    }
 //   cerr << "query on " << this << " " << b_l << " " << b_r << " is " << answer.first << " " << answer.second << "\n";
    return answer;
  }
};

int main(){

  int n;
  
  scanf("%d", &n);

  vector<vector<int> > fr(3, vector<int>(360, 0));
  vector<vector<int> > cards_xor(3, vector<int>(360, 0));
  vector<vector<int> > color(n, vector<int>(3, 0));
  vector<set<int> > color_set(3, set<int>());
  id = vector<int>(n, 0);

  for(int i = 0;i < n;i++){
    for(int j = 0;j < 3;j++){
      scanf("%d", &color[i][j]);
      fr[j][color[i][j]]++;
      cards_xor[j][color[i][j]] ^= i;
      color_set[j].insert(color[i][j]);
    }
    scanf("%d", &id[i]);
  }

  auto getRight = [&color_set, &fr, &color](int pos, int __color) {
    if(fr[__color][color[pos][__color]] > 1){
      return pos;
    }
    set<int>::iterator it = color_set[__color].lower_bound(color[pos][__color] + 1);
    if(it == color_set[__color].end()){
        it = color_set[__color].begin();
    }
//    printf("right of %d %d is %d\n", pos, __color, *it);
    return *it;
  };
  
  auto getLeft = [&color_set, &fr, &color](int pos, int __color) {
    if(fr[__color][color[pos][__color]] > 1){
      return pos;
    }
    set<int>::iterator it = color_set[__color].lower_bound(color[pos][__color]);
    if(it == color_set[__color].begin()){
      it = prev(color_set[__color].end());
    }else{
      it = prev(it);
    }
//    printf("left of %d %d is %d\n", pos, __color, *it);
    return *it;
  };

  /// This function assumes that the card is not deleted
  auto calcSum = [&getRight, &getLeft, &fr, &color_set, &color](int pos) {
    int answer = 0;
    for(int i = 0;i < 3;i++){
      if(fr[i][color[pos][i]] > 1){
        continue;
      }
      int right = getRight(pos, i);
      int left = getLeft(pos, i);
      answer += (right >= color[pos][i] ? right - color[pos][i] :right + 360 - color[pos][i]);
      answer += (left <= color[pos][i] ? color[pos][i] - left : color[pos][i] + 360 - left);
    }
    return answer;
  };

  LightSegmentTree aint(n);

  for(int i = 0;i < n;i++){
    aint.update(i, calcSum(i));
  }

  for(int i = 1;i <= n;i++){
    int pos = aint.query(0, n).second;
    aint.update(pos, inf);
    if(i < n){
      vector<int> toUpdate;
      for(int j = 0;j < 3;j++){
        fr[j][color[pos][j]]--;
        cards_xor[j][color[pos][j]] ^= pos;
        if(fr[j][color[pos][j]] == 0){
          color_set[j].erase(color[pos][j]);
          int left = getLeft(pos, j); 
          int right = getRight(pos, j); 
//          printf("debug %d %d %d %d\n", pos, j, left, right);
          if(fr[j][left] == 1){
            toUpdate.push_back(cards_xor[j][left]);
//            printf("debug pushed left %d\n", cards_xor[j][left]);
          }
          if(fr[j][right] == 1){
            toUpdate.push_back(cards_xor[j][right]);
//            printf("debug pushed right %d\n", cards_xor[j][right]);
          }
        } else if(fr[j][color[pos][j]] == 1){
          toUpdate.push_back(cards_xor[j][color[pos][j]]);
        }
      }
      for(auto &it:toUpdate){
        aint.update(it, calcSum(it));
      }
    }
    printf("%d\n", id[pos]); 
  }

  return 0;
}
