#include <iostream>
#include <vector>

using namespace std;

vector<int> a;
vector<int> b;

vector<int> read_number(){
    string s;
    cin >> s;

    vector<int> ans;

    for(int i = (int)s.size() - 1;i >= 0;i--){
        ans.push_back(s[i] - '0');
    }
    
    return ans;
}

vector<int> add(vector<int> a,vector<int> b){
    vector<int> ans;

    int t = 0;

    for(int i = 0;i < (int)a.size() || i < (int)b.size() || t;i++){
        ans.push_back(t + (i < (int)a.size() ? a[i]:0) + (i < (int)b.size() ? b[i]:0));
        t = ans.back() / 10;
        ans.back() %= 10;
    }

    return ans;
}

void print_number(vector<int> a){
    for(int i = (int)a.size() - 1;i >= 0;i--){
        cout << a[i];    
    }
    cout << "\n";
}

int main(){

    print_number(add(read_number(),read_number()));

    return 0;
}
