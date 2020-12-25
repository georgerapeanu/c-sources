#include <fstream>

using namespace std;

ifstream f("domenii.in");
ofstream g("domenii.out");

int n;
string s;
int fr[30];

int main(){

    f >> n;
    f >> s;

    long long ans = 0;
    long long coef = 0;
    int sum_fr = 0;

    for(int i = n - 1;i >= 0;i--){
        if(s[i] == '.'){
            ans += coef;
        }
        else{
            fr[s[i] - 'a']++;
            sum_fr++;
            coef += sum_fr - fr[s[i] - 'a'];
        }
    }

    g << ans << endl;

    f.close();
    g.close();

    return 0;
}
