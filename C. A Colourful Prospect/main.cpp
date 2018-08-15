#include <iostream>
#include <algorithm>
using namespace std;
int N;
int rez = 0;
struct cerc{
    int x,y,r;
    bool operator < (const cerc &other)const{
        if(x != other.x){
            return x < other.x;
        }
        if(y != other.y){
            return y < other.y;
        }
        return r < other.r;
    }
}V[4];
struct punct{
    double x,y;
};
bool cmp(cerc a,cerc b){
    return a.r < b.r;
}
int sq(int val){
    return val * val;
}
int dist(cerc a,cerc b){
    return sq(a.x - b.x) + sq(a.y - b.y);
}
bool incl(cerc a,cerc b){
    return dist(a,b) <= b.r - a.r;
}
bool in(cerc a,double x,double y){
    return ((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y) <= a.r * a.r);
}
bool ok(vector<cerc> tmp){
    if((int)tmp.size() <= 1){
        return 1;
    }
    sort(tmp.begin(),tmp.end(),cmp);
    for(int i = 0;i < (int)tmp.size();i++){
        for(int j = i + 1;j < (int)tmp.size();j++){
            if(incl(tmp[i],tmp[j]) || incl(tmp[j],tmp[i])){
                return 0;
            }
        }
    }
    if((int)tmp.size() == 2){
        return dist(tmp[0],tmp[1]) < sq(tmp[0].r + tmp[1].r);
    }
    cerc a = tmp[0];
    cerc b = tmp[1];
    cerc c = tmp[2];
    if(!(sq(c.r - b.r) <= dist(b,c) && dist(b,c) <= sq(c.r + b.r))){
        return 0;
    }
    if(!(sq(c.r - a.r) <= dist(a,c) && dist(a,c) <= sq(c.r + a.r))){
        return 0;
    }
    if(!(sq(b.r - a.r) <= dist(b,a) && dist(b,a) <= sq(b.r + a.r))){
        return 0;
    }
    const double eps = 1e-2;
    bool founda = 0;
    bool foundb = 0;
    bool foundc = 0;
    for(double x = min(a.x,min(b.x,c.x)) - c.r;x <= max(a.x,max(b.x,c.x)) + c.r && (!founda || !foundb || !foundc);x += eps){
        for(double y = min(a.y,min(b.y,c.y)) - c.r;y <= max(a.y,max(b.y,c.y)) + c.r && (!founda || !foundb || !foundc);y += eps){
            int tmpa = in(a,x,y);
            int tmpb = in(b,x,y);
            int tmpc = in(c,x,y);
            if(tmpa && tmpb && !tmpc){
                foundc = 1;
            }
            if(tmpa && !tmpb && tmpc){
                foundb = 1;
            }
            if(!tmpa && tmpb && tmpc){
                founda = 1;
            }
        }
    }
    if(!founda | !foundb || !foundc){
        return 0;
    }
    return 1;
}
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i].x >> V[i].y >> V[i].r;
    }
    sort(V + 1,V + 1 + N);
    for(int conf = 0;conf < (1 << N);conf++){
        vector<cerc> tmp;
        for(int i = 0;i < N;i++){
            if((conf >> i) & 1){
                tmp.push_back(V[i + 1]);
            }
        }
        if(ok(tmp)){
            rez++;
        }
    }
    cout << rez;
    return 0;
}
