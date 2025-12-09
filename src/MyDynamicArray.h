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
    
    //class Iterator : public std::iterator<std::bidirectional_iterator_tag, int> {
    //    public:
    //        Iterator(int i = 0) : val(i) {
    //            if(val<0 || val>5) throw;
    //        }

    //        bool operator==(Iterator const& rhs) const {
    //            return (val==rhs.val);
    //        }

    //        bool operator!=(Iterator const& rhs) const {
    //            return !(*this==rhs);
    //        }

    //        Iterator& operator++() {
    //            if(val!=6)
    //                ++val;
    //            return *this;
    //        }

    //        Iterator operator++(int) {
    //            Iterator tmp (*this);
    //            ++(*this);
    //            return tmp;
    //        }

    //        Iterator& operator--() {
    //            if(val!=-1)
    //                --val;
    //            return *this;
    //        }

    //        Iterator operator--(int) {
    //            Iterator tmp (*this);
    //            --(*this);
    //            return tmp;
    //        }

    //        int operator* () const {
    //            if(val==-1 || val==6) throw;
    //            return val;
    //        }

    //    private:
    //        int val;
    //};

    //Iterator begin() {
    //    return Iterator();
    //}

    //Iterator end() {
    //    return ++Iterator(5);
    //}

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
        new (&new_data[i]) T(std::move(_data[i - 1]));
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
        new (&_data[i]) T(std::move(_data[i - 1]));
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
