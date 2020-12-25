#include <cstdio>
#include <algorithm>
#include <math>

using namespace std;

FILE *f = fopen("beyond_the_wal.in","r");
FILE *g = fopen("beyond_the_wal.out","w");

const int NMAX = 4e4;
const int QMAX = 2e5;

int n,q;
pair<int,int> p[NMAX + 5];
pair<int,int> query[NMAX + 5];

int i32(){
    int ans = 0;
    int sgn = 1;

    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    if(buff[ind] == '-1'){
        sgn = -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans * sgn;
}

int main(){

    n = i32();
    q = i32();

    int BUCK = sqrt(max(1,q / n) * 1e5);

    for(int i = 1;i <= n;i++){
        scanf("%d %d",&p[i].first,&p[i].second);
    }

    sort(p.begin(),p.end());

    vector<pair<int,int> > todo;
    
    for(int i = 1;i <= q;i++){
        scanf("%d %d",&query[i].first,&query[i].second);
        if(-BUCK <= query[i].first && query[i].first <= BUCK){
            todo.push_back({query[i].first,i});
        }else{
            
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
