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
        if(this->points != other.points){
            return this->points > other.points;
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

int win,loss;
int n,m;

unordered_map<int,user_t> player;

int main(){

    scanf("%d %d",&win,&loss);
    loss *= -1;
    scanf("%d %d",&m,&n);

    for(int i = 1;i <= m;i++){
        int a,s_a,b,s_b;
        scanf("%d %d %d %d",&a,&s_a,&b,&s_b);
        player[a].id = a;
        player[a].points += (s_a > s_b) * win + (s_a < s_b) * loss;
        player[b].id = b;
        player[b].points += (s_b > s_a) * win + (s_b < s_a) * loss;
    }

    vector<user_t> scoreboard;

    for(auto it:player){
        scoreboard.push_back(it.second);
    }

    sort(scoreboard.begin(),scoreboard.end());

    for(auto it:scoreboard){
        printf("%d %d\n",it.id,it.points);
    }

    return 0;
}
