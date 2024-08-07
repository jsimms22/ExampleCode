#include <iostream>
#include <memory>

template <typename UNIT>
class Node
{
public:
    UNIT m_data;
    std::unique_ptr<Node<UNIT>> m_next;
    Node(UNIT value) :m_data{value}, m_next{nullptr} { }
    ~Node() { std::cout << "Destroyed Node with data: " << this->m_data << std::endl; }
};

// forward declaration
template <typename UNIT>
class List;

// must forward declare to use friend on a template overload
template <typename UNIT>
std::ostream& operator<<(std::ostream &os, const List<UNIT> &list);

template <typename UNIT>
class List
{
private:
    std::unique_ptr<Node<UNIT>> m_head;
public:
    List() :m_head{nullptr} { }
    void push(UNIT value) 
    {
        auto temp = std::make_unique<Node<UNIT>>(value);
        if (m_head) {
            temp->m_next = std::move(m_head);
            m_head = std::move(temp);
        } else {
            m_head = std::move(temp);
        }
    }
    void pop() { }
    void clean()
    {
        while(m_head) {
            m_head = std::move(m_head->m_next);
        }
    }
    friend std::ostream& operator<< <UNIT>(std::ostream &os, const List<UNIT> &list);
    ~List() { clean(); }
};

template <typename UNIT>
std::ostream& operator<<(std::ostream &os, const List<UNIT> &list)
{
    Node<UNIT> *head = list.m_head.get();
    while(head) {
        os << head->m_data << ' ';
        head = head->m_next.get();
    }

    return os;
}

int main()
{
    List list = List<int>();

    for (int i = 0; i < 10; ++i) { list.push(i); }

    std::cout << list << std::endl;

    return 0;
}