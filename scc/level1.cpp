#include <bits/stdc++.h>

using namespace std;

struct user_t{
    int id;
    int points;

    user_t(){
        id = 0;
        points = 0;
    }

    bool operator < (const user_t &other)const {
        if(this->points != other.points){
            return this->points < other.points;
        }
        return id > other.id;
    }
};


class MatchMaker{
private:
public:

    MatchMaker(){
        ;
    }
}; 

int n,m;

map<int,user_t> player;

int main(){

    scanf("%d %d",&m,&n);

    for(int i = 1;i <= m;i++){
        int a,s_a,b,s_b;
        scanf("%d %d %d %d",&a,&s_a,&b,&s_b);
        player[a].id = a;
        player[a].points = max(player[a].points,s_a);
        player[b].id = b;
        player[b].points = max(player[b].points,s_b);
    }


    user_t bst;

    for(auto it:player){
        bst = max(bst,it.second);
    }

    printf("%d %d\n",bst.id,bst.points);

    return 0;
}
