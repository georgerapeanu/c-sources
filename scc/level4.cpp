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


class MatchMaker{
private:
public:

    MatchMaker(){
        ;
    }
}; 

int n,m;

vector<user_t> player;

void process_game(user_t &a,user_t &b,int winA){
    long double e_a;
    int k = 32;

    e_a = ((long double)1) / (1 + pow(10,(b.rating - a.rating) / ((long double)400)));

    a.rating += k * (winA - e_a);
    b.rating += k * ((1 - winA) - (1 - e_a));
}

int main(){

    scanf("%d %d",&m,&n);

    player = vector<user_t>(n,user_t());

    for(int i = 0;i < n;i++){
        player[i].id = i;
        player[i].rating = 1000;
    }


    for(int i = 1;i <= m;i++){
        int a,s_a,b,s_b;
        scanf("%d %d %d %d",&a,&s_a,&b,&s_b);
        process_game(player[a],player[b],(s_a > s_b));  
    }

    vector<user_t> scoreboard = player;

    sort(scoreboard.begin(),scoreboard.end());

    for(auto it:scoreboard){
        printf("%d %d\n",it.id,it.rating);
    }

    return 0;
}
