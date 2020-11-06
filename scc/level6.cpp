#include <bits/stdc++.h>
#include <chrono>

using namespace std;

mt19937 gen(0);

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
int max_elo_diff,score_thresh;

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

struct match_t{
    int sz;
    vector<int> players;

    match_t(){
        sz = 0;
        players = vector<int>();
    }

    match_t(int team_size,vector<int> players){
        this->sz = team_size;
        assert(team_size * 2 == (int)players.size());
        this->players = players;
    }

    int cost(){
        int diff = 0;
        for(int i = 0;i < sz;i++){
           diff += player[players[i]].rating;
        }
        for(int i = 0;i < sz;i++){
           diff -= player[players[sz + i]].rating;
        }
        return abs(diff);
    }

    int find_minimum_score(){
        int diff = 0;
        for(int i = 0;i < sz;i++){
           diff += player[players[i]].rating;
        }
        for(int i = 0;i < sz;i++){
           diff -= player[players[sz + i]].rating;
        }
        for(int i = 1;i <= 400;i++){
            int a = gen() % sz;
            int b = sz + (gen() % sz);
            if(abs(diff - 2 * player[players[a]].rating + 2 * player[players[b]].rating) < abs(diff) + (gen() % 30)){
                diff += 2 * (player[players[b]].rating - player[players[a]].rating);
                swap(players[a],players[b]);
            }
        }
        return abs(diff);
    }

    bool valid(){
        int mi = 1e9;
        int ma = -1e9;

        for(auto it:players){
            mi = min(mi,player[it].rating);
            ma = max(ma,player[it].rating);
        }

        return ma - mi <= max_elo_diff;
    }

    int try_exchange(match_t &other){
        vector<int> b1,b2;
        b1 = this->players;
        b2 = other.players;

        int b1_diff = this->cost();
        int b2_diff = other.cost();

        for(int i = 0;i <= 100;i++){
            int a = gen() % (2 * sz);
            int b = gen() % (2 * sz);
            swap(this->players[a],other.players[b]);
            int tmp_1 = this->find_minimum_score();
            int tmp_2 = other.find_minimum_score();
            if(this->valid() && other.valid() && b1_diff + b2_diff > tmp_1 + tmp_2){
                return (tmp_1 + tmp_2) - (b1_diff +b2_diff);
            }
            this->players = b1;
            other.players = b2;
        }

        return 0;
    }
};


int n,m;
int team_size;

int main(){

    gen = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    scanf("%d %d %d",&m,&n,&team_size);

    player = vector<user_t>(n,user_t());

    for(int i = 0;i < n;i++){
        player[i].id = i;
        player[i].rating = 1000;
    }


    for(int i = 1;i <= m;i++){
        team_t(team_size).process_game();
    }


    scanf("%d %d",&max_elo_diff,&score_thresh);
    int cnt;
    scanf("%d",&cnt);

    vector<int> q;

    for(int i = 1;i <= cnt;i++){
        int id;
        scanf("%d",&id);
        q.push_back(id);
    }
    
    sort(q.begin(),q.end());

    vector<match_t> matches;

    int score = 0;

    for(int i = 0;i < (int)q.size();i += 2 * team_size){
        vector<int> tmp;
        for(int j = 0;j < 2 * team_size;j++){
            tmp.push_back(q[i + j]);
        }
        matches.push_back(match_t(team_size,tmp));
        score += matches.back().find_minimum_score();
    }

    fprintf(stderr,"init score is %d\n",score);

    for(auto it:player){
        fprintf(stderr,"deb %d %d\n",it.id,it.rating);
    }
    while(score > score_thresh){
        for(int i = 0;i + 1 < (int)matches.size();i++){
            score += matches[i].try_exchange(matches[i + 1]);
        }
        fprintf(stderr,"now score is %d\n",score);
    }
    
    fprintf(stderr,"done score is %d\n",score);

    for(auto it:matches){
        for(int i = 0;i < 2 * team_size;i++){
            printf("%d ",it.players[i]);
        }
        printf("\n");
    }

    return 0;
}
