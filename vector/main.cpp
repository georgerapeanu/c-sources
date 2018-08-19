//#include <iostream>
//#include <vector>
//#include <stack>
//#include <queue>
//#include <set>
//using namespace std;
//typedef pair<int,int> d;
////vector<int> v;
////vector<int>::iterator it;
////stack <int> s;
//set<d> s;
//set<d> ::iterator it;
//int main()
//{
////    v.push_back(10);
////    cout<<v[0];
////    v.erase(v.begin());
////    cout<<v.empty();
////    s.push(3);
////    s.push(9);
////    s.push(7);
////    s=NULL;
////    cout<<s.empty();
////    s.push(3);
////    cout<<s.top();
//    s.insert(d(3,5));
//    for(it=s.begin();it!=s.end();it++)
//    cout<<(*it).first<<" "<<(*it).second<<" ";
//    return 0;
//}
#include <iostream>
#include <set>
#include <ctime>
#include <cstdio>
#define nmax 100005
#include <algorithm>
using namespace std;

set <int> S;

int main() {
  srand((unsigned)time(0));

  for(int i=1; i<=10; i++)
    S.insert(rand()%100);

  cout<<"Elementele setului in ordine: ";
  for(set<int> :: iterator x=S.begin();x!=S.end();x++)
    cout<<*x<<" ";
  return 0;
}
