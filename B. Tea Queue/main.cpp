#include <iostream>
#include <algorithm>
using namespace std;
struct data{
    int l,r,id;
    bool operator < (const data &other)const{
        if(l != other.l){
            return l < other.l;
        }
        return id < other.id;
    }
}V[1005];
int R[1005];
int T;
int N;
int main()
{
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 1;i <= N;i++){
            cin >> V[i].l >> V[i].r;
            V[i].id = i;
        }
        int st = 1;
        int num0 = 0;
        for(int i = 1;i <= N;i++){
            while(st < i && R[st]  < V[i].l){
                num0 -= (R[st] == 0);
                st++;
            }
            if((i - st) - num0 + V[i].l > V[i].r){
                R[V[i].id] = 0;
                num0++;
            }
            else{
                R[V[i].id] = (i - st) - num0 + V[i].l ;
            }
        }
        for(int i = 1;i <= N;i++){
            cout << R[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
