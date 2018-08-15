#include <bits/stdc++.h>
using namespace std;
vector<string> apartenente={"caracterizare de personaj","rezumat","text nonliterar","titlu pe liric","titlu pe epic","mesaj pe liric","mesaj pe epic","gen liric","pastel","doina","gen epic","basm","fabula","balada","schita","nuvela","gen dramatic"};
bool ok;
int nr;
int main()
{
    srand(time(NULL));
    random_shuffle(apartenente.begin(),apartenente.end());
    for(auto it:apartenente){cout<<it<<"\n";cin>>ok;nr+=ok;}
    cout<<"\n"<<nr;
    return 0;
}
