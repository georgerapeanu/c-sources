#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;
const int QMAX = 2000;

FILE *f = fopen("transform3.in","r");
FILE *g = fopen("transform3.out","w");

int n;
int q;
int l[QMAX + 5];
int r[QMAX + 5];
int lastNode;

int getNextNode(){
  return ++lastNode;
}

vector<pair<int,int> > answer;
void addEdge(int x,int y){
  answer.push_back({x,y});
}

void processBucket(int leftId,int rightId){
  if(leftId == rightId){
    for(int i = l[rightId];i <= r[leftId];i++){
      addEdge(n + leftId,i);
    }
    return ;
  }
  int centerNode = getNextNode();
  

  for(int i = l[rightId];i <= r[leftId];i++){
    addEdge(centerNode,i);
  }
  
  int lastNode = centerNode;
  for(int i = leftId + 1;i <= rightId;i++){
    if(r[i - 1] + 1 <= r[i]){
      int currentNode = getNextNode();
      addEdge(currentNode,lastNode);
      for(int j = r[i - 1] + 1;j <= r[i];j++){
        addEdge(currentNode,j);
      }
      addEdge(n + i,currentNode);
      lastNode = currentNode;
    }else{
      addEdge(n + i,lastNode);
    }
  }

  lastNode = centerNode;
  for(int i = rightId - 1;i >= leftId;i--){
    if(l[i] < l[i + 1]){
      int currentNode = getNextNode();
      addEdge(currentNode,lastNode);
      for(int j = l[i];j < l[i + 1];j++){
        addEdge(currentNode,j);
      }
      addEdge(n + i,currentNode);
      lastNode = currentNode;
    }else{
      addEdge(n + i,lastNode);
    }
  }
}

int main(){

  fscanf(f,"%d %d",&n,&q);
  lastNode = n + q;

  for(int i = 1;i <= q;i++){
    fscanf(f,"%d %d",&l[i],&r[i]);
  }

  int last = 1;

  for(int i = 2;i <= q;i++){
    if(r[last] < l[i]){
      processBucket(last,i - 1);
      last = i;
    }
  }

  processBucket(last,q);
  
  fprintf(g,"%d\n",(int)answer.size());
  for(auto it:answer){
    fprintf(g,"%d %d\n",it.first,it.second);  
  }


  return 0;
}
