#include <iostream>
#include <algorithm>
using namespace std;
int N;
long long rez;
bool valid(int a,int b,int c){
    if(c < b || c > N){
        return 0;
    }
    return c < a + b;
}
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        for(int j = i;j <= N;j++){
            if(valid(i,j,i ^j)){
                rez++;
            }
        }
    }
    cout << rez;
    return 0;
}
