#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <utility>
#include "CircularBuffer.h"

template<typename ContentT>
CircularBuffer<ContentT>::CircularBuffer()
    : m_buffer(nullptr), m_capacity(0), m_size(0), m_front(0), m_back(0) {}

template<typename ContentT>
CircularBuffer<ContentT>::CircularBuffer(const CircularBuffer& cb)
        : m_capacity(cb.m_capacity), m_size(cb.m_size), m_front(cb.m_front),
          m_back(cb.m_back) {
    m_buffer = new ContentT[m_capacity];
    for (int i = 0; i < m_size; i++) {
        (*this)[i] = cb[i];
    }
}

template<typename ContentT>
CircularBuffer<ContentT>::CircularBuffer(int capacity)
        : m_capacity(capacity), m_size(0), m_front(0), m_back(0) {
    m_buffer = new ContentT[capacity];
}

template<typename ContentT>
CircularBuffer<ContentT>::CircularBuffer(int capacity, const ContentT& item)
        : m_capacity(capacity), m_size(capacity), m_front(0),
          m_back(std::max(0, capacity - 1)) { // In case capacity == 0
    m_buffer = new ContentT[capacity];
    for (int i = 0; i < capacity; i++) {
        m_buffer[i] = item;
    }
}

template<typename ContentT>
CircularBuffer<ContentT>::~CircularBuffer() {
    delete[] m_buffer;
    m_buffer = nullptr;
}

template<typename ContentT>
// idx is index relative to the front element
ContentT& CircularBuffer<ContentT>::operator[](int idx) {
    // Index in the allocated array
    int absolute_ind = (m_front + idx) % m_capacity;
    return m_buffer[absolute_ind];
}

template<typename ContentT>
const ContentT& CircularBuffer<ContentT>::operator[](int idx) const {
    int absolute_ind = (m_front + idx) % m_capacity;
    return m_buffer[absolute_ind];
}

template<typename ContentT>
ContentT& CircularBuffer<ContentT>::at(int idx) {
    if (idx < 0 || idx >= m_size) {
        throw std::out_of_range("Buffer index out of range");
    }
    int absolute_ind = (m_front + idx) % m_capacity;
    return m_buffer[absolute_ind];
}

template<typename ContentT>
const ContentT& CircularBuffer<ContentT>::at(int idx) const {
    if (idx < 0 || idx >= m_size) {
        throw std::out_of_range("Buffer index out of range");
    }
    int absolute_ind = (m_front + idx) % m_capacity;
    return m_buffer[absolute_ind];
}

template<typename ContentT>
ContentT& CircularBuffer<ContentT>::front() {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer is empty");
    }
    return m_buffer[m_front];
}

template<typename ContentT>
const ContentT& CircularBuffer<ContentT>::front() const {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer is empty");
    }
    return m_buffer[m_front];
}

template<typename ContentT>
ContentT& CircularBuffer<ContentT>::back() {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer is empty");
    }
    return m_buffer[m_back];
}

template<typename ContentT>
const ContentT& CircularBuffer<ContentT>::back() const {
    if (IsEmpty()) {
        throw std::out_of_range("Buffer is empty");
    }
    return m_buffer[m_back];
}

template<typename ContentT>
ContentT* CircularBuffer<ContentT>::Linearize() {
    if (IsEmpty()) {
        return nullptr;
    }
    auto buffer_begin = std::begin(m_buffer);
    auto buffer_end = std::end(m_buffer);
    std::rotate(buffer_begin, buffer_begin + m_front, buffer_end);

    m_front = 0;
    m_back = m_size - 1;
    return m_buffer;
}

template<typename ContentT>
bool CircularBuffer<ContentT>::IsLinearized() const {
    return m_front == 0;
}

template<typename ContentT>
// new_beginning is index relative to the front element
void CircularBuffer<ContentT>::Rotate(int new_beginning) {
    if (new_beginning < 0 || new_beginning >= m_size) {
        throw std::out_of_range("Buffer index out of range");
    }

    int absolute_ind = (m_front + new_beginning) % m_capacity;
    auto buffer_begin = std::begin(m_buffer);
    auto buffer_end = std::end(m_buffer);
    std::rotate(buffer_begin, buffer_begin + absolute_ind, buffer_end);

    m_front = (m_front + m_capacity - absolute_ind) % m_capacity;
    m_back = (m_back + m_capacity - absolute_ind) % m_capacity;
}

template<typename ContentT>
int CircularBuffer<ContentT>::size() const {
    return m_size;
}

template<typename ContentT>
bool CircularBuffer<ContentT>::IsEmpty() const {
    return m_size == 0;
}

template<typename ContentT>
bool CircularBuffer<ContentT>::IsFull() const {
    return m_size == m_capacity;
}

template<typename ContentT>
int CircularBuffer<ContentT>::reserve() const {
    return m_capacity - m_size;
}

template<typename ContentT>
int CircularBuffer<ContentT>::capacity() const {
    return m_capacity;
}

template<typename ContentT>
void CircularBuffer<ContentT>::SetCapacity(int new_capacity) {
    Linearize();
    ContentT* new_buffer = new ContentT[new_capacity];
    for (int i = 0; i < std::min(m_size, new_capacity); i++) {
        new_buffer[i] = m_buffer[i];
    }
    m_capacity = new_capacity;
    m_size = std::min(m_size, new_capacity);
    m_back = std::max(0, m_size - 1); // In case m_capacity == 0
    delete[] m_buffer;
    m_buffer = new_buffer;
}

template<typename ContentT>
void CircularBuffer<ContentT>::Resize(int new_capacity,
        const ContentT& item = ContentT()) {
    SetCapacity(new_capacity);
    for (int i = 0; i < reserve(); i++) {
        PushBack(item);
    }
}

template<typename ContentT>
CircularBuffer<ContentT>& CircularBuffer<ContentT>::operator=(
        const CircularBuffer& cb) {
    if (&cb != this) {
        m_capacity = cb.m_capacity;
        m_size = cb.m_size;
        m_front = cb.m_front;
        m_back = cb.m_back;

        ContentT* old_buffer = m_buffer; // Saved for later de-allocation
        m_buffer = new ContentT[m_capacity];
        for (int i = 0; i < m_size; i++) {
            (*this)[i] = cb[i];
        }
        delete[] old_buffer;
    }
    return *this;
}

template<typename ContentT>
void CircularBuffer<ContentT>::Swap(CircularBuffer& cb) {
    std::swap(m_buffer, cb.m_buffer);
    std::swap(m_capacity, cb.m_capacity);
    std::swap(m_size, cb.m_size);
    std::swap(m_back, cb.m_back);
    std::swap(m_front, cb.m_front);
}

template<typename ContentT>
void CircularBuffer<ContentT>::PushBack(const ContentT& item) {
    if (m_capacity == 0) {
        throw std::out_of_range("Push to Buffer of zero capacity");
    }

    // If the Buffer is empty, we need to write to the current slot,
    // otherwise, to the next one.
    m_back = IsEmpty() ? m_back : (m_back + 1) % m_capacity;
    m_buffer[m_back] = item;

    // If the Buffer is full, the front element is overwritten and the size
    // doesn't change.
    m_front = IsFull() ? (m_front + 1) % m_capacity : m_front;
    m_size = IsFull() ? m_size : m_size + 1;
}

template<typename ContentT>
void CircularBuffer<ContentT>::PushFront(const ContentT& item) {
    if (m_capacity == 0) {
        throw std::out_of_range("Push to Buffer of zero capacity");
    }

    // If the Buffer is empty, we need to write to the current slot,
    // otherwise, to the previous one.
    m_front = IsEmpty() ? m_front : (m_front - 1 + m_capacity) % m_capacity;
    m_buffer[m_front] = item;

    // If the Buffer is full, the back element is overwritten and the size
    // doesn't change.
    m_back = IsFull() ? (m_back - 1 + m_capacity) % m_capacity : m_back;
    m_size = IsFull() ? m_size : m_size + 1;
}

template<typename ContentT>
ContentT& CircularBuffer<ContentT>::PopBack() {
    ContentT back_element = back();
    m_size--;
    if (IsEmpty()) {
        m_back = m_front;
    }
    else {
        m_back = (m_back - 1 + m_capacity) % m_capacity;
    }
    return back_element;
}

template<typename ContentT>
ContentT& CircularBuffer<ContentT>::PopFront() {
    ContentT front_element = front();
    m_size--;
    if (IsEmpty()) {
        m_front = (m_front + 1) % m_capacity;
    }
    return front_element;
}

template<typename ContentT>
void CircularBuffer<ContentT>::Insert(int pos,
        const ContentT& item = ContentT()) {
    // Insertion after the last element is allowed
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid insertion index");
    }

    PushBack();
    for (int i = pos + 1; i < m_size; i++) {
        (*this)[i] = (*this)[i - 1];
    }
    (*this)[pos] = item;
}

template<typename ContentT>
void CircularBuffer<ContentT>::Erase(int first, int last) {
    if (first < 0 || first >= m_size || last < 0 || last > m_size) {
        throw std::out_of_range("Invalid index");
    }
    if (first >= last) {
        return;
    }

    for (int i = last; i < m_size; i++) {
        int shift = i - last;
        (*this)[first + shift] = (*this)[i];
    }

    int num_of_removed = last - first;
    m_size -= num_of_removed;
    if (IsEmpty()) {
        m_back = m_front;
    }
    else {
        m_back = (m_back - num_of_removed + m_capacity) % m_capacity;
    }
}

template<typename ContentT>
void CircularBuffer<ContentT>::Clear() {
    m_size = 0;
    m_back = m_front;
}

template <typename ContentT>
bool operator==(const CircularBuffer<ContentT>& cb1,
        const CircularBuffer<ContentT>& cb2) {
    if (cb1.capacity() != cb2.capacity() || cb1.size() != cb2.size()) {
        return false;
    }
    for (int i = 0; i < cb1.size(); i++) {
        if (cb1[i] != cb2[i]) {
            return false;
        }
    }
    return true;
}

template <typename ContentT>
bool operator!=(const CircularBuffer<ContentT>& cb1,
        const CircularBuffer<ContentT>& cb2) {
    return !(cb1 == cb2);
}
