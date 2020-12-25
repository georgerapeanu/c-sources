#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

int n;
char s[2000005];
int dq[2000005];
int sums[2000005];
int stq = 1,drq = 0;

int main(){

    scanf("%d\n",&n);
    scanf("%s",s);

    int l = 0,r = 0;

    dq[++drq] = 0;
    
    sums[0] = 0;

    for(int i = 0;i < n;i++){
        if(s[i] == 'P'){
            l++;
            while(drq - stq + 1 > 0 && dq[stq] < l){
                stq++;
            }
        }
        else{
            r++;
            sums[r] = (sums[r - 1] + (s[i] == '(' ? 1:-1));
            while(drq - stq + 1 > 0 && sums[dq[drq]] >= sums[r]){
                drq--;
            }
            dq[++drq] = r;
        }
        if(l >= r || sums[l] == sums[r] && sums[dq[stq]] >= sums[l]){
            printf("1");
        }
        else{
            printf("0");
        }
    }

    return 0;
}
