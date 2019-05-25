#include <cstdio>
#include <algorithm>

using namespace std;

struct node_t{
    long long weight;
    node_t *l;
    node_t *r;
    long long sum;

    node_t(long long weight,node_t *l,node_t *r,long long sum = 0){
        this->weight = weight;
        this->l = l;
        this->r = r;
        this->sum = sum;
    }
}*nill,*aint;

void add(node_t *root,long long l,long long r,long long pos){
    if(r < pos || l > pos){
        return ;
    }

    if(l == r){
        root->weight++;
        root->sum += pos;
        return ;
    }

    long long mid = (l + r) / 2;

    if(root->l == nill){
        root->l = new node_t(0,nill,nill);
    }

    if(root->r == nill){
        root->r = new node_t(0,nill,nill);
    }

    add(root->l,l,mid,pos);
    add(root->r,mid + 1,r,pos);

    root->weight = root->l->weight + root->r->weight;
    root->sum = root->l->sum + root->r->sum;
}

long long offset = 0;

pair<long long,long long> get_elem(node_t *root,long long l,long long r,long long pos){
    if(l == r){
        return {l,offset};
    }

    long long mid = (l + r) / 2;

    if(root->l->weight < pos){
        pos -= root->l->weight;
        auto tmp = get_elem(root->r,mid + 1,r,pos);
        tmp.second = tmp.second + 1LL * root->l->weight * tmp.first - root->l->sum;
        return tmp;
    }
    else{
        auto tmp = get_elem(root->l,l,mid,pos);
        tmp.second = tmp.second - 1LL * root->r->weight * tmp.first + root->r->sum;
        return tmp;
    }
}

long long q;

int main(){
    nill = new node_t(0,NULL,NULL);
    aint = new node_t(0,nill,nill);

    scanf("%lld",&q);

    while(q--){
        long long t;
        scanf("%lld",&t);

        if(t == 1){
            long long a,b;
            scanf("%lld %lld",&a,&b);
            offset += b;
           add(aint,1,2e9 + 1,a + 1e9 + 1);
        }
        else{
            pair<long long,long long> tmp = {0,0}; 
            tmp = get_elem(aint,1,2e9 + 1,(1 + aint->weight) / 2);
            tmp.first -= 1;
            tmp.first -= 1e9;
            printf("%lld %lld\n",tmp.first,tmp.second);
        }
    }

    return 0;
}
