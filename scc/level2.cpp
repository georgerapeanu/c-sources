#include <bits/stdc++.h>

using namespace std;

struct user_t{
    int id;
    int points;
    int wins;

    user_t(){
        id = 0;
        points = 0;
        wins = 0;
    }

    bool operator < (const user_t &other)const {
        if(this->wins != other.wins){
            return this->wins > other.wins;
        }
        return id < other.id;
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

unordered_map<int,user_t> player;

int main(){

    scanf("%d %d",&m,&n);

    for(int i = 1;i <= m;i++){
        int a,s_a,b,s_b;
        scanf("%d %d %d %d",&a,&s_a,&b,&s_b);
        player[a].id = a;
        player[a].points = max(player[a].points,s_a);
        player[a].wins += (s_a > s_b);
        player[b].id = b;
        player[b].points = max(player[b].points,s_b);
        player[b].wins += (s_b > s_a);
    }

    vector<user_t> scoreboard;

    for(auto it:player){
        scoreboard.push_back(it.second);
    }

    sort(scoreboard.begin(),scoreboard.end());

    for(auto it:scoreboard){
        printf("%d %d\n",it.id,it.wins);
    }

    return 0;
}
