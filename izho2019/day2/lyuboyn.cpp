#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,k,t,fst;
vector<int> v;
string s;

int main(){
    

    cin >> n >> k >> t;
    cin >> s;

    reverse(s.begin(),s.end());

    for(auto it:s){
        fst = fst * 2 + it - '0';
    }

    if(k % 2 == 0){
        printf("-1");
        return 0;
    }

    printf("%d\n",(1 << n));

    int _n = 2;
    int _k = 1;
    v = {0,1,3,2};

    while(_k < k){
        vector<int> nv;
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(v[i] ^ ((i % 2 == 0 ? 0:3) << _n));
        }
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(((1 << _n) - 1) ^ v[(1 << _n) - 1 - i] ^ ((i % 2 == 0 ? 2:1) << _n));
        }
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(v[i] ^ ((i % 2 == 0 ? 3:0) << _n));
        }
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(((1 << _n) - 1) ^ v[(1 << _n) - 1 - i] ^ ((i % 2 == 0 ? 1:2) << _n));
        }

        _k += 2;
        _n += 2;
        v = nv;
    }
    
    while(_n < n){
        vector<int> nv;
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(v[i]);
        }
        for(int i = 0;i < (1 << _n);i++){
            nv.push_back(v[i] ^ (1 << _n));
        }
        for(int h = 0;h < _n;h++){
            if(((v[0] >> h) & 1) != ((v[(1 << _n) - 1] >> h) & 1)){
                for(int i = (1 << _n);i < (2 << _n);i++){
                    nv[i] ^= (1 << h);
                }
                break;
            }
        }
        _n++;
        v = nv;
    }

/*
    for(int i = 0;i < (1 << n);i++){
        printf("%d ",__builtin_popcount(v[i] ^ v[(i + 1) & ((1 << n) - 1)]));
    }
    printf("\n");
*/
    for(int i = 0;i < (1 << n);i++){
        v[i] ^= fst;
        for(int h = 0;h < n;h++){
            printf("%d",((v[i] >> h)) & 1);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

