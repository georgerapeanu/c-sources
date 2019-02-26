#include <iostream>

using namespace std;

bool pal(string &a){
    bool ok = true;

    for(int st = 0,dr = (int)a.size() - 1;st < dr;st++,dr--){
        ok &= (a[st] == a[dr]);
    }

    return ok;
}

int main(){
    string a;
    
    cin >> a;

    bool ok = true;

    for(int i = 0;i < (int)a.size();i++){
        if((int)a.size() % 2 == 1 && i == (int)a.size() / 2){
            continue;
        }
        ok &= (a[i] == a[0]);
    }

    if(ok){
        printf("Impossible\n");
        return 0;
    }

    string pref;

    for(int i = 0;i < (int)a.size();i++){
        pref += a[i];
        string b = a.substr(i + 1) + pref;
        if(pal(b) && a != b){
            printf("%d\n",1);
            return 0;
        }
    }

    printf("%d\n",2);

    return 0;
}
