#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
string a,b;
int fr[10];
int pref = -1;
int low(){
    int cf = 0;
    while(1){
        if(fr[cf]){
            return cf;
        }
        cf++;
    }
}
int main()
{
    cin >> a >> b;
    if(a.size() < b.size()){
        sort(a.begin(),a.end());
        reverse(a.begin(),a.end());
        cout << a;
        return 0;
    }
    for(auto it:a){
        fr[it - '0']++;
    }
    for(int i = 0;i < (int)b.size();i++){
        if(!fr[b[i] - '0']){
            break;
        }
        fr[b[i] - '0']--;
        if(i == (int)b.size() - 1 || low() < b[i + 1] - '0'){
            pref = i;
        }
    }
    memset(fr,0,sizeof(fr));
    for(auto it:a){
        fr[it - '0']++;
    }
    for(int i = 0;i < (int)b.size();i++){
        if(i <= pref){
            fr[b[i] - '0']--;
            cout << b[i];
        }
        else{
            int cf = b[i] - '0' - 1;
            while(!fr[cf]){
                cf--;
            }
            cout << cf;
            fr[cf]--;
            break;
        }
    }
    for(int cf = 9;cf >= 0;cf--){
        while(fr[cf]--){
            cout << cf;
        }
    }
    return 0;
}
