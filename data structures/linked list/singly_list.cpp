/*
    Example code for a singly linked list
*/

#include<cstdlib>
#include<iostream>

struct Node // or class with public:
{
    char ch;
    Node* next; // next node in list or NULL
};

class LinkedList
{
public:
    LinkedList(char ch) :head{new Node{ch,NULL}} { }
    void insert(char ch);
    void prepend(char ch);
    void print_list();

    // char get_char(Node* n) const { return n->ch; }
    Node* get_head() const { return head; }
    bool search(Node* head, char c);

private:
    Node* head;
};

void LinkedList::insert(char ch)
{
    Node* temp;
    Node* ptr;
    temp = new Node{ch,NULL};
    
    if (this->head == NULL) {
        this->head = temp; 
    } else {
        ptr = this->head;
        while (ptr->next) { ptr = ptr->next; }
        ptr->next = temp;
    }
}

void LinkedList::prepend(char ch)
{
    Node* temp = new Node{ch,NULL};
    
    if (this->head == NULL) {
        this->head = temp; 
    } else {
        temp->next = this->head;
        this->head = temp;
    }
}

void LinkedList::print_list()
{
    Node* temp = this->head;
    while(temp) {   // while temp != NULL
        std::cout << temp->ch << "->";
        temp = temp->next;
    }
    std::cout << '\n';
}

bool LinkedList::search(Node* head, char c)
// O(N) recursive seach algorithm
{
    if (head == NULL) { return false; }
    if (head->ch == c) { return true; }

    return search(head->next,c);
}

void tests(LinkedList* list)
{
    list->insert('b');
    list->insert('c');
    list->print_list();

    list->prepend('z');
    list->print_list();

    char key = 'd';
    bool result = list->search(list->get_head(),key);
    if (result == true) { 
        std::cout << key << " is a part of the list\n";
    } else {
        std::cout << key << " is NOT a part of the list\n";
    }
}

int main()
{
    LinkedList* list = new LinkedList('a');
    tests(list);
    delete(list);

    return 0;
}