#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f =fopen("mst.in","r");
FILE *g =fopen("mst.out","w");
const double eps = 1e-9;
int N,M;
struct Edge{
    int u,v,a,b,c;
    double operator () (const double &t){
        return (double)1 * a * t * t + (double)1 * b * t + c;
    }
    vector<double> roots(){
        if(a != 0){
            long long delta = 1LL * b * b - 4LL * a * c;
            if(delta < 0){
                return {};
            }
            if(delta == 0){
                return {-b / ((double)2 * a)};
            }
            return {((double)(-b - sqrt((double)delta))) / (2 * a),((double)(-b + sqrt((double)delta))) / (2 * a)};
        }
        if(b != 0){
            return {-(double)c / b};
        }
        return {};
    }
    Edge combine(const Edge &other){
        Edge tmp;
        tmp.u = u;
        tmp.v = v;
        tmp.a = a - other.a;
        tmp.b = b - other.b;
        tmp.c = c - other.c;
        return tmp;
    }
    vector<double> sect(const Edge &other){
        return combine(other).roots();
    }
}E[105];
struct DSU{
    int T[105];
    void Reset(){
        for(int i = 0;i <= 100;i++){
            T[i] = -1;
        }
    }
    int Find(int x){
        if(T[x] < 0){
            return x;
        }
        return T[x] = Find(T[x]);
    }
    bool Union(int x,int y){
        x = Find(x);
        y = Find(y);
        if(x == y){
            return 0;
        }
        if(T[x] < T[y]){
            T[x] += T[y];
            T[y] = x;
        }
        else{
            T[y] += T[x];
            T[x] = y;
        }
        return 1;
    }
}APM_DSU;
int Time;
bool cmp(Edge a,Edge b){
    return a(Time) - b(Time) < -eps;
}
vector<double> changes;
vector<int> edges_for_apm(double tim){
    vector<int> ans;
    Time = tim;
    sort(E + 1,E + 1 + M,cmp);
    APM_DSU.Reset();
    for(int i = 1;i <= M;i++){
        if(APM_DSU.Union(E[i].u,E[i].v)){
            ans.push_back(i);
        }
    }
    return ans;
}
pair<double,double> time_cost_APM(double st,double dr){
    vector<int> tmp = edges_for_apm((st + dr) / 2);
    Edge func = {0,0,0,0,0};
    for(auto it:tmp){
        func.a += E[it].a;
        func.b += E[it].b;
        func.c += E[it].c;
    }
    return {-(double)func.b / (2 * func.a),func(-(double)func.b / (2 * func.a))};
}
int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i<= M;i++){
        fscanf(f,"%d %d %d %d %d",&E[i].u,&E[i].v,&E[i].a,&E[i].b,&E[i].c);
    }
    changes.push_back(-1e6);
    changes.push_back(1e6);
    for(int i = 1; i <= M;i++){
        for(int j = i;j <= M;j++){
            vector<double> tmp = (E[i].combine(E[j])).roots();
            for(auto it:tmp){
                changes.push_back(it);
            }
        }
    }
    sort(changes.begin(),changes.end());
    int len = 0;
    for(int i = 1;i < (int)changes.size();i++){
        if(changes[len] - changes[i] > eps || changes[len] - changes[i] < -eps){
            changes[++len] = changes[i];
        }
    }
    changes.resize(len + 1);
    pair<double,double> ans = {0,1e18};
    for(int i = 0;i < (int)changes.size() - 1;i++){
        pair<double,double> tmp = time_cost_APM(changes[i],changes[i + 1]);
        if(eps < ans.second - tmp.second){
            ans = tmp;
        }
    }
    fprintf(g,"%.9f %.9f",ans.first,ans.second);
    fclose(f);
    fclose(g);
    return 0;
}
