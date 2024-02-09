//
// Created by Gianni on 26/01/2024.
//

#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_HPP
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_HPP

#include <cstdint>
#include <utility>


template <typename T>
struct SinglyListNode
{
    T m_value;
    SinglyListNode* m_next;

    SinglyListNode(const T& value = T(), SinglyListNode* next = nullptr)
        : m_value(value), m_next(next) {}

    SinglyListNode(SinglyListNode&& other) noexcept
        : m_value(std::move(other.m_value))
        , m_next(other.m_next)
    { other.m_next = nullptr; }

    SinglyListNode& operator=(SinglyListNode&& other) noexcept
    {
        if (this != &other)
        {
            m_value = std::move(other.m_value);
            m_next = other.m_next;

            other.m_next = nullptr;
        }

        return *this;
    }

    SinglyListNode(const SinglyListNode&) = delete;
    SinglyListNode& operator=(const SinglyListNode&) = delete;
};


template <typename T>
struct SinglyLinkedListIterator
{
    using iterator = SinglyLinkedListIterator<T>;
    using node = SinglyListNode<T>;

    using pointer = T*;
    using reference = T&;

    SinglyLinkedListIterator() : m_node(nullptr) {}
    SinglyLinkedListIterator(node* node) : m_node(node) {}

    pointer operator->() const noexcept
    {
        return &(m_node->m_value);
    }

    reference operator*() const noexcept
    {
        return m_node->m_value;
    }

    iterator& operator++() noexcept
    {
        m_node = m_node->m_next;
        return *this;
    }

    iterator operator++(int) noexcept
    {
        iterator temp = *this;
        m_node = m_node->m_next;
        return temp;
    }

    bool operator==(const iterator& other) const noexcept
    {
        return m_node == other.m_node;
    }

    bool operator!=(const iterator& other) const noexcept
    {
        return m_node != other.m_node;
    }

    operator bool() const noexcept
    {
        return m_node != nullptr;
    }

    node* m_node;
};


template <typename T>
struct SinglyLinkedListConstIterator
{
    using const_iterator = SinglyLinkedListConstIterator<T>;
    using const_node = const SinglyListNode<T>;

    using const_pointer = const T*;
    using const_reference = const T&;

    SinglyLinkedListConstIterator() : m_node(nullptr) {}
    SinglyLinkedListConstIterator(const_node* node) : m_node(node) {}

    const_pointer operator->() const noexcept
    {
        return &(m_node->m_value);
    }

    const_reference operator*() const noexcept
    {
        return m_node->m_value;
    }

    const_iterator& operator++() noexcept
    {
        m_node = m_node->m_next;
        return *this;
    }

    const_iterator operator++(int) noexcept
    {
        const_iterator temp = *this;
        m_node = m_node->m_next;
        return temp;
    }

    bool operator==(const const_iterator & other) const noexcept
    {
        return m_node == other.m_node;
    }

    bool operator!=(const const_iterator& other) const noexcept
    {
        return m_node != other.m_node;
    }

    operator bool() const noexcept
    {
        return m_node != nullptr;
    }

    const_node* m_node;
};

template <typename T>
class SinglyLinkedList
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using node = SinglyListNode<T>;
    using iterator = SinglyLinkedListIterator<T>;
    using const_iterator = SinglyLinkedListConstIterator<T>;

public:
    SinglyLinkedList() noexcept : m_head(nullptr) {}

    SinglyLinkedList(size_t count, const_reference value)
        : m_head(nullptr)
    {
        while (count--) push_back(value);
    }

    SinglyLinkedList(size_t count)
        : SinglyLinkedList(count, value_type())
    {
    }

    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList& other)
        : m_head(nullptr)
    {
        for (auto itr = other.begin(); itr != other.end(); ++itr)
            push_back(*itr);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other)
    {
        clear();

        if (this != &other)
        {
            for (auto itr = other.begin(); itr != other.end(); ++itr)
                push_back(*itr);
        }

        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : m_head(other.m_head)
    {
        other.m_head = nullptr;
    }

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            m_head = other.m_head;
            other.m_head = nullptr;
        }

        return *this;
    }

    iterator begin() noexcept { return iterator(m_head); }
    iterator end() noexcept { return iterator(nullptr); }

    const_iterator cbegin() const noexcept { return const_iterator(m_head); }
    const_iterator cend() const noexcept { return const_iterator(nullptr); }

    reference front()
    {
        if (!m_head) __builtin_trap();
        return m_head->m_value;
    }
    const_reference front() const
    {
        if (!m_head) __builtin_trap();
        return m_head->m_value;
    }

    reference back()
    {
        if (!m_head) __builtin_trap();

        auto current = m_head;

        while (current->m_next)
            current = current->m_next;

        return current->m_value;
    }

    const_reference back() const
    {
        if (!m_head) __builtin_trap();

        auto current = m_head;

        while (current->m_next)
            current = current->m_next;

        return current->m_value;
    }

    bool empty() const noexcept { return m_head == nullptr; }

    void push_front(const_reference value)
    {
        node* new_node = new node(value);

        new_node->m_next = m_head;

        m_head = new_node;
    }

    void push_back(const_reference value)
    {
        node* new_node = new node(value);

        if (!m_head)
        {
            m_head = new_node;
            return;
        }

        auto current = m_head;

        while (current->m_next)
            current = current->m_next;

        current->m_next = new_node;
    }

    void pop_front()
    {
        if (m_head == nullptr) __builtin_trap();

        auto temp = m_head;

        m_head = m_head->m_next;

        delete temp;
    }

    void pop_back()
    {
        if (m_head == nullptr) __builtin_trap();

        if (m_head->m_next == nullptr)
        {
            delete m_head;
            m_head = nullptr;
            return;
        }

        if (m_head->m_next->m_next == nullptr)
        {
            delete m_head->m_next;
            m_head->m_next = nullptr;
            return;
        }

        auto current = m_head;

        while (current->m_next->m_next)
            current = current->m_next;

        delete current->m_next;
        current->m_next = nullptr;
    }

    void reverse()
    {
        node* current = m_head;
        node* next = nullptr;
        node* prev = nullptr;

        while (current)
        {
            next = current->m_next;
            current->m_next = prev;
            prev = current;
            current = next;
        }

        m_head = prev;
    }

    bool erase(const_reference value)
    {
        if (!m_head) return false;

        if (m_head->m_value == value)
        {
            auto temp = m_head->m_next;
            delete m_head;
            m_head = temp;
            return true;
        }

        auto current = m_head;

        while (current->m_next != nullptr && current->m_next->m_value != value)
            current = current->m_next;

        if (current->m_next == nullptr)
            return false;

        auto temp = current->m_next->m_next;

        delete current->m_next;
        current->m_next = temp;

        return true;
    }

    void erase_all_of(const_reference value)
    {
        while (m_head && m_head->m_value == value)
        {
            auto next = m_head->m_next;
            delete m_head;
            m_head = next;
        }

        auto current = m_head;

        while (current && current->m_next)
        {
            if (current->m_next->m_value == value)
            {
                auto next = current->m_next->m_next;
                delete current->m_next;
                current->m_next = next;
            }
            else
            {
                current = current->m_next;
            }
        }
    }

    bool search(const_reference value) const
    {
        auto current = cbegin();

        while (current)
        {
            if (*current == value)
                return true;

            ++current;
        }

        return false;
    }

    void clear()
    {
        while (m_head)
        {
            auto temp = m_head;
            m_head = m_head->m_next;
            delete temp;
        }
    }

private:
    node* m_head;
};

#endif //DATA_STRUCTURES_SINGLY_LINKED_LIST_HPP
