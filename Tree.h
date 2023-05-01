#ifndef DS_1_WET_TREE_H
#define DS_1_WET_TREE_H


#include "AVL_node.h"

class TreeEmpty: public std::exception{};

template<class Key, class Data>
class Tree{
private:
    AVL_node<Key, Data>* root;
    int size;
    bool validCheck(AVL_node<Key, Data>* node);
public:
    Tree():root(nullptr), size(0){}
    void insert(const Key& key, const Data& data);
    void remove(const Key& key);
    void print();
    Key* get_as_sorted_array();
    int getSize() const;
    Data* operator[](const Key& key);
    Data* find_by_index(int index);

    // for tests:
    bool validCheck();
    int realHeight(AVL_node<Key, Data>* node);

    virtual ~Tree();
};

template<class Key, class Data>
void Tree<Key, Data>::insert(const Key &key, const Data &data) {
    if(this->root == nullptr){
        this->root = new AVL_node<Key, Data>(key ,data);
    } else{
        this->root = this->root->insert(key, data);
    }
    this->size++;
}

template<class Key, class Data>
void Tree<Key, Data>::remove(const Key &key) {
    if(this->root == nullptr){
        throw TreeEmpty();
    }
    this->root = this->root->remove(key);
    this->size--;
}

template<class Key, class Data>
void Tree<Key, Data>::print() {
    if(this->root != nullptr){
        this->root->print("", false);
    }
}

template<class Key, class Data>
Key * Tree<Key, Data>::get_as_sorted_array(){
    Key *result = new Key[this->size];
    int index = 0;
    if(root != nullptr){
        this->root->get_as_sorted_array(result, index);
    }
    return result;
}

template<class Key, class Data>
int Tree<Key, Data>::getSize() const {
    return size;
}



template<class Key, class Data>
int Tree<Key, Data>::realHeight(AVL_node<Key, Data>* node){
    if(node == nullptr)
        return -1;
    return 1 + std::max(realHeight(node->getLeft()), realHeight(node->getRight()));
}

template<class Key, class Data>
bool Tree<Key, Data>::validCheck(AVL_node<Key, Data>* node){
    if(node == nullptr){
        return true;
    }
    if(realHeight(node) != node->getHeight()){
        return false;
    }

    int balance = realHeight(node->getRight()) - realHeight(node->getLeft());
    if (balance > 1 || balance < -1){
        return false;
    }
    return validCheck(node->getLeft()) && validCheck(node->getRight());
}

template<class Key, class Data>
bool Tree<Key, Data>::validCheck() {
    return this->validCheck(root);
}

template<class Key, class Data>
Data* Tree<Key, Data>::operator[](const Key &key) {
    if(root == nullptr){
        return nullptr;
    }
    return (*root)[key];
}

template<class Key, class Data>
Data *Tree<Key, Data>::find_by_index(int index) {
    if(root == nullptr){
        return nullptr;
    }
    return root->find_by_index(index);
}

template<class Key, class Data>
Tree<Key, Data>::~Tree() {
    delete root;
}

#endif //DS_1_WET_TREE_H
