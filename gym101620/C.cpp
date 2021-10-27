#include <bits/stdc++.h>

using namespace std;

struct node_t{
  long long a,b;

  node_t(){
    a = 0;
    b = 0;
  }

  node_t(long long a,long long b){
    this->a = a;
    this->b = b;
  }
  
  node_t getSon(int son){
    return node_t(2 * a,2 * b + son);
  }

  long long eval(long long initialValue)const{
    return a * initialValue + b;
  }

  node_t operator + (const node_t &other)const{
    node_t ans;
    ans.a = a + other.a;
    ans.b = b + other.b;
    return ans;
  }
};

vector<node_t> getPrufer(node_t node,bool noFather,int depth){
  if(depth == 1){
    return {};
  }
  vector<node_t> ans,tmp;
  ans = getPrufer(node.getSon(0),false,depth - 1);
  ans.push_back(node);
  tmp = getPrufer(node.getSon(1),noFather,depth - 1);
  

  for(auto it:tmp){
    ans.push_back(it);
  }
  if(noFather == false){
    ans.push_back(node);
  }
  return ans;
}

long long solve(int node,bool noFather,int depth,int l,int d,int m,int splitPoint,const vector<node_t> &sum){
  int r = l + (m - 1) * d;
  if(depth <= splitPoint){
    l -= d;
    int r = l + m * d;
    printf("sum %d %d %d\n",l,r,d);
    long long ans = sum[r].eval(node);
    if(l >= 0){
      ans -= sum[l].eval(node);
    }
    return ans;
  }
  long long ans = 0;
  
  int fstMyIdx = ((1 << (depth - 1)) - 1) - 1;
  int sndMyIdx = (1 << depth) - 2 - 1;
  if(l <= fstMyIdx && l + d * (m - 1) >= fstMyIdx && (fstMyIdx - l) % d == 0){
    ans += sum[fstMyIdx].eval(node);
    if(fstMyIdx - d >= 0){
      ans -= sum[fstMyIdx].eval(node);
    }
  }
  if(l <= sndMyIdx && l + d * (m - 1) >= sndMyIdx && (sndMyIdx - l) % d == 0){
    ans += sum[sndMyIdx].eval(node);
    if(sndMyIdx - d >= 0){
      ans -= sum[sndMyIdx].eval(node);
    }
  }
  
  int leftSonSt = 0;
  int leftSonDr = (1 << (depth - 1)) - 3;
  int rightSonSt = (1 << (depth - 1)) - 1;
  int rightSonDr = (1 << depth) - 3;

  if(l <= leftSonDr){
    int leftSonM = (leftSonDr - l) / d + 1;
    ans += solve(node * 2,depth - 1,l,d,leftSonM,splitPoint,sum);
  }

  if(r >= rightSonSt){
    int rightSonL = ((rightSonSt - l + d - 1) / d) * d + l;
    int rightSonM = (r - rightSonL) / d + 1;
    ans += solve(node * 2 + 1,depth - 1,rightSonL,d,rightSonM,splitPoint,sum);
  }

  return ans;
}

int main(){

  int k,q;
  scanf("%d %d",&k,&q);
  int splitPoint = min(k,15);
  vector<node_t> prufer = getPrufer(node_t(1,0),splitPoint);
  vector<node_t> sum(prufer.size());

  while(q--){
    int l,d,m;
    scanf("%d %d %d",&l,&d,&m);
    l--;
    for(int i = 0;i < (int)sum.size();i++){
      sum[i] = prufer[i];
      if(i >= d){
        sum[i] = sum[i - d] + sum[i]; 
      }
    }
    printf("%lld\n",solve(1,k,l,d,m,splitPoint,sum));
  }


  return 0;
}
