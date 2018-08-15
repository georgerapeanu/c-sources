#include <iostream>
#include <algorithm>
using namespace std;
int N;
int V[1005];
int rez = - ( 1<< 30);
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        if(V[i] >= 0 && ((int)sqrt(V[i])) * ((int)sqrt(V[i])) == V[i]){
            ;
        }
        else {
            rez = max(rez,V[i]);
        }
    }
    cout << rez;
    return 0;
}
