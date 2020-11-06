#include "mushrooms.h"
#include <cstdio>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

const int TARGET = 141;

int count_mushrooms(int n) {

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> stuff[2];
    stuff[0] = {0};

    vector<int> order;

    for(int i = 1;i < n;i++){
        order.push_back(i);
    }

    shuffle(order.begin(),order.end(),gen);

    if(n <= 226){
        int ans = 1;
        for(int i = 1;i < n;i++){
            ans += (use_machine({0,i}) == 0);
        }
        return ans;
    }

    for(int i = 0;stuff[0].size() < 2 && stuff[1].size() < 2;i++){
        stuff[use_machine({0,order.back()})].push_back(order.back());
        order.pop_back();
    }

    while((int)stuff[0].size() < TARGET && (int)stuff[1].size() < TARGET && (int)order.size() > 1){
        if((int)stuff[0].size() > 1){
            int a = order.back();order.pop_back();
            int b = order.back();order.pop_back();
            int tmp = use_machine({stuff[0][0],a,stuff[0][1],b});
            stuff[tmp % 2].push_back(b);
            stuff[tmp / 2].push_back(a);
        }
        else{
            int a = order.back();order.pop_back();
            int b = order.back();order.pop_back();
            int tmp = use_machine({stuff[1][0],a,stuff[1][1],b});
            stuff[1 - (tmp % 2)].push_back(b);
            stuff[1 - (tmp / 2)].push_back(a);
        }
    }

    if(order.size() == 1){
        return (int)stuff[0].size() + (use_machine({0,order[0]}) == 0);
    }

    if(order.size() == 0){
        return stuff[0].size();
    }

    int ans = stuff[0].size();

    while((int)order.size() > 0){
        int cnt = min(order.size(),max(stuff[0].size(),stuff[1].size()));
        vector<int> tmp;
        if(stuff[0].size() > stuff[1].size()){
            for(int i = 0;i < cnt;i++){
                tmp.push_back(stuff[0][i]);
                tmp.push_back(order[(int)order.size() - 1 - i]);
            }
            int aux = use_machine(tmp);
            ans += cnt - ((aux / 2) + (aux % 2));
            stuff[aux % 2].push_back(tmp.back());
        }
        else{
            for(int i = 0;i < cnt;i++){
                tmp.push_back(stuff[1][i]);
                tmp.push_back(order[(int)order.size() - 1 - i]);
            }
            int aux = use_machine(tmp);
            ans += ((aux / 2) + (aux % 2));
            stuff[1 - (aux % 2)].push_back(tmp.back());
        }
        for(int i = 0;i < cnt;i++){
            order.pop_back();
        }
    }

    return ans;
}
