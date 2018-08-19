#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N,minsz;
vector< pair<string,int> > INPUT;

struct node{
    string name;
    vector<node*> sons;
    int sz;
    node(){
        name = "";
        sons = vector<node*>();
        sz = 0;
    }
    node(string NAME,vector<node*> SONS,int SZ){
        name = NAME;
        sons = SONS;
        sz = SZ;
    }
}*T;

void ins(string a,int sz){
    vector<string> path;
    string last_file;
    for(int i = 1;i < (int)a.size();i++){
        if(a[i] == '/'){
            path.push_back(last_file);
            last_file = "";
        }
        else{
            last_file += a[i];
        }
    }
    node *tmp = T;
    for(auto it:path){
        tmp -> sz += sz;
        if((tmp -> sons).empty() || ((tmp -> sons).back()) -> name != it){
            (tmp -> sons).push_back(new node(it,vector<node*>(),0));
        }
        tmp = (tmp -> sons).back();
    }
    tmp -> sz += sz;
}

void afis(node *T,string &path){
    path +=  (T -> name) + "/";

    if((T -> sons).empty()){
        cout << "  " << path << " " << T -> sz << "\n";
    }

    else{
        bool expand = 0;

        for(auto it:(T -> sons)){
            expand |= (it -> sz >= minsz);
        }

        if(expand){
            cout << "- " << path << " " << T -> sz << "\n";
            for(auto it:(T -> sons)){
                afis(it,path);
            }
        }

        else{
            cout << "+ " << path << " " << T -> sz << "\n";
        }
    }

    path.resize(path.size() - (T -> name).size() - 1);
}

int main(){
    cin >> N;

    for(int i = 1;i <= N;i++){
        string a;
        int sz;
        cin >> a >> sz;
        INPUT.push_back({a,sz});
    }

    cin >> minsz;

    sort(INPUT.begin(),INPUT.end());

    T = new node;

    for(int i = 0;i < N;i++){
        ins(INPUT[i].first,INPUT[i].second);
    }

    string path = "";

    afis(T,path);

    return 0;
}
