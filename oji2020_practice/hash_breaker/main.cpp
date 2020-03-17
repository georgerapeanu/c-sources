#include <iostream>

using namespace std;

long long mod1;
long long mod2;

string get_string(int len,long long a){
    int expected = 1;

    string s;

    for(int i = len;i >= 0;i--){
        if(((a >> i) & 1) == expected){
            s += '0';
            expected ^= 1;
        }
        else{
            s += '1';
            s += '0';
        }
    }

    return s;
}

int main(){

    const long long mod1 = 1000000003;
    const long long mod2 = 1000000009;

    long long a = mod1 * mod2 + 1;
    long long b = 1;

    int len = 63;

    while((a >> len) == 0){
        len--;
    }

    string s,t;

    s = get_string(len,a);
    t = get_string(len,b);

    while(s.size() < t.size()){
        s = s + '1';
    }

    while(t.size() < s.size()){
        t = t + '1';
    }

    cout << t.size() + s.size() << "\n" << s + t << "\n" << "1\n1 " << s.size() + 1 << " " << s.size() << endl;


    return 0;
}
