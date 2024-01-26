//
// Created by Gianni on 24/01/2024.
//

#ifndef DATA_STRUCTURES_ARRAY_HPP
#define DATA_STRUCTURES_ARRAY_HPP

#include <iterator>
#include <utility>

template <typename T, size_t S>
struct ArrayTraits
{
    using type = T[S];
    using is_swappable = std::is_swappable<T>;
    using is_nothrow_swappable = std::is_nothrow_swappable<T>;
};

template <typename T>
struct ArrayTraits<T, 0>
{
    struct type
    {
        [[noreturn]] T& operator[](size_t) const noexcept
        { __builtin_trap(); }
    };

    using is_swappable = std::true_type;
    using is_nothrow_swappable = std::true_type;
};

template <typename T, size_t S>
struct Array
{
    typedef T value_type;
    typedef size_t size_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    constexpr iterator begin() noexcept { return data(); }
    constexpr const_iterator begin() const noexcept { return data(); }

    constexpr iterator end() noexcept { return (data() + S); }
    constexpr const_iterator end() const noexcept { return (data() + S); }

    constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    constexpr const_reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }

    constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    constexpr const_reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }

    constexpr reference front() noexcept { return m_elements[0]; }
    constexpr const_reference front() const noexcept { return m_elements[0]; }

    constexpr reference back() noexcept { return m_elements[S - 1]; }
    constexpr const_reference back() const noexcept { return m_elements[S - 1]; }

    constexpr size_type size() const noexcept { return S; }
    constexpr bool empty() const noexcept { return S; }

    constexpr pointer data() noexcept { return m_elements; }
    constexpr const_pointer data() const noexcept { return m_elements; }

    constexpr reference at(size_t index)
    {
        if (index >= S)
            throw std::out_of_range("Array::at: index >= S\n");

        return m_elements[index];
    }

    constexpr const_reference at(size_t index) const
    {
        if (index >= S)
            throw std::out_of_range("Array::at: index >= S\n");

        return m_elements[index];
    }

    constexpr reference operator[](size_t index) { return m_elements[index]; }
    constexpr const_reference operator[](size_t index) const { return m_elements[index]; }

    constexpr void fill(const T& value)
    {
        for (iterator i = begin(); i < end(); ++i)
            *i = value;
    }

    constexpr void swap(Array& other) noexcept(ArrayTraits<T, S>::is_nothrow_swappable::value)
    {
        for (iterator i = begin(), j = other.begin(); i < end(); ++i, ++j)
            std::iter_swap(i, j);
    }

    typename ArrayTraits<T, S>::type m_elements;
};

#endif //DATA_STRUCTURES_ARRAY_HPP
