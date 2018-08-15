#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
bool viz[200005];
string a;
int nxt[200005];
int lst[200005];
int st0[200005],len0;
int st1[200005],len1;
vector<vector<int> > Ans;
int main()
{
    cin >> a;
    a = " " + a;
    for(int i = 1;i < (int)a.size();i++){
        if(a[i] == '0'){
            if(len1){
                lst[i] = st1[len1];
                nxt[st1[len1]] = i;
                len1--;
            }
            st0[++len0] = i;
        }
        else{
            if(len0){
               lst[i] = st0[len0];
               nxt[st0[len0]] = i;
               len0--;
            }
            else{
                cout << -1;
                return 0;
            }
            st1[++len1] = i;
        }
    }
    for(int i = 1;i < (int)a.size();i++){
        if(a[i] == '1' && (!nxt[i] || !lst[i])){
            cout << -1;
            return 0;
        }
    }
    for(int i = 1;i < (int)a.size();i++){
        if(!viz[i]){
            vector<int> tmp;
            int nod = i;
            while(nod){
                    viz[nod] = 1;
                tmp.push_back(nod);
                nod = nxt[nod];
            }
            Ans.push_back(tmp);
        }
    }
    printf("%d\n",Ans.size());
    for(auto it:Ans){
        printf("%d ",it.size());
        for(auto it2:it){
            printf("%d ",it2);
        }
        printf("\n");
    }
    return 0;
}
