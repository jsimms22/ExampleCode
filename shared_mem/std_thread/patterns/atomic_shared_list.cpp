#include <thread>
#include <vector>
#include <atomic>
#include <vector>
#include <iostream>
#include <memory>

struct Node
{   // our node struct
    int m_data;
    std::shared_ptr<Node> m_next;
    Node(int value) :m_data{value}, m_next{nullptr} { }
    ~Node() { std::cout << "Destroyed Node with data: " << this->m_data << std::endl; }
};

// head of our list
std::atomic<std::shared_ptr<Node>> head;

// lazy to add to our list
void push_front(size_t x) 
{
    // create a local temp node
    std::shared_ptr<Node> new_n = std::make_shared<Node>(x);
    // get our head node
    std::shared_ptr<Node> old_h = head;
    // insert of new node to the front
    do {new_n.get()->m_next.swap(old_h); }
    // if head == old_h, CAS: head = new_n, return true
    // else old_h = head, return false
    while (!head.compare_exchange_strong(old_h,new_n));
}

/* could add an atomic queue add to load many values more than your thread count */

// print list
void print_list(const std::shared_ptr<Node>& head)
{
    Node* temp = head.get();
    while (temp) {
        std::cout << temp->m_data << std::endl;
        temp = temp->m_next.get();
    }
}

int main()
{
    std::vector<std::jthread> thread_bin(16);
    int itr{};
    for (auto& thr : thread_bin) {
        ++itr;
        thr = std::jthread(push_front,itr);
        // std::cout << "inserted value: " << itr << std::endl;
    }
    for (auto& thr : thread_bin) { thr.join(); }

    print_list(head);
}