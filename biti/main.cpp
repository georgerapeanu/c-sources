#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("biti.in");
ofstream g("biti.out");
int N;
bool used[1 << 20];
int st[1 << 20],top;
string ans;
int main(){
    f >> N;
    if(N == 1){
        g << "2\n01";
        return 0;
    }
    st[++top] = 0;
    while(top){
        int nod = st[top];
        if(!used[nod << 1]){
            st[++top] = (nod << 1) & ((1 << (N - 1)) - 1);
            used[nod << 1] = 1;
        }
        else if(!used[(nod << 1) + 1]){
            st[++top] = ((nod << 1) + 1) & ((1 << (N - 1)) - 1);
            used[(nod << 1) + 1] = 1;
        }
        else{
            if(top != 1){
                ans += '0' + (nod & 1);
            }
            top--;
        }
    }
    for(int i = 1;i < N;i++){
        ans += '0';
    }
    reverse(ans.begin(),ans.end());
    g << ans.size() << "\n" << ans;
    f.close();
    g.close();
    return 0;
}
