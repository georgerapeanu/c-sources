#include "icc.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

const int NMAX = 1e2;

vector<vector<int>> components;
int label[NMAX + 5];

int a[NMAX + 5],len_a;
int b[NMAX + 5],len_b;
int lg2[NMAX + 5];

int my_query(vector<int> &c1,vector<int> &c2) {
    len_a = 0;
    for(auto it:c1) {
        a[len_a++] = it;
    }

    len_b = 0;
    for(auto it:c2) {
        b[len_b++] = it;
    }

    if(len_a == 0 || len_b == 0) {
        return 0;
    }

    return query(len_a,len_b,a,b);
}

void run(int n) {
    lg2[0] = -1;
    for(int i = 1; i <= n; i++) {
        lg2[i] = 1 + lg2[i >> 1];
        components.push_back({i});
    }
    for(int t = 1; t < n; t++) {
        int last_comp_bit = lg2[(int)components.size() - 1];
        for(int x = 0; x < (int)components.size(); x++) {
            for(int i = 0; i < (int)components[x].size(); i++) {
                label[components[x][i]] = x;
            }
        }

        int m1 = 0;
        int m2 = 0;
        int xo = 0;

        for(int b = 0; b <= last_comp_bit; b++) {
            vector<int> v1,v2;
            for(int i = 1; i <= n; i++) {
                if((label[i] >> b) & 1) {
                    v1.push_back(i);
                }
                else {
                    v2.push_back(i);
                }
            }

            xo |= my_query(v1,v2) << b;
        }

        int pos = 0;

        for(int b = 0; b <= last_comp_bit; b++) {
            if((xo >> b) & 1) {
                m1 = 1 << b;
                pos = b;
                break;
            }
        }

        for(int b = 0; b <= last_comp_bit; b++) {
            if(b == pos) {
                continue;
            }
            m2 |= ((((xo >> b) & 1)) << b);

            vector<int> v1,v2;

            for(int i = 1; i <= n; i++) {
                if(((label[i] >> pos) & 1) == 1 && (((1 << (b + 1)) - 1) & label[i]) == (((1 << (b + 1)) - 1) & m1)) {
                    v1.push_back(i);
                }
                else if(((label[i] >> pos) & 1) == 0 && (((1 << (b + 1)) - 1) & label[i]) == (((1 << (b + 1)) - 1) & m2)) {
                    v2.push_back(i);
                }
            }

            if(my_query(v1,v2) == 0) {
                m1 ^= (1 << b);
                m2 ^= (1 << b);
            }
        }

        int fst_comp = m1;
        int snd_comp = m2;

        int st1 = -1,dr1 = (int)components[fst_comp].size() - 1;
        while(dr1 - st1 > 1) {
            int mid1 = (st1 + dr1) / 2;
            vector<int> v;
            for(int i = 0; i <= mid1; i++) {
                v.push_back(components[fst_comp][i]);
            }

            if(my_query(v,components[snd_comp]) == 0) {
                st1 = mid1;
            }
            else {
                dr1 = mid1;
            }
        }

        int st2 = -1,dr2 = (int)components[snd_comp].size() - 1;
        while(dr2 - st2 > 1) {
            int mid2 = (st2 + dr2) / 2;
            vector<int> v;
            for(int i = 0; i <= mid2; i++) {
                v.push_back(components[snd_comp][i]);
            }

            if(my_query(v,components[fst_comp]) == 0) {
                st2 = mid2;
            }
            else {
                dr2 = mid2;
            }
        }

        int u = components[fst_comp][dr1];
        int v = components[snd_comp][dr2];

        setRoad(u,v);

        for(auto it:components[fst_comp]) {
            components[snd_comp].push_back(it);
        }
        swap(components[fst_comp],components.back());
        components.pop_back();
    }
}
