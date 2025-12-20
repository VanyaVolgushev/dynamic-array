#pragma once

#include <type_traits>
#include <cassert>
#include <iterator>

template<typename T>
class MyDynamicArray final {
public:
    MyDynamicArray();
    MyDynamicArray(size_t capacity);
    ~MyDynamicArray();

    size_t insert(T const& value);
    size_t insert(size_t index, T const& value);
    void remove(size_t index);

    T& operator[] (size_t index);
    T const& operator[] (size_t index) const;

    size_t size() const;
    size_t capacity() const;
    
class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    
        Iterator(size_t i = 0, T* p = nullptr) : offset(i), p(p) {}
    
        bool operator==(Iterator const& rhs) const {
            return p == rhs.p && offset == rhs.offset;
        }
    
        bool operator!=(Iterator const& rhs) const {
            return !(*this == rhs);
        }
    
        Iterator& operator++() { ++offset; return *this; }
        Iterator  operator++(int) { Iterator tmp(*this); ++(*this); return tmp; }
    
        Iterator& operator--() { --offset; return *this; }
        Iterator  operator--(int) { Iterator tmp(*this); --(*this); return tmp; }
    
        // return a reference so iterator behaves like a normal container iterator
        reference operator*() const { return *(p + offset); }
        pointer   operator->() const { return p + offset; }
    
    private:
        T*     p;
        size_t offset;
    };
    
    // add typedef for reverse iterator and the rbegin/rend functions
    using reverse_iterator = std::reverse_iterator<Iterator>;
    
    Iterator begin() { return Iterator(0, _data); }
    Iterator end()   { return Iterator(_size, _data); }
    
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend()   { return reverse_iterator(begin()); }
    
private:
    static constexpr size_t DEFAULT_CAPACITY = 16;
    static constexpr float RESIZE_FACTOR = 2.0f;
    size_t _capacity;
    size_t _size;
    T* _data;

    void upsize();
};

// ------------------------------------------------------------------------
// ------------IMPLEMENTATION----------------------------------------------
// ------------------------------------------------------------------------

template<typename T>
MyDynamicArray<T>::MyDynamicArray() : MyDynamicArray(DEFAULT_CAPACITY) {};

template<typename T>
MyDynamicArray<T>::MyDynamicArray(size_t capactiy) {
    _capacity = capactiy;
    _size = 0;
    _data = static_cast<T*>(malloc(sizeof(T) * _capacity));
}

template<typename T>
MyDynamicArray<T>::~MyDynamicArray() {
    for (size_t i = 0; i < _size; i++)
    {
        _data[i].~T();
    }
    free(_data);
}

template <typename T>
size_t MyDynamicArray<T>::insert(T const &value)
{
    if (_size >= _capacity) {
        upsize();
    }
    new (&_data[_size]) T(value);
    _size++;
    return _size;
}

template <typename T>
size_t MyDynamicArray<T>::insert(size_t index, T const &value)
{
    assert(index <= _size);
    if (_size >= _capacity) {
        upsize();
    }
    for (size_t i = _size; i > index; i--) {
        new (&_data[i]) T(std::move(_data[i - 1]));
    }
    new (&_data[index]) T(value);
    _size++;
    return index;
}

template <typename T>
void MyDynamicArray<T>::remove(size_t index)
{
    assert(index < _size);
    if (std::is_destructible<T>::value && !std::is_trivially_destructible<T>::value) {
        _data[index].~T();
    }
    for (size_t i = index; i < _size - 1; i++) {
        new (&_data[i]) T(std::move(_data[i + 1]));
    }
    _size--;
}

template <typename T>
T& MyDynamicArray<T>::operator[](size_t index) {
    assert(index < _size);
    return _data[index];
}

template <typename T>
T const& MyDynamicArray<T>::operator[](size_t index) const {
    assert(index < _size);
    return _data[index];
}

template <typename T>
size_t MyDynamicArray<T>::size() const
{
    return _size;
}

template <typename T>
size_t MyDynamicArray<T>::capacity() const
{
    return _capacity;
}

template <typename T>
void MyDynamicArray<T>::upsize() {
    size_t new_capacity = _capacity * RESIZE_FACTOR;
    T* new_data = (T*)malloc(sizeof(T) * new_capacity);
    for (size_t i = 0; i < _size; i++) {
        new (&new_data[i]) T(std::move(_data[i]));
    }
    free(_data);
    _data = new_data;
    _capacity = new_capacity;
};
