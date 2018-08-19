#include <iostream>

using namespace std;
int x,y;
int last = -1;
string a;
int N,rez;
int main()
{
    cin >> N >> a;
    for(auto it:a){
        if(x == y){
            x += (it == 'R');
            y += (it == 'U');
            if(y < x){
                rez += (last == 1);
                last = 2;
            }
            if(x < y){
                rez += (last == 2);
                last = 1;
            }
        }
        else{
             x += (it == 'R');
             y += (it == 'U');
        }
    }
    cout << rez;
    return 0;
}
