#include <bits/stdc++.h>

using namespace std;


const int inf = 1e9;

/// n obiecte
///weight[i],value[i]
///pentru un w valoarea maxima daca furam obiecte cu fix greutatea w

int n,w;

///dp[i][weight] = valoarea maxima posibile considerand primele i obiecte daca stim ca suma greutatilor lor e weight
int a[100];
int dp[100][100];

int main(){

    for(int weight = 0;weight <= w;weight++){
        dp[0][weight] = -inf;
    }

    dp[0][0] = 0;

    for(int i = 1;i <= n;i++){
        for(int weight = 0;weight <= w;weight++){
            dp[i][weight] = -inf;
            dp[i][weight] = max(dp[i][weight],dp[i - 1][weight]);
            if(weight >= a[i]){
                dp[i][weight] = max(dp[i][weight],dp[i - 1][weight - a[i]]);
            }
        }
    }

    printf("%d\n",dp[n][w]);

    return 0;
}
