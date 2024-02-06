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

    const_node* m_node;
};

template <typename T>
class SinglyLinkedList
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
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

    iterator begin() noexcept { return iterator(m_head); }
    const_iterator begin() const noexcept { return const_iterator(m_head); }

    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }

    void clear()
    {
        while (m_head)
        {
            auto temp = m_head;
            m_head = m_head->m_next;
            delete temp;
        }
    }

    void print() const
    {
        auto current = m_head;

        while (current)
        {
            std::cout << current->m_value << '\n';
            current = current->m_next;
        }
    }

private:
    node* m_head;
};

#endif //DATA_STRUCTURES_SINGLY_LINKED_LIST_HPP
