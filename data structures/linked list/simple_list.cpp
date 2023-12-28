/*
    Example code for simple singly linked list
*/

#include<cstdlib>
#include<iostream>

struct Node // or class with public:
{
    char ch;
    Node* next; // next node in list or NULL
};

void print_list(Node* head)
// simple function to print list, starting at a node 
// insert head node for whole list
{
    Node* temp = head;
    while(temp) {   // while temp != NULL
        std::cout << temp->ch << "->";
        temp = temp->next;
    }
    std::cout << '\n';
}

Node* add_new_node(char ch)
// returns newly created node
{
    Node* result = new Node();
    result->ch = ch;
    result->next = NULL;
    return result;
}

int main()
{
    Node n1, n2, n3;
    Node* head1;

    n1.ch = 'a';
    n2.ch = 'b';
    n3.ch = 'c';

    // adding nodes to list manually
    head1 = &n3;
    n3.next = &n2; 
    n2.next = &n1;
    n1.next = add_new_node('d');

    print_list(head1);

    // dynamically adding nodes

    std::cout << "\nusing 'new' keyword to add nodes\n";

    // creating list: head2 -> node -> node
    Node* head2 = new Node{'1',new Node{'2',NULL}};

    print_list(head2);

    return 0;
}