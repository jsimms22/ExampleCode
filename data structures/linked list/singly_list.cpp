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

int main()
{
    LinkedList* list = new LinkedList('a');

    list->insert('b');
    list->insert('c');
    list->print_list();

    list->prepend('z');
    list->print_list();
    
    delete(list);

    return 0;
}