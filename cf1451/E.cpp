#include <bits/stdc++.h>

using namespace std;

int n;

int ask_or(int a,int b){
    a++;b++;
    int ans;
    cout << "OR " << a << " " << b << endl;
    cin >> ans;
    return ans;
}

int ask_and(int a,int b){
    a++;b++;
    int ans;
    cout << "AND " << a << " " << b << endl;
    cin >> ans;
    return ans;
}

int ask_xor(int a,int b){
    a++;b++;
    int ans;
    cout << "XOR " << a << " " << b << endl;
    cin >> ans;
    return ans;
}

void answer(const vector<int> &vals){
    cout << "! ";
    for(auto it:vals){
        cout << it << " ";
    }
    cout << endl;
    exit(0);
}

int where[1 << 16];

int main(){
    int n;
    
    vector<int> tmp = {0};
    vector<int> vals = {0};

    cin >> n;

    for(int i = 1;i < n;i++){
        tmp.push_back(ask_xor(0,i));
        vals.push_back(0);
    }

    for(int i = 1;i < n;i++){
        if(tmp[i] == 0){
            vals[0] = ask_and(0,i);
            for(int i = 1;i < n;i++){
                vals[i] = vals[0] ^ tmp[i];
            }
            answer(vals);
        }
    }

    for(int i = 1;i < n;i++){
        if(where[tmp[i]]){
            vals[i] = ask_and(where[tmp[i]],i);
            vals[0] = tmp[i] ^ vals[i];
            for(int i = 1;i < n;i++){
                vals[i] = vals[0] ^ tmp[i];
            }
            answer(vals);
        }
        where[tmp[i]] = i;
    }

    bool done_1 = false,done_2 = false;
    for(int i = 1;i < n;i++){
        if(tmp[i] == 1 && done_1 == false){
            vals[0] |= ((int(ask_and(0,i) >> 1)) << 1);
            done_1 = true;
        }
        if(tmp[i] == 2 && done_2 == false){
            vals[0] |= (ask_and(0,i) & 1);
            done_2 = true;
        }
    }
        
    for(int i = 1;i < n;i++){
        vals[i] = vals[0] ^ tmp[i];
    }

    answer(vals);

    return 0;
}
