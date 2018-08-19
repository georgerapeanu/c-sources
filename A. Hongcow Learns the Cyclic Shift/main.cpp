#include <iostream>
#include <unordered_set>
#define works 1
using namespace std;
string C;
unordered_set <string> S;
int main()
{
    getline(cin,C);
    S.insert(C);
    int N=C.size();
    for(int i=1;i<N;i++)
    {

        C.insert(C.begin(),C.back());
        C.erase(C.begin()+N);
        S.insert(C);
        ///it doesnt take my first solution
    }
    cout<<S.size();
    return 0;
}
