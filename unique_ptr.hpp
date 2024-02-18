//
// Created by Gianni on 15/02/2024.
//

#ifndef DATA_STRUCTURES_UNIQUE_PTR_HPP
#define DATA_STRUCTURES_UNIQUE_PTR_HPP

#include <type_traits>


template <typename T>
struct default_delete
{
    constexpr default_delete() noexcept = default;

    template<typename U>
    constexpr default_delete(const default_delete<U>&) noexcept {}

    constexpr void operator()(T* ptr) const
    {
        static_assert(!std::is_void<T>::value,
                "default_delete::operator(): attempt to delete void* doesn't call destructor of T");

        static_assert(sizeof(T) > 0,
                "default_delete::operator(): T is incomplete type");

        delete ptr;
    }
};


template <typename T, typename Deleter = default_delete<T>>
class unique_ptr
{
public:
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;

public:
    constexpr unique_ptr() noexcept
        : m_ptr()
        , m_deleter()
    {
    }

    constexpr unique_ptr(std::nullptr_t) noexcept
        : unique_ptr()
    {
    }

    constexpr explicit unique_ptr(pointer ptr) noexcept
        : m_ptr(ptr)
        , m_deleter()
    {
    }

    constexpr unique_ptr(pointer ptr, const Deleter& deleter) noexcept
        : m_ptr(ptr)
        , m_deleter(deleter)
    {
    }

    constexpr ~unique_ptr() { reset(); }

    constexpr unique_ptr(unique_ptr&& other) noexcept
        : m_ptr(other.release())
        , m_deleter(std::move(other.m_deleter))
    {
    }

    template<typename U, typename D>
    constexpr unique_ptr(unique_ptr<U, D>&& other) noexcept
        : m_ptr(other.release())
        , m_deleter(std::move(other.get_deleter()))
    {
    }

    constexpr unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        if (this != &other)
        {
            reset(other.release());
            m_deleter = std::move(other.get_deleter());
        }

        return *this;
    }

    template<typename U, typename D>
    constexpr unique_ptr& operator=(unique_ptr<U, D>&& other) noexcept
    {
        if (this != &other)
        {
            reset(other.release());
            m_deleter = std::move(other.get_deleter());
        }

        return *this;
    }

    constexpr unique_ptr& operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    constexpr pointer release() noexcept
    {
        pointer temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    constexpr void reset(pointer ptr = pointer()) noexcept
    {
        if (ptr == m_ptr) return;

        pointer old_ptr = m_ptr;
        m_ptr = ptr;

        if (old_ptr)
        {
            m_deleter(old_ptr);
        }
    }

    constexpr void swap(unique_ptr& other) noexcept
    {
        std::swap(this->m_ptr, other.m_ptr);
        std::swap(this->m_deleter, other.m_deleter);
    }

    constexpr pointer get() const noexcept { return m_ptr; }

    constexpr Deleter& get_deleter() noexcept { return m_deleter; }
    constexpr const Deleter& get_deleter() const noexcept { return m_deleter; }

    constexpr explicit operator bool() const noexcept { return m_ptr != nullptr; }

    constexpr reference operator*() noexcept { return *m_ptr; }
    constexpr const_reference operator*() const noexcept { return *m_ptr; }

    constexpr pointer operator->() const noexcept { return m_ptr; }

private:
    pointer m_ptr;
    Deleter m_deleter;
};


template <typename T, typename... Args>
constexpr inline unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //DATA_STRUCTURES_UNIQUE_PTR_HPP
