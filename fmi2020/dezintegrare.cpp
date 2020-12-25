#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("dezintegrare.in","r");
FILE *g = fopen("dezintegrare.out","w");

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
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
    return ans * sgn;
}

long long i64(){
    long long ans = 0;
    int sgn = 1;


    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    if(buff[ind] == '-'){
        sgn *= -1;
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

    return ans * sgn;
}
struct line_t{
    int a;
    long long b;
    int id;

    bool operator < (const line_t &other){
        if(b != other.b){
            return b < other.b;
        }
        return a > other.a;
    }
};

const long double eps = 1e-6;
int sect(line_t &a,line_t &b,long long x){

    long double tmp =  (b.b - a.b) / ((long double)a.a - b.a) - x;
    if(tmp < -eps){
        return -1;
    }
    else if(tmp < eps){
        return 0;
    }
    else{
        return 1;
    }
}

bool bad(line_t &a,line_t &b,line_t &c){
    return (c.b - a.b) / ((long double)a.a - c.a) - (b.b - a.b) / ((long double)a.a - b.a) <= eps;
}

vector<line_t> lines;

int main(){

    int k,q;

    k = i32();
    q = i32();

    for(int i = 1;i <= k;i++){
        line_t tmp;
        tmp.b = i64();
        tmp.a = -i32();
        tmp.id = i;
        lines.push_back(tmp);
    }

    sort(lines.begin(),lines.end());

    vector<line_t> cht;

    for(auto it:lines){
        if(cht.empty() || cht.back().a > it.a){
            cht.push_back(it);
        }
    }

    lines = cht;

    cht.clear();

    for(auto it:lines){
        while((int)cht.size() > 1 && bad(cht[(int)cht.size() - 2],cht[(int)cht.size() - 1],it)){
            cht.pop_back();
        }
        cht.push_back(it);
    }

    while(q--){
        int t = i32();
        
        int pos = 0;

        if(cht.size() == 1 || sect(cht[0],cht[1],t) >= 0){
            pos = 0;
        }
        else{
            for(int h = 17;h >= 0;h--){
                int x = pos + (1 << h);
                if(x + 1 < (int)cht.size() && sect(cht[x],cht[x + 1],t) < 0){
                    pos = x;
                }
            }
            pos++;
        }

        fprintf(g,"%d\n",cht[pos].id);
    }

    fclose(f);
    fclose(g);

    return 0;
}
