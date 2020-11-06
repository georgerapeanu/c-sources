#include <bits/stdc++.h>

using namespace std;

struct user_t{
    int id;
    int rating;

    user_t(){
        id = 0;
        rating = 0;
    }

    bool operator < (const user_t &other)const {
        if(this->rating != other.rating){
            return this->rating > other.rating;
        }
        return id < other.id;
    }
};

vector<user_t> player;

struct team_t{
    vector<pair<int,int> > fst;
    vector<pair<int,int> > snd;

    team_t(int team_size){
        for(int i = 0;i < team_size;i++){
            fst.push_back({0,0});
            scanf("%d %d\n",&fst.back().first,&fst.back().second);
        }
        for(int i = 0;i < team_size;i++){
            snd.push_back({0,0});
            scanf("%d %d\n",&snd.back().first,&snd.back().second);
        }
    }
    
    void process_a_game(user_t &a,user_t &b,int winA){
        long double e_a;
        int k = 32;

        e_a = ((long double)1) / (1 + pow(10,(b.rating - a.rating) / ((long double)400)));

        a.rating += k * (winA - e_a);
        b.rating += k * ((1 - winA) - (1 - e_a));
    }

    void process_game(){
        int win_fst = 0;
        int rating_sum_fst = 0;
        int rating_sum_snd = 0;
        for(auto it:fst){
            win_fst += it.second;
            rating_sum_fst += player[it.first].rating;
        }
        for(auto it:snd){
            win_fst -= it.second;
            rating_sum_snd += player[it.first].rating;
        }
        win_fst = (win_fst > 0);
        for(auto it:fst){
            int opp_rating = rating_sum_snd - rating_sum_fst + player[it.first].rating;
            user_t opp;
            opp.id = 0;
            opp.rating = opp_rating;
            process_a_game(player[it.first],opp,win_fst);
        }
        for(auto it:snd){
            int opp_rating = rating_sum_fst - rating_sum_snd + player[it.first].rating;
            user_t opp;
            opp.id = 0;
            opp.rating = opp_rating;
            process_a_game(player[it.first],opp,1 - win_fst);
        }
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
int team_size;



int main(){

    scanf("%d %d %d",&m,&n,&team_size);

    player = vector<user_t>(n,user_t());

    for(int i = 0;i < n;i++){
        player[i].id = i;
        player[i].rating = 1000;
    }


    for(int i = 1;i <= m;i++){
        team_t(team_size).process_game();
    }

    vector<user_t> scoreboard = player;

    sort(scoreboard.begin(),scoreboard.end());

    for(auto it:scoreboard){
        printf("%d %d\n",it.id,it.rating);
    }

    return 0;
}
