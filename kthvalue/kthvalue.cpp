#include <bits/stdc++.h>

using namespace std;

struct node_t {
  int left_son;
  int right_son;
  int sum;

  node_t(){
    this->sum = 0;
    this->left_son = -1;
    this->right_son = -1;
  }

  node_t(int sum) {
    this->sum = sum;
    this->left_son = -1;
    this->right_son = -1;
  }

  node_t(int sum, int left_son, int right_son) {
    this->sum = sum;
    this->left_son = left_son;
    this->right_son = right_son;
  }
};

class PersistentSegmentTree {
  int n;
  vector<node_t> aint;

  int build(int st, int dr) {
    if(st == dr) {
      node_t tmp = node_t();
      aint.push_back(tmp);
      return (int)aint.size() - 1;
    }

    int mid = (st + dr) / 2;
    
    int lft = build(st, mid);
    int rgt = build(mid + 1, dr);

    node_t tmp(aint[lft].sum + aint[rgt].sum, lft, rgt);

    aint.push_back(tmp);
    return (int)aint.size() - 1;
  }

  int update(int nod, int st, int dr, int pos, int value) {
    if(dr < pos || st > pos) {
      return nod;
    }

    if(st == dr) {
      node_t tmp = node_t(aint[nod].sum + value);
      aint.push_back(tmp);
      return (int)aint.size() - 1;
    }

    int mid = (st + dr) / 2;
    int lft = update(aint[nod].left_son, st, mid, pos, value);
    int rgt = update(aint[nod].right_son, mid + 1, dr, pos, value);

    node_t tmp(aint[lft].sum + aint[rgt].sum, lft, rgt);

    aint.push_back(tmp);
    return (int)aint.size() - 1;
  }

  int get_sum(int root1, int root2) {
    return aint[root2].sum - aint[root1].sum;
  }
  
  int query(int root1, int root2, int st, int dr, int k) {
    if(st == dr) {
      return st;
    }

    int mid = (st + dr) / 2;

    if(k <= get_sum(aint[root1].left_son, aint[root2].left_son)) {
      return query(aint[root1].left_son, aint[root2].left_son, st, mid, k);
    }
    
    return query(aint[root1].right_son, aint[root2].right_son, mid + 1, dr, k - get_sum(aint[root1].left_son, aint[root2].left_son));
  }
  

  public:

  PersistentSegmentTree(int n, int &root) {
    this->n = n;
    root = this->build(1, n);
  }

  int update(int root, int pos, int value) {
    return this->update(root, 1, n, pos, value);
  }

  int query(int root1, int root2, int k) {
    return this->query(root1, root2, 1, n, k);
  }
};

const int LEN = 1 << 17;
char buff[LEN];
int ind = LEN - 1;

int i32() {
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9') {
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, stdin);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')) {
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff, 1, LEN, stdin);
    }
  }
  return ans;
}

int main() {
 
  freopen("kthvalue.in", "r", stdin);
  freopen("kthvalue.out", "w", stdout);

  int n;
  n = i32();

  deque<int> roots;

  roots.push_back(0);
  PersistentSegmentTree aint(n, roots[0]);
  
  while(n--) {
    int op;

    op = i32();

    if(op == 1) {
      int value;
      value = i32();
      int new_root = aint.update(roots[0], value, -1);
      roots.push_front(new_root);
    }else if(op == 2) {
      int value;
      value = i32();
      int new_root = aint.update(roots.back(), value, 1);
      roots.push_back(new_root);
    }else if(op == 3) {
      roots.pop_front();
    }else if(op == 4) {
      roots.pop_back();
    }else {
      int x, y, k;
      x = i32();y = i32();k = i32();
      printf("%d\n", aint.query(roots[x - 1], roots[y], k));
    }
  }

  return 0;
}
