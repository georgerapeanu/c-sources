#include <iostream>

using namespace std;

struct node_t{
    string val;
    node_t *left,*right;

    node_t(string val,node_t *left,node_t *right){
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

string serialize(node_t *node){
    if(node == NULL){
        return "{}";
    }
    string ans = string("{") + string("'") + node->val + string("', ");
    ans = ans + serialize(node->left) + ", ";
    ans = ans + serialize(node->right) + "}";
    return ans;
}

node_t* deserialize(const string &a){
    if(a == "{}"){
        return NULL;
    }
    node_t* ans;
    string val[3];
    int curr = 0;
    int height = 0;

    for(int i = 0;i < (int)a.size();i++){
        height += (a[i] == '{' ? 1 : (a[i] == '}' ? -1:0));
        val[curr] += a[i];
        if(a[i] == ',' && height == 1){
            curr++;
        }
    }

    string root = val[0].substr(2,(int)val[0].size() - 4);
    string lft = val[1].substr(1,(int)val[1].size() - 2);
    string rgt = val[2].substr(1,(int)val[2].size() - 2);

    return new node_t(root,deserialize(lft),deserialize(rgt));
}

int main(){

    node_t* lftlft;lftlft = new node_t(string("left.left"),NULL,NULL);
    node_t* lft;lft = new node_t(string("left"),lftlft,NULL);
    node_t* rgt;rgt = new node_t(string("right"),NULL,NULL);
    node_t* root;root = new node_t(string("root"),lft,rgt);

    cout << serialize(root) << "\n";
    cout << deserialize(serialize(root))->left->left->val;

    return 0;
}
