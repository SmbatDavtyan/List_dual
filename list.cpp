
#include "list.hpp"

#include <cassert>

class list::node
{
public:
    value_type m_value;
    node* m_next;
    node* m_prev;
public:
    node(value_type v, node* n, node * p)
        : m_value(v)
        , m_next(n)
        , m_prev(p)
    {
    }

    ~node()
    {
    }
};

std::ostream& operator<<(std::ostream& out, const list& l)
{
    list::node* current = l.m_head;
    while (current != nullptr) {
        out << current->m_value << " ";
        current = current->m_next;
    }
    return out;
}

list::size_type list::size() const
{
    node* current = m_head;
    size_type count = 0;
    while (current != nullptr) {
        current = current->m_next;
        ++count;
    }
    return count;
}

bool list::empty() const
{
    return (m_head == nullptr);
}

void list::push_front(const value_type& value) // O(1)
{
    node* new_node = new node(value, m_head, nullptr);
    m_head = new_node;
}

void list::push_back(const value_type& value) // O(n)
{
    node* new_node = new node(value, nullptr, m_head);
    if (m_head == nullptr) {
        m_head = new_node;
    } else {
        assert(size() >= 1);
        node* last = access_helper(size() - 1);
        assert(last != nullptr);
        assert(last->m_next == nullptr);
        last->m_next = new_node;
        new_node->m_prev = last;
    }
}

void list::insert(const size_type& index, const value_type& value)
{
    assert(index >= 0);
    assert(index <= size());
    node* new_node = new node(value, nullptr, nullptr);
    if (index == 0) {
        push_front(value);
    } else if (index == size()) {
        push_back(value);
    } else {
        assert(index >= 1);
        node* current = access_helper(index - 1);
        assert(current != nullptr);
        new_node->m_next = current->m_next;
        current->m_next = new_node;
        new_node->m_prev = current;
        current->m_next->m_prev = new_node;
    }
}

void list::pop_front()
{
    if (m_head == nullptr)
    {
        return;
    }
    node* n = m_head;
    m_head = m_head->m_next;

    if (m_head != nullptr && m_head->m_next)
    {
        m_head->m_next->m_prev = nullptr;
    }
    delete n;
}

void list::pop_back()
{
    assert(m_head != nullptr);
    if (m_head->m_next == nullptr) {
        pop_front();
        assert(m_head == nullptr);
    } else {
        assert(size() >= 2);
        node* last = access_helper(size() - 1);
        assert(last != nullptr);
        last->m_prev->m_next = nullptr;
        delete last;
    }
}

list::node* list::access_helper(const size_type& index) const
{
    assert(index >= 0);
    assert(index < size());
	node* current = m_head;
    for (size_type i = 0; i < index; ++i) {
        assert(current != nullptr);
        current = current->m_next;
	}
    assert(current != nullptr);
	return current;
}

list::value_type list::access(const size_type& index) const
{
    node* n = access_helper(index);
    assert(n != nullptr);
	return n->m_value;
}

list::list()
    : m_head(nullptr)
{
}

list::list(size_type n, const value_type& default_value)
    : m_head(nullptr)
{
    node* current = nullptr;
    for (size_type i = 0; i < n; ++i) {
        node* new_node = new node(default_value, nullptr, nullptr);
        if (current != nullptr) {
            current->m_next = new_node;
            new_node->m_prev = current;
        } else {
            assert(m_head == nullptr);
            m_head = new_node;
        }
        current = new_node;
    }
}

list::list(const list& b)
    : m_head(nullptr)
{
    *this = b;
}

const list& list::operator=(const list& c)
{
    destroy_list();

    node* c_current = c.m_head;

    while (c_current != nullptr)
    {
        push_back(c_current->m_value);

        c_current = c_current->m_next;
    }

    return *this;
}

list::~list()
{
    destroy_list();
}

void list::destroy_list()
{
    while (!empty())
    {
        pop_front();
    }
}
