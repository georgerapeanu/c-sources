#include <bits/stdc++.h>

using namespace std;

vector<pair<long long,pair<long long,long long> > > ans;

long long add(long long a,long long b){
    ans.push_back({1,{a,b}});
    return a + b;
}

long long xo(long long a,long long b){
    ans.push_back({2,{a,b}});
    return a ^ b;
}

void answer(){
    printf("%d\n",(int)ans.size());
    for(auto it:ans){
        if(it.first == 1){
            printf("%lld + %lld\n",it.second.first,it.second.second);
        }
        else{
            printf("%lld ^ %lld\n",it.second.first,it.second.second);
        }
    }
    exit(0);
}

int main() {

    long long x;

    scanf("%lld",&x);

    long long tmp = x;

    for(int i = 1;(x >> i);i++){
        tmp = add(tmp,tmp);
    }

    tmp = xo(add(add(tmp,x),xo(tmp,x)),add(xo(tmp,x),xo(tmp,x)));

    long long new_x = x;

    for(int i = 1;(1LL << i) < tmp;i++){
        if((new_x >> i) & 1){
            new_x = add(x * (1LL << i),new_x);
        }
    }

    while(new_x != 1){
        if(new_x & tmp){
            new_x = xo(new_x,tmp);
        }
        tmp = add(tmp,tmp);
    }

    answer();

    return 0;
}
