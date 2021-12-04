#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 'Z' - 'A' + 1;
const int DIGITS = 10;

struct node_t{
  node_t *sons[SIGMA];
  int cnt;
  bool ok;
  int dfsCnt;
  int index;
  int fatherEdge;
  node_t* father;
  node_t(){
    memset(sons,0,sizeof(sons));
    cnt = 0;
    dfsCnt = 0;
    index = 0;
    fatherEdge = 0;
    father = NULL;
  }
};

int globalIndex = 0;///horrible code i know
void ins(node_t* root,const string &s,int pos){
  if(pos >= (int)s.size()){
    root->cnt++;
    root->index = globalIndex++;
    return ;
  }

  if(root->sons[s[pos] - 'A'] == NULL){
    root->sons[s[pos] - 'A'] = new node_t();
    root->sons[s[pos] - 'A']->fatherEdge = s[pos] - 'A';
    root->sons[s[pos] - 'A']->father = root;
  }

  ins(root->sons[s[pos] - 'A'],s,pos + 1);
}

int ans = 0;
int value[SIGMA];
int inv[DIGITS];

void dfs(const string &a,const string &b, node_t *root,int pos,int carry,int fatherEdge){
  if(root == NULL){
    return ;
  }

  bool ok = ( carry == 0 && 
              pos >= (int)a.size() && 
              pos >= (int)b.size() &&
              fatherEdge != -1 && 
              value[fatherEdge] > 0 && 
              value[a[(int)a.size() - 1] - 'A'] > 0 && 
              value[b[(int)b.size() - 1] - 'A'] > 0);


  if(ok){
    root->dfsCnt++;
  }

  /*
  if( value['D' - 'A'] == 7 && 
      value['E' - 'A'] == 5 && 
      value['Y' - 'A'] == 2 && 
      value['N' - 'A'] == 6 && 
      value['R' - 'A'] == 8 &&
      value['O' - 'A'] == 0 &&
      value['S' - 'A'] == 9 &&
      true){
    //printf("debug %d %c\n",root,fatherEdge + 'A');
   // printf("info %d %d %d %d %d %d => %d\n",carry,pos,fatherEdge,value[fatherEdge],value[a[(int)a.size() - 1] - 'A'],value[b[(int)b.size() - 1] - 'A'],ok);
    //printf("counts are %d %d\n",root->cnt,root->dfsCnt);
  }
  */
  bool needA = (pos < (int)a.size() && value[a[pos] - 'A'] == -1);
  bool needB = (pos < (int)b.size() && value[b[pos] - 'A'] == -1 && a[pos] != b[pos]);

  for(int i = 0;i < (needA ? DIGITS:1);i++){
    if(needA && inv[i] != -1){
      continue;
    }
    if(needA){
      value[a[pos] - 'A'] = i;
      inv[i] = a[pos] - 'A';
    }
    for(int j = 0;j < (needB ? DIGITS:1);j++){
      if(needB && inv[j] != -1){
        continue;
      }
      if(needB){
        value[b[pos] - 'A'] = j;
        inv[j] = b[pos] - 'A';
      }
      int sum = (pos < (int)a.size() ? value[a[pos] - 'A']:0) + (pos < (int)b.size() ? value[b[pos] - 'A']:0) + carry;
      if(inv[sum % 10] != -1){
        dfs(a,b,root->sons[inv[sum % 10]],pos + 1,sum / 10,inv[sum % 10]); 
      }else{
        for(int it = 0;it < SIGMA;it++){
          if(value[it] != -1 || root->sons[it] == NULL){
            continue;
          }
          value[it] = sum % 10;
          inv[sum % 10] = it;
          dfs(a,b,root->sons[it],pos + 1,sum / 10,it);
          inv[sum % 10] = -1;
          value[it] = -1;
        }
      }
      if(needB){
        value[b[pos] - 'A'] = -1;
        inv[j] = -1;
      }
    }
    if(needA){
      value[a[pos] - 'A'] = -1;
      inv[i] = -1;
    }
  }
  return ;
}

vector<node_t *> nodes;
void getStrings(node_t *root){
  if(root == NULL){
    return ;
  }

  if(root->dfsCnt == 1 && root->cnt > 0){
    nodes.push_back(root);
  }
  
  for(int i = 0;i < SIGMA;i++){
    getStrings(root->sons[i]);
  }
}


bool cmp(node_t *a,node_t *b){
  return a->index < b->index;
}

int main(){

    for(int i = 0;i < SIGMA;i++){
      value[i] = -1;
    }
    for(int i = 0;i < DIGITS;i++){
      inv[i] = -1;
    }

    node_t* root = new node_t();

    int n;
    string a,b,s;
    cin >> a >> b;
  
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());

    cin >> n;

    while(n--){
      cin >> s;
      reverse(s.begin(),s.end());
      ins(root,s,0);
    }
    
    dfs(a,b,root,0,0,-1);
    getStrings(root);
    cout << (int)nodes.size() << "\n";
    sort(nodes.begin(),nodes.end(),cmp);
    for(auto it:nodes){
      while(it != root){
        cout << (char)(it->fatherEdge + 'A');
        it = it->father;
      }
      cout << "\n";
    }

    return 0;
}
