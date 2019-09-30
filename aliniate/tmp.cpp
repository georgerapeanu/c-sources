#include<cstdio>
#include<algorithm>
#include<vector>
#define op operator
#define rt return
using namespace std;
FILE*f=fopen("aliniate.in","r");
FILE*g=fopen("aliniate.out","w");
typedef unsigned int ui;
const ui LGMAX=32;
int t,n;
const int d=1<<15;
char c[d];
int p=d-1;
ui u32() {
    ui e=0;
    while(c[p]<'0'||c[p]>'9') {
        if(++p>=d) {
            p=0;
            fread(c,1,d,f);
        }
    }
    while(c[p]>='0'&&c[p]<='9') {
        e=e*10+(c[p]-'0');
        if(++p>=d) {
            p=0;
            fread(c,1,d,f);
        }
    }
    rt e;
}
inline ui trail(ui o) {
    if(o==0) {
        rt LGMAX;
    }
    ui e=0;
    while(o%2==0) {
        o>>=1;
        e++;
    }
    rt e;
}
struct b {
    ui o;
    bool h;
    b() {
        o=1;
        h=true;
    } b(ui o) {
        this->o=o;
        this->h=false;
    } b op*(const b&other)const {
        b e;
        e.o=this->o*other.o;
        e.h=(this->h|other.h);
        rt e;
    } bool op==(const b&other)const {
        rt this->o==other.o;
    } bool op!=(const b&other)const {
        rt this->o!=other.o;
    } bool can_tre(const b&other)const {
        if(this->h) {
            rt trail(this->o)<=trail(other.o);
        }
        rt this->o==other.o;
    } bool op<(const b&other)const {
        rt this->h<other.h;
        if(this->o!=other.o) {
            rt this->o<other.o;
        }
    }
};
vector<pair<ui,b>>a[LGMAX+1];
int main() {
    t=u32();
    while(t--) {
        for(ui h=0; h<=LGMAX; h++) {
            a[h].clear();
        }
        n=u32();
        bool ok=true;
        for(int i=1; i<=n; i++) {
            ui x,y,z;
            x=u32();
            y=u32();
            z=u32();
            a[trail(y-x+1)].push_back({x,b(z)});
        }
        for(ui h=0; h<LGMAX; h++) {
            sort(a[h].begin(),a[h].end());
            int len=1;
            for(int i=1; i<(int)a[h].size(); i++) {
                if(a[h][len-1].first!=a[h][i].first) {
                    a[h][len++]=a[h][i];
                }
                if(a[h][i].second.can_tre(a[h][len-1].second)==false) {
                    ok=false;
                    goto done1;
                }
            }
            a[h].resize(len);
            for(int i=0; i<(int)a[h].size(); i++) {
                if((a[h][i].first>>h)&1) {
                    if(i!=0&&a[h][i].first-a[h][i-1].first==(((ui)1)<<h)) {
                        a[h+1].push_back({a[h][i].first-((ui)1<<h),a[h][i-1].second*a[h][i].second});
                    }
                    else {
                        a[h+1].push_back({a[h][i].first-((ui)1<<h),b()*a[h][i].second});
                    }
                }
                else {
                    if(i<(int)a[h].size()-1&&a[h][i+1].first-a[h][i].first==(((ui)1)<<h)) {
                        a[h+1].push_back({a[h][i].first,a[h][i].second*a[h][i+1].second});
                    }
                    else {
                        a[h+1].push_back({a[h][i].first,a[h][i].second*b()});
                    }
                }
            }
        }
done1:
        ;
        fprintf(g,"%d\n",ok);
    }
    fclose(f);
    fclose(g);
    rt 0;
}
