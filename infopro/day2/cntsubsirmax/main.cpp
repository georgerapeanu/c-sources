#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e6;
const int MOD = 1e9 + 7;

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int scad(int a,int b){
    a -= b;

    if(a < 0){
        a += MOD;
    }

    return a;
}

struct stack_t{
    int sum = 0;
    vector<pair<int,int> > v;

    void push(int val,int weight){
        v.push_back({val,weight});
        if((int)v.size() > 1){
            v[(int)v.size() - 1].second = add(v[(int)v.size() - 1].second,v[(int)v.size() - 2].second);
        }
        sum = add(sum,v.back().second);
    }

    void pop(){
        sum = scad(sum,v.back().second);
        v.pop_back();
    }

    pair<int,int> top(){
        return v.back();
    }

    bool empty(){
        return v.empty();
    }

    int size(){
        return v.size();
    }

    int answer(){
        return sum;
    }
};

char s[NMAX + 5];

int main(){

    freopen("cntsubsirmax.in","r",stdin);
    freopen("cntsubsirmax.out","w",stdout);
   
    fgets(s + 1,NMAX + 4,stdin);

    stack_t solver;

    int ans = 0;

    for(int i = 1;s[i] != '\0' && s[i] != '\n';i++){
        while(!solver.empty() && s[solver.top().first] < s[i]){
            solver.pop();
        }
        solver.push(i,i - (solver.empty() ? 0:solver.top().first));
        ans = add(ans,solver.answer());
    }

    printf("%d\n",ans);

    return 0;
}
