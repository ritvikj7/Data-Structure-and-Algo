/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file. IMPORTANT: read avltree.h to understand
 * what to do in this lab.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL)
        subtree = new Node(key, value);
    else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }


    // Rebalance tree after insertion (don't remove this)
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* node)
{
    if(node == NULL){
        return;
    } else {
        node->height = 1 + max(height(node->right), height(node->left));
    }
}



template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    Node* newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;

    // TODO: update the heights for t->left and t (in that order)
    updateHeight(t->left);
    updateHeight(t);
}


template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    Node* newSubRoot = t->left;
    t->left =  newSubRoot->right;
    newSubRoot->right = t;
    t = newSubRoot;

    updateHeight(t->right);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    // HINT: you should make use of the other functions defined in this file,
    // instead of manually changing the pointers again
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
   // TODO: your code here
   rotateRight(t->right);
   rotateLeft(t);
}



template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{   
    int balance = height(subtree->right) - height(subtree->left);
    if(abs(balance) <= 1){
        updateHeight(subtree);
    } else {
        if(balance == -2){
            int leftBalance = height(subtree->left->right) - height(subtree->left->left);
            if(leftBalance == -1){
                rotateRight(subtree);
            } else {
                rotateLeftRight(subtree);
            }
        } else if (balance == 2){
            int rightBalance = height(subtree->right->right) - height(subtree->right->left);
            if(rightBalance == 1){
                rotateLeft(subtree);
            } else {
                rotateRightLeft(subtree);
            }
        }
    }


    // First attempt at writting my own implementation without looking at notes... 
    // too lazy to fix, but super close to the actual solution.

    // int leftSubtreeHeight = height(subtree->left);
    // int rightSubtreeHeight = height(subtree->right);

    // if(abs(leftSubtreeHeight - rightSubtreeHeight) == 1 || abs(leftSubtreeHeight - rightSubtreeHeight) == 0){
    //     updateHeight(subtree);
    // } else {
    //     if(leftSubtreeHeight - rightSubtreeHeight == 2){
    //         if(height(subtree->left->right) - height(subtree->left->left) == -1){
    //             rotateRight(subtree);
    //         } else {
    //             rotateLeftRight(subtree);
    //         }
    //     } else if (leftSubtreeHeight - rightSubtreeHeight == -2){
    //         if(height(subtree->left->right) - height(subtree->left->left) == 1){
    //             rotateLeft(subtree);
    //         } else {
    //             rotateRightLeft(subtree);
    //         }
    //     }
    // }
}







template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}



template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        /* Reached the node that we need to delete */
        if (subtree->left == NULL && subtree->right == NULL) {
            /* Case 1: Node to remove has no children */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node* rightMostNode = subtree->left;
            while(rightMostNode->right != NULL){
                rightMostNode = rightMostNode->right;
            }
            swap(subtree, rightMostNode);
            remove(subtree->left, key);
        } else {
            /* Case 3: Node to remove has one child */
            Node* curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}
