#include <iostream>

using namespace std;
int N;
string a;
bool isvow(int last){
    return last == 'a' || last == 'e' || last == 'i' || last == 'o' || last == 'u' || last == 'y';
}
int main()
{
    cin >> N >> a;
    char last = '0';
    for(auto it:a){
        if(isvow(last) && isvow(it)){
            continue;
        }
        cout << it;
        last = it;
    }

    return 0;
}
