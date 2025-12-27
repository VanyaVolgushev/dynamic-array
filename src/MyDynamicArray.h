#pragma once

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <utility>
#include <algorithm>

template<typename T>
class MyDynamicArray final {
public:
    MyDynamicArray();
    MyDynamicArray(size_t capacity);
    ~MyDynamicArray();

    MyDynamicArray(MyDynamicArray const& other);
    MyDynamicArray(MyDynamicArray&& other) noexcept;

    MyDynamicArray& operator=(MyDynamicArray other);

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
    
        reference operator*() const { return *(p + offset); }
        pointer   operator->() const { return p + offset; }
    
    private:
        T*     p;
        size_t offset;
    };
    
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
    void swap(MyDynamicArray& other) noexcept;
};

// ------------------------------------------------------------------------
// ------------IMPLEMENTATION----------------------------------------------
// ------------------------------------------------------------------------

template<typename T>
MyDynamicArray<T>::MyDynamicArray() : MyDynamicArray(DEFAULT_CAPACITY) {}

template<typename T>
MyDynamicArray<T>::MyDynamicArray(size_t capactiy) {
    _capacity = capactiy;
    _size = 0;
    _data = static_cast<T*>(malloc(sizeof(T) * _capacity));
}

template<typename T>
MyDynamicArray<T>::~MyDynamicArray() {
    if (_data) {
        for (size_t i = 0; i < _size; i++)
        {
            _data[i].~T();
        }
        free(_data);
    }
}

template<typename T>
MyDynamicArray<T>::MyDynamicArray(MyDynamicArray const& other) {
    _capacity = other._capacity;
    _size = other._size;
    if (_capacity == 0) {
        _data = nullptr;
        return;
    }
    _data = static_cast<T*>(malloc(sizeof(T) * _capacity));
    for (size_t i = 0; i < _size; ++i) {
        new (&_data[i]) T(other._data[i]);
    }
}

template<typename T>
MyDynamicArray<T>::MyDynamicArray(MyDynamicArray&& other) noexcept {
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;

    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}

template<typename T>
MyDynamicArray<T>& MyDynamicArray<T>::operator=(MyDynamicArray other) {
    swap(other);
    return *this;
}

template<typename T>
void MyDynamicArray<T>::swap(MyDynamicArray& other) noexcept {
    using std::swap;
    swap(_capacity, other._capacity);
    swap(_size, other._size);
    swap(_data, other._data);
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
    for (size_t i = _size; i > index; --i) {
        new (&_data[i]) T(std::move(_data[i - 1]));
        _data[i - 1].~T();
    }
    new (&_data[index]) T(value);
    _size++;
    return index;
}

template <typename T>
void MyDynamicArray<T>::remove(size_t index)
{
    assert(index < _size);
    _data[index].~T();
    for (size_t i = index; i < _size - 1; ++i) {
        new (&_data[i]) T(std::move(_data[i + 1]));
        _data[i + 1].~T();
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
    size_t new_capacity = (_capacity == 0) ? DEFAULT_CAPACITY : static_cast<size_t>(_capacity * RESIZE_FACTOR);
    T* new_data = (T*)malloc(sizeof(T) * new_capacity);
    for (size_t i = 0; i < _size; i++) {
        new (&new_data[i]) T(std::move(_data[i]));
        _data[i].~T();
    }
    if (_data) free(_data);
    _data = new_data;
    _capacity = new_capacity;
};
