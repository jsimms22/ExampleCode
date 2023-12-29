/*
    Binary Tree that stores values
    -Left Child's value is less than parent's value
    -Right Child's value is equal to or greater than parent's value
*/

#include<cstdlib>
#include<iostream>
#include<iomanip>

struct Node // or class with public:
{
    int m_value;
    Node* m_parent;   // parent node
    Node* m_left;     // left child node
    Node* m_right;    // right child node
};

const Node* get_parent(Node* node) { return node->m_parent; }
const Node* get_lchild(Node* node) { return node->m_left; }
const Node* get_rchild(Node* node) { return node->m_right; }

class BinaryTree
{   
public:
    BinaryTree() :m_root{NULL} { }
    BinaryTree(int _value) 
        :m_root{new Node{_value,NULL,NULL,NULL}} { }
    void insert(int _value);
    void search(); /* TODO */

private:
    Node* m_root;
};

void BinaryTree::insert(int _value)
// 
{
    Node* temp = new Node{_value,NULL,NULL,NULL};

    // need to handle cases:
    // -root is null
    // -traverse and find appropriate child to place new node
    // -deteremine if a swap between root and temp is required
    if (this->m_root == NULL) {
        this->m_root = temp;
    } else {

    }
}

int main()
{
    BinaryTree* btree = new BinaryTree(10);

    

}