#include <iostream>
#include <algorithm>
using namespace std;
int N;
long long sum;
string a;
int toInt(){
    int rez = 0;
    for(auto it:a){
        rez = rez * 10 + it - '0';
    }
    return rez;
}
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> a;
        string b;
        b = a;
        reverse(b.begin(),b.end());
        if(b == a){
            sum += toInt();
        }
    }
    cout << sum;
    return 0;
}
