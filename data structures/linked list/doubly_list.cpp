/*
    Example code for a doubly linked list
*/

#include<cstdlib>
#include<iostream>

struct Node // or class with public:
{
    char ch;
    Node* next; // next node in list or NULL
    Node* prev; // previous node in list or NULL
};

class LinkedList
{
public:
    LinkedList() :head{NULL} { };
    LinkedList(char ch) :head{new Node{ch,NULL,NULL}} { }
    //void insert(char ch);
    void append(char ch);
    void prepend(char ch);
    void print_list(bool reverse);

    // char get_char(Node* n) const { return n->ch; }
    Node* get_head() const { return head; }
    bool search(Node* head, char c);

private:
    Node* head;
};

void LinkedList::append(char ch)
{
    Node* new_node = new Node{ch,NULL,NULL};
    Node* ptr = this->head;

    if (head == NULL) { 
        this->head = new_node; 
        return;
    } else {
        while (ptr->next != NULL) { ptr = ptr->next; }
        ptr->next = new_node;
        new_node->prev = ptr;
        return;
    }
}

void LinkedList::prepend(char ch)
{
    Node* temp = new Node{ch,NULL,NULL};
    
    if (this->head == NULL) {
        this->head = temp; 
    } else {
        temp->next = this->head;
        this->head->prev = temp;
        this->head = temp;
    }
}

void LinkedList::print_list(bool reverse)
// false prints head -> tail
// true prints head -> tail -> head
{
    if (this->head == NULL) {
        std::cout << "empty list\n";
        return;
    }
    
    if (reverse == false) {
        Node* temp = this->head;
        while(temp->next != NULL) {   // while temp != NULL
            std::cout << temp->ch << " <-> ";
            temp = temp->next;
        }
        std::cout << temp->ch << " <->\n";
        return;
    } else if (reverse == true) {
        std::cout << "forward: ";
        Node* temp = this->head;
        while(temp->next != NULL) {   // while temp != NULL
            std::cout << temp->ch << " <-> ";
            temp = temp->next;
        }
        std::cout << temp->ch << " <->\n";

        std::cout << "reverse: ";
        while(temp->prev != NULL) {
            std::cout << temp->ch << " <-> ";
            temp = temp->prev;            
        }
        std::cout << temp->ch << " <->\n";
        return;       
    }
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
    list->print_list(false);
    list->append('b');
    list->append('c');
    list->print_list(false);

    list->prepend('z');
    list->print_list(false);
    list->print_list(true);

    char key = 'd';
    bool result = list->search(list->get_head(),key);
    if (result == true) { 
        std::cout << key << " is a part of the list\n";
    } else {
        std::cout << key << " is NOT a part of the list\n";
    }

    list->append('d');
    list->print_list(false);
    result = list->search(list->get_head(),key);
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