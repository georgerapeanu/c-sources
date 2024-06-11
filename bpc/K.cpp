#include <bits/stdc++.h>
#define SIGMA (('z' - 'a' + 1) + ('Z' - 'A' + 1) + 1) 
using namespace std;

int CH(char x) {
  if('a' <= x && x <= 'z') {
    return x - 'a';
  }
  if('A' <= x && x <= 'Z') {
    return ('z' - 'a' + 1) + x - 'A';
  }
  assert(x == ' ');
  return ('z' - 'a' + 1) + ('Z' - 'A' + 1);
}

struct tn
{
    int n0;
    vector<int> cuv;
    tn *fiu[SIGMA],*fail;
    tn()
    {
        memset(fiu,0,sizeof(fiu));
        fail=0;
        n0=0;
    }
};
void ins(tn *t,const char *c,int nr)
{
    if(*c=='\n' || *c == 0)
    {
        t->cuv.push_back(nr);
        return ;
    }
    if(!t->fiu[CH(*c)]) t->fiu[CH(*c)]=new tn;
    ins(t->fiu[CH(*c)],c+1,nr);
}
tn *q[1000005];
int st=0,dr=0;
int rez[200005];
tn *T;
void bfs()
{
    T->fail=T;
    q[st]=T;
    tn *a,*fr;
    while(st<=dr)
    {
        fr=q[st++];
        for(int i=0;i<SIGMA;i++)
        {
            if(fr->fiu[i]==0) continue;
            a=fr->fail;
            while(a!=T&&a->fiu[i]==0)
                a=a->fail;
            if(a->fiu[i]!=0&&a->fiu[i]!=fr->fiu[i]) a=a->fiu[i];
            fr->fiu[i]->fail=a;
            q[++dr]=fr->fiu[i];
        }
    }
    T->fail=0;
}
void antibfs()
{
    for(int i=dr;i>0;i--)
    {
        if(q[i]->fail!=0) q[i]->fail->n0+=q[i]->n0;
        for(auto it:q[i]->cuv)
            rez[it]=q[i]->n0;
    }
}

pair<string, int> get_normalized_string(const string& s) {
    istringstream tmp(s);
    int count = 0;
    string answer, word;

    while(tmp >> word) {
      count += 1;
      if(count > 1) {
        answer += " ";
      }
      answer += word;
    }
    return {answer, count};
}

int main()
{
    T=new tn;
    int n;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin.get();
  
    vector<int> cost(n + 1);
    for(int i=1;i<=n;i++)
    {
      string pattern;
      getline(cin, pattern);
      auto tmp = get_normalized_string(pattern);
      cost[i] = tmp.second;
      ins(T, tmp.first.c_str(), i);
    }
    bfs();
    tn *tmp=T;
    string text;
    getline(cin, text);
    text = get_normalized_string(text).first;
    for(int i=0; i < (int)text.size();i++)
    {
        while(tmp!=T&&tmp->fiu[CH(text[i])]==0)
            tmp=tmp->fail;
        if(tmp->fiu[CH(text[i])]!=0)tmp=tmp->fiu[CH(text[i])];
        tmp->n0++;
    }
    antibfs();
    long long sum = 0;
    for(int i=1;i<=n;i++) {
      sum += 1LL * rez[i] * cost[i];
    }
    cout << sum << "\n";
    return 0;
}
