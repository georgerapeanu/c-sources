#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000;

int main() {

    int n;
    string s;

    while(cin >> n){
        cin >> s;

        set<int> s0,s2;

        for(int i = 0;i < n;i++){
            if(s[i] == '0'){
                s0.insert(i + 1);
            }
            else if(s[i] == '2'){
                s2.insert(i + 1);
            }
        }

        int st = 0,dr = (int)s.size() / 4 + 1;

        while(dr - st > 1){
            int mid = (st + dr) / 2;
            vector<int> tmp(mid,0);
            set<int> :: iterator it0 = s0.begin(); 
            set<int> :: iterator it2 = s2.begin(); 
            for(int i = 0;i < mid;i++){
                while(it2 != s2.end() && *it2 <= tmp[i]){
                    it2++;
                }
                if(it2 == s2.end()){
                    dr = mid;
                    goto done;
                }
                tmp[i] = *it2;
                it2++;
            }
            for(int i = 0;i < mid;i++){
                while(it0 != s0.end() && *it0 <= tmp[i]){
                    it0++;
                }
                if(it0 == s0.end()){
                    dr = mid;
                    goto done;
                }
                tmp[i] = *it0;
                it0++;
            }
            for(int i = 0;i < mid;i++){
                while(it2 != s2.end() && *it2 <= tmp[i]){
                    it2++;
                }
                if(it2 == s2.end()){
                    dr = mid;
                    goto done;
                }
                tmp[i] = *it2;
                it2++;
            }
            for(int i = 0;i < mid;i++){
                while(it0 != s0.end() && *it0 <= tmp[i]){
                    it0++;
                }
                if(it0 == s0.end()){
                    dr = mid;
                    goto done;
                }
                tmp[i] = *it0;
                it0++;
            }

            st = mid;
            done:;
        }
        printf("%d\n",st);
    }


    return 0;
}
