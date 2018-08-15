#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;
struct cow{
    int day;
    string name;
    int dif;
    bool operator < (const cow &other)const{
        return day < other.day;
    }
}V[105];
map<string,int> last;
int compute(){
    int rez = 0,maxi = max(max(last["Mildred"],last["Elsie"]),last["Bessie"]);
    if(last["Bessie"] == maxi){
        rez |= 1;
    }
    if(last["Elsie"] == maxi){
        rez |= 2;
    }
    if(last["Mildred"] == maxi){
        rez |= 4;
    }
    return rez;
}
int N;
int conf = (1 << 3) - 1;
int main()
{
    freopen("measurement.in","r",stdin);
    freopen("measurement.out","w",stdout);
    last["Mildred"] = 7;
    last["Elsie"] = 7;
    last["Bessie"] = 7;
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i].day >> V[i].name >> V[i].dif;
    }
    sort(V + 1,V + 1 + N);
    int rez = 0;
    for(int i = 1;i <= N;i++){
        last[V[i].name] += V[i].dif;
        int nconf = compute();
        if(nconf != conf){
            rez++;
        }
        conf = nconf;
    }
    cout << rez;
    return 0;
}
