#ifndef DS_1_WET_AVL_NODE_H
#define DS_1_WET_AVL_NODE_H

#ifndef DS_WET1_AVL_node_H
#define DS_WET1_AVL_node_H
#include <iostream>


class KeyNotInTree: public std::exception{};
class KeyAlreadyInTree: public std::exception{};

// we assume key has all compare operators
template<class Key, class Data>
class AVL_node{
protected:
    Key key;
    Data data;
    int height;
    AVL_node* left;
    AVL_node* right;
    int size;

    int balance() const;

    AVL_node* rotate();
    AVL_node* LL_roll();
    AVL_node* RR_roll();
    AVL_node* LR_roll();
    AVL_node* RL_roll();

    void updateHeight();
    void updateSize();
public:
    AVL_node(Key key, Data data):key(key), data(data), height(0), left(nullptr), right(nullptr), size(1){}
    AVL_node(const AVL_node& toCopy);
    Data* getData() {return data;}
    Data* getData() const {return data;}

    int getHeight() const;
    int getSize() const;

    //AVL_node<Key, Data>* getLeft() {return left;}
    AVL_node<Key, Data>* getLeft() const {return left;}

    //AVL_node<Key, Data>* getRight() {return right;}
    AVL_node<Key, Data>* getRight() const {return right;}



    Data* operator[](const Key& key) ;
    Data* find_by_index(int index);


    AVL_node<Key, Data>* insert(const Key& key, const Data& data);
    AVL_node<Key, Data>* remove(const Key& key);

    virtual ~AVL_node();

    // for tests:
    void print(const std::string& prefix, bool isLeft);
    void get_as_sorted_array(Key *arr, int& index);
};


template<class Key, class Data>
int AVL_node<Key, Data>::balance() const {
    int leftHeight = this->left == nullptr ? -1 : this->left->height;
    int rightHeight = this->right == nullptr ? -1 : this->right->height;
    return leftHeight - rightHeight;
}


template<class Key, class Data>
AVL_node<Key, Data>::AVL_node(const AVL_node& toCopy){
    this->key = toCopy.key;
    this->data = toCopy.data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
    this->size = 1;
}

/**
 * this function always returns the root of current sub-node
 * @tparam Key
 * @tparam Data
 * @param data data pointer
 * @param key duplicate the key
 * @return the root of the new node
 */
template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::insert(const Key& key, const Data& data){
    //left case
    if(key < this->key) {
        if (this->left == nullptr){ // Check if this the right place to insert
            this->left = new AVL_node<Key, Data>(key, data);
        }
        else{
            this->left = this->left->insert(key, data);// search in left sub-node
            //here we update our son with potential new son (happens when a roll is in action)
        }
    }
        //right case
    else if(key > this->key){ // same for right
        if(this->right == nullptr) { // Check if this the right place to insert
            //add the new node to the right
            this->right = new AVL_node(key, data);
        }
        else{
            this->right = this->right->insert(key, data);
        }
    }
    else{// in case of key already in node.
        throw KeyAlreadyInTree();
    }
    size++;
    this->updateHeight();
    return this->rotate();
}

/**
 * remove node from node
 * @tparam Key
 * @tparam Data
 * @param key of the node you want to remove
 * @return new root
 */
template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::remove(const Key& key) {
    /**** remove node ****/
    //search for node in left
    if (key < this->key) {
        if (this->left != nullptr) {
            this->left = this->left->remove(key);
            this->updateHeight();
            size--;
            return this->rotate();
        } else {
            throw KeyNotInTree();
        }
    }
        //search for node in right
    else if (this->key < key) {
        if (this->right != nullptr) {
            this->right = this->right->remove(key);
            this->updateHeight();
            size--;
            return this->rotate();
        } else {
            throw KeyNotInTree();
        }
    } else {// found the value
        AVL_node<Key, Data> *newRoot;
        if (this->left == nullptr && this->right == nullptr) {
            delete this;
            return nullptr;
        } else if ((this->left == nullptr && this->right != nullptr) ||
                   (this->left != nullptr && this->right == nullptr)) {
            if(this->left){
                newRoot = this->left;
            }
            else{ //if (this->right)
                newRoot = this->right;
            }
            this->right = nullptr;
            this->left = nullptr;
            // the sons must be NULL! because otherwise it will destroy the sub-tree
            delete this;
            return newRoot;
        } else {// 2 sons case
            if(this->left->right == nullptr){
                newRoot = this->left;
                // switch this and this->left
                AVL_node<Key, Data>* temp = this->left->left;
                this->left->left = this;
                this->left->right = this->right;
                this->right = nullptr;
                this->left = temp;
            } else {
                AVL_node<Key, Data>* new_root_father = this->left;
                while (new_root_father->right->right != nullptr){
                    new_root_father = new_root_father->right;
                }
                newRoot = new_root_father->right;
                // switch this and new_root_father->right
                AVL_node<Key, Data>* temp = new_root_father->right->left;
                new_root_father->right = this;
                newRoot->right = this->right;
                newRoot->left = this->left;
                this->right = nullptr;
                this->left = temp;
            }
            // recursive call
            newRoot->left =  newRoot->left->remove(key);
            newRoot->updateHeight();
            newRoot->updateSize();
            return newRoot->rotate();
        }
    }
}

//***********************************************************************/
//   Rolls

/**
 * rotates the node only if needed else do nothing
 * @tparam Key
 * @tparam Data
 * @return the new root
 */
template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::rotate() {
    //deciding which roll is needed

    // LR LL cases
    if(balance() == 2){
        if(this->left->balance() >= 0){// LL case
            return this->LL_roll();
        }
        if(this->left->balance() == -1){// LR case
            return this->LR_roll();
        }
    }
        // LR LL cases
    else if(balance() == -2){
        if(this->right->balance() <= 0){// RR case
            return this->RR_roll();
        }
        if(this->right->balance() == 1){// RL case
            return this->RL_roll();
        }
    }
    return this;
}


template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::LL_roll(){
    AVL_node<Key, Data>* newRoot = this->left;
    this->left = newRoot->right;
    newRoot->right = this;

    // update height and size
    this->updateHeight();
    newRoot->updateHeight();

    this->updateSize();
    newRoot->updateSize();
    return newRoot;
}


template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::RR_roll(){
    AVL_node<Key, Data>* newRoot = this->right;
    this->right = newRoot->left;
    newRoot->left = this;

    // update height and size
    this->updateHeight();
    newRoot->updateHeight();

    this->updateSize();
    newRoot->updateSize();
    return newRoot;
}


template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::LR_roll(){
    this->left = this->left->RR_roll();
    return this->LL_roll();
}

template<class Key, class Data>
AVL_node<Key, Data>* AVL_node<Key, Data>::RL_roll(){
    this->right = this->right->LL_roll();
    return this->RR_roll();
}
/**************************************************************************/


template<class Key, class Data>
void AVL_node<Key, Data>::updateHeight(){
    if (this == nullptr)
        return;
    int leftHeight = this->left == nullptr ? -1 : this->left->height;
    int rightHeight = this->right == nullptr ? -1 : this->right->height;
    this->height = 1 + std::max(rightHeight , leftHeight);
}

template<class Key, class Data>
void AVL_node<Key, Data>::updateSize(){
    if (this == nullptr)
        return;
    int leftSize = this->left == nullptr ? 0 : this->left->size;
    int rightSize = this->right == nullptr ? 0 : this->right->size;
    this->size = 1 + leftSize + rightSize;
}


template<class Key, class Data>
int AVL_node<Key, Data>::getHeight() const {
    return height;
}

template<class Key, class Data>
AVL_node<Key, Data>::~AVL_node() {
    delete this->left;
    delete this->right;
}

/**
 * find by a key
 * @tparam Key
 * @tparam Data
 * @param key
 * @return data or nullptr if doesn't exist
 */
template<class Key, class Data>
Data* AVL_node<Key, Data>::operator[](const Key& key) {
    if(this->key == key){
        return &this->data;
    }
    if(this->right != nullptr){
        if(this->key < key) {
            return (*(this->right))[key];
        }
    }

    if(this->left != nullptr){
        if(this->key > key){
            return (*(this->left))[key];
        }
    }
    return nullptr;
}


template<class Key, class Data>
Data *AVL_node<Key, Data>::find_by_index(int index) {
    int current_index = this->left == nullptr ? 0 : this->left->size;
    AVL_node<Key, Data>* current = this;
    while (current != nullptr && current_index != index) {
        if (current_index < index) {
            current = current->right;
            current_index++;
            if (current != nullptr && current->left != nullptr){
                current_index += current->left->size;
            }
        }
        else if (current_index > index) {
            current = current->left;
            current_index--;
            if (current != nullptr && current->right != nullptr) {
                current_index -= current->right->size;
            }
        }
    }
    if(current == nullptr){
        return nullptr;
    }
    return &current->data;
}


template<class Key, class Data>
void AVL_node<Key, Data>::print(const std::string& prefix, bool isLeft)
{
    std::cout << prefix;
    std::cout << (isLeft ? "L--" : "R--" );
    // print the value of the node
    std::cout << this->key << std::endl;
    // enter the next tree level - left and right branch
    if(this->left != nullptr)
        this->left->print( prefix + (isLeft ? "L   " : "    "), true);
    if(this->right != nullptr)
        this->right->print( prefix + (isLeft ? "L   " : "    "), false);
}

template<class Key, class Data>
void AVL_node<Key, Data>::get_as_sorted_array(Key * arr, int& index){
    if(this->left != nullptr)
        this->left->get_as_sorted_array(arr, index);
    arr[index] = this->key;
    index++;
    if(this->right != nullptr)
        this->right->get_as_sorted_array(arr, index);
}

template<class Key, class Data>
int AVL_node<Key, Data>::getSize() const {
    return size;
}


template<class Key, class Data>
void AVL_node<Key, Data>::inOrderTraverse(AVL_node<Key, Data>) {
    std::cout << prefix;
    std::cout << (isLeft ? "L--" : "R--");
    // print the value of the node
    std::cout << this->key << std::endl;
    // enter the next tree level - left and right branch
    if (this->left != nullptr)
        this->left->print(prefix + (isLeft ? "L   " : "    "), true);
    if (this->right != nullptr)
        this->right->print(prefix + (isLeft ? "L   " : "    "), false);
}

#endif //DS_WET1_AVL_node_H
#endif //DS_1_WET_AVL_NODE_H
