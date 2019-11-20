/* Binary Search Tree - recursive
 * Fall 2019
 * DSA
 * For the sake of demonstration and clarity we are going to use 
 * only a numerical value in the nodes of the tree. An element 
 * that is comparable could be used instead, but the syntax is 
 * more complicated than we need to deal with to understand 
 * Binary Search trees. This is the actual class definition.
 * 
 * BST ADT
 * add element
 * remove element if in tree
 * search for element - boolean result
 * traversals
 */
#include <iostream>
#include "BST.h"
#include <queue>

using namespace std;

// Constructor, destructor, copy 
BST::BST(int k){
  key = k;
  left = right = nullptr;
}
BST::BST(int k, BST* l, BST* r){
  key = k;
  left = l;
  right = r;
}
BST::~BST(){
  delete left;
  delete right;
}

// private methods
void BST::visit() const{
  cout << key << " ";
}

/* Accessors */
BST* BST::getLeft(){
  return left;
}
BST* BST::getRight(){
  return right;
}

// TO DO
bool BST::find(int num) const{
  if (key == num) return true;
  else if (num>key && right != nullptr){
    return right->find(num);
  }
  else if(num<key && left != nullptr){
    return left->find(num);
  }
  return false; // bada bing baada boom
}

BST* BST::search(int num){ //return the BST
  if (key == num) return this;
  else if (num>key && right != nullptr){
    return right->search(num);
  }
  else if(num<key && left != nullptr){
    return left->search(num);
  }
  return nullptr; 
  
}

BST* BST::searchParent(int num){
  cout << "Starting search parent. " <<endl;
  if (key == num){
    cout << "returning nullptr" << endl;
    return nullptr;
  }
  cout << "Key currently looking at: " << key << endl;

  // are any of the children the thing we are looking for
  if (right != nullptr && right->key == num)
    return this;
  else if (left != nullptr && left->key == num)
    return this;

  
  if (right != nullptr && num > key){
      cout << "recursing on right of " << key << endl;
      return right->searchParent(num);
  }
  else if (left != nullptr && left->key == num){
      cout << "found it, parent is: " << key << endl;
      return left->searchParent(num);
  }
  
  return nullptr; 

}
void BST::inOrder() const{
  if (left != nullptr) {
    left->inOrder();
  }
  visit();
  if (right != nullptr) {
    right->inOrder();
  }

  
  //bada bing
}
void BST::preOrder() const{
  visit();
  if (left != nullptr) {
    left->preOrder();
  }
  if (right != nullptr) {
    right->preOrder();
  }  

}
void BST::postOrder() const{
  if (left != nullptr) {
    left->postOrder();
  }
  if (right != nullptr) {
    right->postOrder();
  }
  visit();
  
}
void BST::breadthFirst() {
}

/* Mutators */
bool BST::add(int num){
  if (num>key){
    if (right == NULL){
      right = new BST(num);
    }
    else{
      right->add(num);
    }
  }
  else if (num < key){
    if (left == NULL){
      left = new BST(num);
    }
    else{
      left->add(num);
    }
  }
  else{
    return false;
  }
  return true; //bada bink
}
bool BST::remove(int num){
  BST* cur = search(num);
  cout << "Current: " << cur->key << endl;
  BST* parent = searchParent(num);
  cout << "Parent: " << parent->key << endl;
  if (cur == nullptr) return false;
  if (cur->right == nullptr && cur->left == nullptr){
    if (parent != nullptr){
      if (parent->key < num){
	parent -> right = nullptr;
      }
      else{
	parent -> left = nullptr;
      }
    }    
    delete cur;
    return true;
  }
  BST* temp = nullptr;
  if (cur->right != nullptr){
    temp = cur->right;
    while (temp->left != nullptr){
      temp  = temp->left;
    }
  }
  else{
    temp = cur->left;
    while (temp->right != nullptr){
      temp = temp->right;
    }
  }
  int tempKey = temp->key;
  temp->key = cur->key;
  cur->key = tempKey;
  cout << "Recursing " << temp->key << endl;
  
  return temp->remove(num);
}

int main(){
  BST* tree = new BST(5);

  tree->add(8);
  tree->add(3);
  tree->add(2);
  tree->add(1);
  tree->add(4);
  tree->add(7);
  tree->add(9);
  tree->add(6);
  tree->add(10);

  cout << "printing tree traversals: in, pre, post"
       << endl;
  //  cout << tree->search(2)->key << endl;
  //cout << tree->searchParent(2)->key <<endl;
  tree->inOrder();
  cout << endl;
  tree->preOrder();
  cout << endl;
  tree->postOrder();
  cout << endl;

  cout << "removing 3" << endl;
  tree->remove(3);
  
  tree->inOrder(); 
  /*  tree->remove(6);
  tree->inOrder();
  tree->remove(5);
  tree->inOrder();*/
  
}
