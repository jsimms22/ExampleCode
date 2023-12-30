/*
    Binary Tree that stores values
    -Left Child's value is less than parent's value
    -Right Child's value is equal to or greater than parent's value
*/

#include<cstdlib>
#include<iostream>
#include<iomanip>

#define COUNT 10

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
    void insert(Node* ptr, int _value);
    void search(); /* TODO */
    Node* get_root() const { return m_root; }

private:
    Node* m_root;
};

void BinaryTree::insert(Node* root, int _value)
// 
{
    Node* temp = new Node{_value,NULL,NULL,NULL};
    Node* ptr = root;
    // need to handle cases:
    // -root is null
    // -traverse and find appropriate child to place new node
    // -deteremine if a swap between root and temp is required
    if (root == NULL) {
        root = temp;
        //delete(temp);
        std::cout << "root = temp\n";
        return;
    } else if (_value <= root->m_value) {
        if (root->m_left == NULL) {
            root->m_left = temp;
            //delete(temp);
            std::cout << "root->m_left = temp\n";
            return;
        } else {
            ptr = root->m_left;
            //delete(temp);
            std::cout << "ptr = left, calling insert()\n";
            insert(ptr,_value);
        }
    } else if (_value > root->m_value) {
        if (root->m_right == NULL) {
            root->m_right = temp;
            //delete(temp);
            std::cout << "root->m_right = temp\n";
            return;
        } else {
            ptr = root->m_right;
            //delete(temp);
            std::cout << "ptr = right, calling insert()\n";
            insert(ptr,_value);
        }
    } else {
        delete(temp);
        std::cout << "returning\n";
        return;
    }
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Node* root, int space)
{
    // Base case
    if (root == NULL) { return; }
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->m_right, space);
 
    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->m_value << "\n";
 
    // Process left child
    print2DUtil(root->m_left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int main()
{
    BinaryTree* btree = new BinaryTree(10);
    btree->insert(btree->get_root(),5);
    btree->insert(btree->get_root(),11);
    btree->insert(btree->get_root(),11);
    btree->insert(btree->get_root(),9);
    btree->insert(btree->get_root(),4);
    btree->insert(btree->get_root(),15);
    btree->insert(btree->get_root(),12);
    btree->insert(btree->get_root(),'a'); //inserts ASCII value for 'a' by converting char->int

    print2D(btree->get_root());

    delete(btree);

    return 0;
}