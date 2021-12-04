/**
 * Author: Rapeanu George - Alexandru
 * License: None
 * Description: 0-indexed Segment Tree that suports lazy update with containers like kactlStaticSegmentTreeNode.h
 * Status: Not tested yet
 */
#pragma once
#include <algorithm>
#include <vector>

using namespace std;

template <class T>
class SegmentTree{
  int n;
  vector<T> aint;

  void propagate(int nod,int st,int dr){
    if(aint[nod].lazy == T().lazy || st == dr){
      return ;
    }
    int mid = (st + dr) / 2;
    aint[nod * 2].propagate(aint[nod].lazy,st,mid);
    aint[nod * 2 + 1].propagate(aint[nod].lazy,mid + 1,dr);
    aint[nod].lazy = T().lazy;
  }
  
  ///change lazy here
  void updateAdd(int nod,int st,int dr,int l,int r,int lazy){
    propagate(nod,st,dr);

    if(dr < l || st > r){
      return ;
    }

    if(l <= st && dr <= r){
      aint[nod].propagate(lazy,st,dr);
      return ;
    }
    
    int mid = (st + dr) / 2;

    updateAdd(nod * 2,st,mid,l,r,lazy);
    updateAdd(nod * 2 + 1,mid + 1,dr,l,r,lazy);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  void updateSet(int nod,int st,int dr,int pos,const T &value){
    propagate(nod,st,dr);

    if(dr < pos || st > pos){
      return ;
    }

    if(st == dr){
      aint[nod] = value;
      return ;
    }

    int mid = (st + dr) / 2;

    updateSet(nod * 2,st,mid,pos,value);
    updateSet(nod * 2 + 1,mid + 1,dr,pos,value);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  T query(int nod,int st,int dr,int l,int r){
    propagate(nod,st,dr);

    if(dr < l || st > r){
      return T();
    }

    if(l <= st && dr <= r){
      return aint[nod];
    }


    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
  }

  public:
  
  SegmentTree(int n){
    this->n = n;
    this->aint = vector<T>(4 * n + 5,T());
  }

  ///update with a node
  void updateSet(int pos,T val){
    updateSet(1,0,n - 1,pos,val);
  }
  
  ///update with a lazy
  void updateAdd(int pos,int val){
    updateAdd(1,0,n - 1,pos,pos,val);
  }

  void updateAdd(int l,int r,int val){
    updateAdd(1,0,n - 1,l,r,val);
  }

  T query(int l,int r){
    return query(1,0,n - 1,l,r);
  }
};
