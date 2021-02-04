//
//  main.cpp
//  dp rucsac rucsac
//
//  Created by Diana H on 10/01/2021.
//

#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("rucsac.in");
ofstream fout("rucsac.out");
 
/// n obiecte cu val 1 si weight citit 
///
///val maxima daca luam obiecte cu fix greutatea w
 
int n,w;
 
///dp[i][weight] = val maxima posibila considerand primele i obiecte daca stim ca suma greutatilor lor e weight
int a[5005];
int b[5005];

int dp[10005];
 
int main(){
 
    fin >> n >> w;
    for( int i=1; i<=n; i++)
        fin >> a[i] >> b[i]; //greutatile
   
    for(int i = 1;i <= n;i++){
        for(int weight = w; weight >= 0; weight--)
        {
            if(weight >= a[i])
            {
                dp[weight] = max(dp[weight - a[i]] + b[i], dp[weight]);
                
            }
        }
    }
 
    fout << (dp[w]);
 
    return 0;
}


