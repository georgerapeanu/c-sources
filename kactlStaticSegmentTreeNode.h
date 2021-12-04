/**
 * Author: Rapeanu George - Alexandru
 * License: None
 * Description: Customizable node container for segment tree which is implemented with vectors
 * Status: Not tested yet
 */
#pragma once

struct node_t{
  int value;
  int lazy;

  /// should be a neutral node for both lazy and query operations
  node_t(){ 
    value = lazy = 0;
  }

  /// aditional constructors for specific problem
  node_t(int value){
    this->value = value;
    this->lazy = 0;
  }
  
  /// associative internal operation 
  node_t operator + (const node_t &other)const{
    return node_t((this->value > other.value ? this->value:other.value));
  }

  /// internal propagation law
  void propagate(int lazy,int st,int dr){
    this->lazy += lazy;
    this->value += lazy;
  }
};
