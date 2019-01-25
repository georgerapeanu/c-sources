#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;
const int VMAX = 1e6;

int n;
string a,b;
int p[NMAX + 5];
bool viz[NMAX + 5];

vector< pair<int,int> > tcr_data;

void kmp_and_mark(string &text,string &pattern){
    text = " " + text;
    pattern = " " + pattern;
    vector<int> fail(pattern.size(),0);
    for(int i = 2;i < (int)pattern.size();i++){
        int k = fail[i - 1];
        while(k && pattern[k + 1] != pattern[i]){
            k = fail[k];
        }
        if(pattern[k + 1] == pattern[i]){
            k++;
        }
        fail[i] = k;
    }

    int ind = 0;

    int fstr = -1;

    for(int i = 1;i < (int)text.size() - 1;i++){
        while(ind && text[i] != pattern[ind + 1]){
            ind = fail[ind];
        }

        if(text[i] == pattern[ind + 1]){
            ind++;
            if(ind == (int)pattern.size() - 1){
                ind = fail[ind];
                int r = i - ((int)pattern.size() - 1);
                if(fstr == -1){
                    fstr = r;
                }
                else{
                    tcr_data.push_back({r - fstr,fstr});
                    return ;
                }
            }
        }
    }
    
    if(fstr == -1){
        cout << "-1\n";
        exit(0);
    }
    else{
        tcr_data.push_back({(int)pattern.size() - 1,fstr});
    }
}

string shuffle(string s){
    string t(s.size(),' ');
    for(int i = 1;i <= n;i++){
        t[p[i]] = s[i];
    }
    return t;
}

int main(){
   
    cin >> a;a = " " + a;
    cin >> b;b = " " + b;

    swap(a,b);

    n = a.size() - 1;

    for(int i = 1;i <= n;i++){
        p[i] = (i <= n / 2 ? 2 * i - 1 : (i - n / 2) * 2);    
    }

    int cycles = 0;
    int mx_size = 0;

    for(int i = 1;i <= n;i++){
        if(viz[i] == false){
            string text = "";
            string pattern = "";
            for(int nod = i;viz[nod] == false;nod = p[nod]){
                pattern += a[nod];
                text += b[nod];
                viz[nod] = true;
            }
            text = text + text;
            cycles++;
            mx_size = max(mx_size,(int)pattern.size());
            kmp_and_mark(text,pattern);
        }
    }

    sort(tcr_data.begin(),tcr_data.end());
    tcr_data.resize(unique(tcr_data.begin(),tcr_data.end()) - tcr_data.begin());

    int ans = 0;

    while(1){
        for(auto it:tcr_data){
            if(ans % it.first != it.second){
                goto fail;
            }
        }
        
        cout << ans << "\n";
        return 0;

        fail:;
        ans++;
    }

    return 0;
}
