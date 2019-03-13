#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

FILE *f = fopen("multimi4.in","r");
FILE *g = fopen("multimi4.out","w");

const int NMAX = 1e3;

int n;

bitset<1 << 16> nothing;
bitset<1 << 16> ini[16];///ini[x] = configuratiile din care e compusa multimea x inclusa {'A','B',...}

char tag[20];
int fst[20];
int snd[20];
int pas[20];
int remap[600];

int lst = 1;
int len;

vector< bitset<1 << 16> > s;

char c[NMAX + 5];

void expr(int id);
void uni(int id);
void inter(int id);

void expr(int id){
    if(id >= (int)s.size()){
        s.push_back(nothing);
    }

    uni(id + 1);
    s[id] = s[id + 1];

    while(lst <= len && c[lst] == '+'){
        lst++;
        uni(id + 1);
        s[id] |= s[id + 1];
    }
}

void uni(int id){
    if(id >= (int)s.size()){
        s.push_back(nothing);
    }

    inter(id + 1);
    s[id] = s[id + 1];

    while(lst <= len && c[lst] == '*'){
        lst++;
        inter(id + 1);
        s[id] &= s[id + 1];
    }
}

void inter(int id){
    if(id >= (int)s.size()){
        s.push_back(nothing);
    }

    if(lst > len){
        return ;
    }
    else if(c[lst] == '('){
        lst++;
        expr(id + 1);
        s[id] = s[id + 1];
        lst++;
    }
    else{
        s[id] = ini[remap[c[lst]]];
        lst++;
    }
}

int main(){
    fscanf(f,"%d\n",&n);

    for(int conf = 0;conf < (1 << n);conf++){
        for(int i = 0;i < n;i++){
            ini[i][conf] = ((conf >> i) & 1);
        }
    }

    vector<pair<int,int> > smecherie;

    for(int i = 0;i < n;i++){
        fscanf(f,"%c=%d-%d/%d\n",&tag[i],&fst[i],&snd[i],&pas[i]);
        remap[tag[i]] = i;
        for(int x = fst[i];x <= snd[i];x += pas[i]){
            smecherie.push_back({x,1 << i});
        }
    }

    sort(smecherie.begin(),smecherie.end());

    int l = 0;

    for(int i = 1;i < (int)smecherie.size();i++){
        if(smecherie[l].first != smecherie[i].first){
            smecherie[++l] = smecherie[i];
        }
        else{
            smecherie[l].second |= smecherie[i].second;
        }
    }

    smecherie.resize(l + 1);

    vector<pair<int,int> > mult;

    for(auto it:smecherie){
        mult.push_back({it.second,it.first});
    }

    sort(mult.begin(),mult.end());

    fgets(c + 1,NMAX + 5,f);

    len = strlen(c + 1);
    len -= (c[len] == '\n');

    expr(1);

    int lst = 0;

    vector<int> ans;

    for(int i = 0;i < (1 << n);i++){
        if(s[1][i] == 1){
            while(lst < (int)mult.size() && mult[lst].first < i){
                lst++;
            }
            while(lst < (int)mult.size() && mult[lst].first == i){
                ans.push_back(mult[lst].second);
                lst++;
            }
        }
    }

    sort(ans.begin(),ans.end());

    fprintf(g,"%d\n",ans.size());

    for(auto it:ans){
        fprintf(g,"%d ",it);
    }

    return 0;
}
