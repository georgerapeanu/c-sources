#include <cstdio>
#include <cstring>
#include <chrono>
#include <random>
#include <cstdlib>
#include <algorithm>

using namespace std;

FILE *f = fopen("congr.in","r");
FILE *g = fopen("congr.out","w");

const int NMAX = 3e5;

int p;
pair<int,int> v[2 * NMAX + 5];
int sum;

inline int add(int a,int b){
    a += b;
    if(a >= p){
        a -= p;
    }
    return a;
}

inline int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += p;
    }
    return a;
}

const int LEN = 1 << 14;
char buff[LEN];
int ind;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    p = i32();

    for(int i = 1;i < 2 * p;i++){
        v[i].first = i32();
        v[i].first %= p;
        v[i].second = i;
        if(i <= p){
            sum = add(sum,v[i].first);
        }
    }

    while(true){
        int x = gen() % p + 1;
        int y = p + 1 + (gen() % (p - 1));

        sum = add(sum,v[y].first);
        sum = scad(sum,v[x].first);

        swap(v[x],v[y]);

        if(sum == 0){
            for(int j = 1;j <= p;j++){
                fprintf(g,"%d ",v[j].second);
            }
            return 0;
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
