#include "permutation.h"
#pragma once
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[2][300][300];
pair<int,pair<int,int> > ant[300][300][300];

void solve(int n) {
    memset(dp,0,sizeof(dp));
    memset(ant,0,sizeof(ant));
    vector<int> a(n,0);
    vector<int> perm;
    vector<int> sums;

    for(int i = 1;i <= n;i++){
        perm.push_back(i);
    }

    int total_sum = 0;

    for(int i = 1;i <= n;i++){
        sums.push_back(query(perm));
        total_sum += sums.back();
        int tmp = perm[0];
        for(int i = 0;i < n - 1;i++){
            perm[i] = perm[i + 1];
        }
        perm[n - 1] = tmp;
    }

    for(int i = 0;i < n;i++){
        a[(n + i - 1) % n] = total_sum / (n - 1) - sums[i];
    }

    dp[0][0][0] = 1;

    /*for(auto it:a){
        printf("%d ",it);
    }

    printf("\n");
*/
    for(int i = 0,l = 0;i < n - 1;i++,l ^= 1){
        memset(dp[l ^ 1],0,sizeof(dp[l ^ 1]));
        for(int dmin = 0;dmin <= n;dmin++){
            for(int delta = 0;delta <= n;delta++){
                if(dp[l][dmin][delta] == false)continue;
  //              printf("enter %d %d %d\n",i,dmin,delta);
                if(delta + max(0,a[i] - dmin) < n && ant[i + 1][max(0,dmin - a[i])][delta + max(0,a[i] - dmin)].first == 0){
    //                printf("trans %d %d %d\n",i + 1,max(0,dmin - a[i]),delta + max(0,a[i] - dmin));
                    dp[l ^ 1][max(0,dmin - a[i])][delta + max(0,a[i] - dmin)] = true;
                    ant[i + 1][max(0,dmin - a[i])][delta + max(0,a[i] - dmin)] = {-1,{dmin,delta}};
                }
                if(dmin + a[i] < n && ant[i + 1][dmin + a[i]][max(delta,dmin + a[i])].first == 0){
      //              printf("trans %d %d %d\n",i + 1,max(0,dmin + a[i]),max(delta,a[i] + dmin));
                    ant[i + 1][dmin + a[i]][max(delta,dmin + a[i])] = {+1,{dmin,delta}};
                    dp[l ^ 1][dmin + a[i]][max(delta,a[i] + dmin)] = true;
                }
            }
        }
    }

    for(int i = 0;i < n;i++){
        if(dp[(n - 1) & 1][i][n - 1] == true){
            vector<int> candidate = {};
            int x = n - 1;
            int y = i;
            int z = n - 1;
        //    printf("yuss %d %d %d\n",x,y,z);
            while(x > 0){
                candidate.push_back(a[x - 1] * ant[x][y][z].first);
                int yy = ant[x][y][z].second.first;
                int zz = ant[x][y][z].second.second;
                x--;
                y = yy;
                z = zz;
            }
            candidate.push_back(0);
            reverse(candidate.begin(),candidate.end());
            int mi = candidate[0];
            for(int i = 1;i < (int)candidate.size();i++){
                candidate[i] += candidate[i - 1];
                mi = min(mi,candidate[i]);
            }
            for(auto &it:candidate){
                it = it - mi + 1;
            }
            bool ok = (abs(candidate[n - 1] - candidate[0]) == a[n - 1]);
            vector<int> tmp = candidate;
            sort(tmp.begin(),tmp.end());

            for(int i = 0;i < n;i++){
                ok &= (tmp[i] == i + 1);
            }

            if(ok){
          //      for(auto it:candidate)printf("%d ",it);printf("\n");
                answer(candidate);
                return ;
            }
        }
    }
    answer(a);
}
