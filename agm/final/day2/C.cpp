#include <bits/stdc++.h>

using namespace std;

const int DEB = false;

class _2SATSolver{
public:

  int n;
  vector<vector<int> > graph;
  vector<int> ctc;
  vector<vector<int> > comp;
  vector<int> toposort;
  vector<int> low;
  vector<int> id;
  vector<int> st;
  vector<int> inst;
  vector<int> viz;
  vector<int> value;
  int last_id;

  inline int transform(int x){
    if(x < 0){
      return (-x) * 2 + 1;
    }
    return x * 2;
  }

  void dfs(int nod){
    low[nod] = id[nod] = ++last_id;
    viz[nod] = 1;
    st.push_back(nod);
    inst[nod] = true;
    for(auto it:graph[nod]){
      if(viz[it] == 0){
        dfs(it);
      }
      if(inst[it] == true){
        low[nod] = min(low[nod],low[it]);
      }
    }
    if(low[nod] == id[nod]){
      if(DEB){
        printf("packing %d\n",nod);
      }
      vector<int> nodes;
      while(st.back() != nod){
        nodes.push_back(st.back());
        inst[st.back()] = false;
        st.pop_back();
      }
      nodes.push_back(st.back());
      inst[st.back()] = false;
      st.pop_back();
      for(auto it:nodes){
        ctc[it] = comp.size();
      }
      toposort.push_back(comp.size());
      comp.push_back(nodes);
    } 
  }

public:

  _2SATSolver(int n){
    this->n = n;
    graph = vector<vector<int> > (2 * n + 5,vector<int>());
    ctc = vector<int>(2 * n + 5);
    comp = vector<vector<int> > ();
    toposort = vector<int>();
    id = vector<int>(2 * n + 5);
    low = vector<int>(2 * n + 5);
    st = vector<int>();
    inst = vector<int>(2 * n + 5,0);
    viz = vector<int>(2 * n + 5,0);
    value = vector<int>(2 * n + 5,-1);
    last_id = 0;
  }

  void add_relation(int x,int y){
    if(DEB){
      printf("add edge %d %d\n",transform(x),transform(-y));
      printf("add edge %d %d\n",transform(y),transform(-x));
    }
    graph[transform(x)].push_back(transform(-y));
    graph[transform(y)].push_back(transform(-x));
  }

  bool build(){
    ctc = vector<int>(2 * n + 5);
    id = vector<int>(2 * n + 5);
    low = vector<int>(2 * n + 5);
    comp = vector<vector<int> > ();
    comp.push_back(vector<int>());
    toposort = vector<int>();
    st = vector<int>();
    inst = vector<int>(2 * n + 5,0);
    viz = vector<int>(2 * n + 5,0);
    value = vector<int>(2 * n + 5,-1);
    last_id = 0;
  
    for(int i = transform(1);i <= transform(-n);i++){
      if(viz[i] == 0){
        dfs(i);
      }
    }

    if(DEB){
      for(int i = 0;i < (int)ctc.size();i++){
        printf("deb %d is in %d\n",i,ctc[i]);
      }
    }

    reverse(toposort.begin(),toposort.end());
    
      for(int i = 1;i <= n;i++){
        if(ctc[transform(i)] == ctc[transform(-i)]){
          if(DEB){
            printf("return 108\n");
          }
          return false;
        }
      }

    for(auto id:toposort){
      if(DEB){
        printf("doing %d\n",id);
      }
      if(value[id] == -1){
        value[id] = 0;
      }
      if(value[id] == 1){
        for(auto node:comp[id]){
          for(auto it:graph[node]){
            if(value[ctc[it]] == -1){
              value[ctc[it]] = 1;
            }else if(value[ctc[it]] == 0){
              if(DEB){
                printf("return 123\n");
              }
              return false;
            }
          }
        }
      }
      for(auto it:comp[id]){
        int other = ctc[it ^ 1];
        if(DEB){
          printf("deb %d %d %d\n",other,value[other],value[id]);
        }
        if(value[other] == -1){
          value[other] = !value[id];
        }else if(value[other] == value[id]){
          if(DEB){
            printf("return 134\n");
          }
          return false; 
        }
      }
    }
    return true;
  }
};

int n,m;
vector<pair<int,int> > stuff;

bool check(int x){
  if(DEB){
    printf("tring %d...\n",x);
  }
  _2SATSolver solver(n);
  for(int i = 0;i <= x;i++){
    solver.add_relation(stuff[i].first,stuff[i].second);
  }
  bool tmp =  solver.build();
  if(DEB && tmp == true){
    printf("%d was true:\n",x);
    for(auto it:solver.value){
      printf("%d ",it);
    }
    printf("\n");
  }
  return tmp;
}

int main(){

  scanf("%d %d",&n,&m);

  stuff = vector<pair<int,int> >(m);

  for(auto &it:stuff){
    scanf("%d %d",&it.first,&it.second);
  }

  int l = -1;
  int r = m;

  while(r - l > 1){
    int mid = (l + r) / 2;
    if(check(mid)){
      l = mid;
    }else{
      r = mid;
    }
  }

  printf("%d\n",max(0,m - r - 1));

  return 0;
}
