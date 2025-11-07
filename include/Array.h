#pragma once

#include <memory>
#include <utility>

template <typename T>
class Array {
private:
    std::unique_ptr<std::shared_ptr<T>[]> data;
    size_t size;
    size_t capacity;

    void reallocate(size_t new_capacity);

public:
    Array();
    explicit Array(size_t initial_capacity);
    ~Array() = default;

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    Array(Array&& other) noexcept;
    Array& operator=(Array&& other) noexcept;

    void push_back(const std::shared_ptr<T>& elem);
    void remove_at(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void resize(size_t new_capacity);

    size_t getSize() const;
    size_t getCapacity() const;
};


template <typename T>
void Array<T>::reallocate(size_t new_capacity) {
    if (new_capacity == capacity) return;

    auto new_data = std::make_unique<std::shared_ptr<T>[]>(new_capacity);
    size_t copy_count = (new_capacity < size) ? new_capacity : size;
    for (size_t i = 0; i < copy_count; ++i) {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    capacity = new_capacity;
    if (size > capacity) size = capacity;
}

template <typename T>
Array<T>::Array()
    : data(nullptr), size(0), capacity(0) {}

template <typename T>
Array<T>::Array(size_t initial_capacity)
    : size(0), capacity(initial_capacity)
{
    if (capacity > 0) {
        data = std::make_unique<std::shared_ptr<T>[]>(capacity);
    }
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : data(std::move(other.data)), size(other.size), capacity(other.capacity)
{
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        size = other.size;
        capacity = other.capacity;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T>
void Array<T>::push_back(const std::shared_ptr<T>& elem) {
    if (size >= capacity) {
        size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
        reallocate(new_cap);
    }
    data[size] = elem;
    ++size;
}

template <typename T>
void Array<T>::remove_at(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    data[size - 1].reset();
    --size;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    return *data[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const {
    return *data[index];
}

template <typename T>
void Array<T>::resize(size_t new_capacity) {
    reallocate(new_capacity);
}

template <typename T>
size_t Array<T>::getSize() const {
    return size;
}

template <typename T>
size_t Array<T>::getCapacity() const {
    return capacity;
}