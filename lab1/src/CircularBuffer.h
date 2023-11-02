#ifndef CIRCULAR_BUFFER_H_INCLUDED
#define CIRCULAR_BUFFER_H_INCLUDED

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <utility>

template <typename ContentT>
class CircularBuffer {
    private:
        ContentT* m_buffer;
        int m_capacity;
        int m_size; // Number of elements stored
        int m_front; // Index of the earliest added element
        int m_back; // Index of the latest added element

    public:

    // Constructs Circular Buffer of zero size and zero capacity.
    CircularBuffer()
        : m_buffer(nullptr), m_capacity(0), m_size(0), m_front(0),
          m_back(0) {};

    // Constructs a copy of cb.
    CircularBuffer(const CircularBuffer& cb)
            : m_capacity(cb.m_capacity), m_size(cb.m_size),
              m_front(cb.m_front), m_back(cb.m_back) {
        m_buffer = new ContentT[m_capacity];
        for (int i = 0; i < m_size; i++) {
            (*this)[i] = cb[i];
        }
    }

    // Constructs empty Circular Buffer of requested capacity, which must be
    // non-negative.
    explicit CircularBuffer(int capacity)
            : m_capacity(capacity), m_size(0), m_front(0), m_back(0) {
        m_buffer = new ContentT[capacity];
    }

    // Constructs Circular Buffer of requested capacity filled with item.
    // capacity must be non-negative.
    CircularBuffer(int capacity, const ContentT& item)
            : m_capacity(capacity), m_size(capacity), m_front(0),
              m_back(std::max(0, capacity - 1)) { // In case capacity == 0
        m_buffer = new ContentT[capacity];
        for (int i = 0; i < capacity; i++) {
            m_buffer[i] = item;
        }
    }

    ~CircularBuffer() {
        delete[] m_buffer;
        m_buffer = nullptr;
    }

    // Provides read/mutate index access relative to the front element. The
    // behaviour is undefined if idx is invalid.
    ContentT& operator[](int idx) {
        // Index in the allocated array
        int absolute_ind = (m_front + idx) % m_capacity;
        return m_buffer[absolute_ind];
    }

    // Provides read-only index access relative to the front element. The
    // behaviour is undefined if idx is invalid.
    const ContentT& operator[](int idx) const {
        int absolute_ind = (m_front + idx) % m_capacity;
        return m_buffer[absolute_ind];
    }

    // Provides read/mutate index access relative to the front element. Throws
    // out_of_range if the index is invalid.
    ContentT& at(int idx) {
        if (idx < 0 || idx >= m_size) {
            throw std::out_of_range("Buffer index out of range");
        }
        int absolute_ind = (m_front + idx) % m_capacity;
        return m_buffer[absolute_ind];
    }

    // Provides read-inly index access relative to the front element. Throws
    // out_of_range if the index is invalid.
    const ContentT& at(int idx) const {
        if (idx < 0 || idx >= m_size) {
            throw std::out_of_range("Buffer index out of range");
        }
        int absolute_ind = (m_front + idx) % m_capacity;
        return m_buffer[absolute_ind];
    }

    // Returns reference to the front element. Throws out_of_range if the
    // Buffer is empty.
    ContentT& front() {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return m_buffer[m_front];
    }

    // Returns const reference to the front element. Throws out_of_range if the
    // Buffer is empty.
    const ContentT& front() const {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return m_buffer[m_front];
    }

    // Returns reference to the back element. Throws out_of_range if the Buffer
    // is empty.
    ContentT& back() {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return m_buffer[m_back];
    }

    // Returns const reference to the back element. Throws out_of_range if the Buffer
    // is empty.
    const ContentT& back() const {
        if (IsEmpty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return m_buffer[m_back];
    }

    // Shifts Circular Buffer so that its front element is moved to the
    // beginning of allocated memory. Returns pointer to the front element. If
    // the Buffer is empty, performs no action and returns nullptr.
    ContentT* Linearize() {
        if (IsEmpty()) {
            return nullptr;
        }
        ContentT* buffer_begin = m_buffer;
        ContentT* buffer_end = m_buffer + m_capacity;
        std::rotate(buffer_begin, buffer_begin + m_front, buffer_end);

        m_front = 0;
        m_back = m_size - 1;
        return m_buffer;
    }

    // Returns true if the Buffer is linearized, that is, its front element is
    // located at the beginning of allocated memory.
    bool IsLinearized() const {
        return m_front == 0;
    }

    // Shifts Circular Buffer so that the element with index new_beginning is
    // moved to the beginning of allocated memory. Throws out_of_range if the
    // new beginning index is invalid.
    void Rotate(int new_beginning) {
        if (new_beginning < 0 || new_beginning >= m_size) {
            throw std::out_of_range("Buffer index out of range");
        }

        int absolute_ind = (m_front + new_beginning) % m_capacity;
        ContentT* buffer_begin = m_buffer;
        ContentT* buffer_end = m_buffer + m_capacity;
        std::rotate(buffer_begin, buffer_begin + absolute_ind, buffer_end);

        m_front = (m_front + m_capacity - absolute_ind) % m_capacity;
        m_back = (m_back + m_capacity - absolute_ind) % m_capacity;
    }

    // Returns the number of elements stored in the Buffer.
    int size() const {
        return m_size;
    }

    // Returns true if the Buffer size equals zero.
    bool IsEmpty() const {
        return m_size == 0;
    }

    // Returns true if the Buffer size equals Buffer capacity.
    bool IsFull() const {
        return m_size == m_capacity;
    }

    // Returns the number of free Buffer slots.
    int reserve() const {
        return m_capacity - m_size;
    }

    // Returns the capacity of the Buffer.
    int capacity() const {
        return m_capacity;
    }

    // Sets the Buffer capacity and resizes the Buffer accordingly. If
    // new_capacity is less than Buffer size, the excess elements are
    // discarded. The resulting Buffer is linearized. new_capacity must be
    // non-negative.
    void SetCapacity(int new_capacity) {
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

    // Sets the Buffer capacity and resizes the Buffer accordingly. If
    // new_capacity is less than Buffer size, the excess elements are
    // discarded. Otherwise, all free Buffer slots are filled with item. The
    // resulting Buffer is linearized. new_capacity must be non-negative.
    void Resize(int new_capacity, const ContentT& item = ContentT()) {
        SetCapacity(new_capacity);
        int res = reserve();
        for (int i = 0; i < res; i++) {
            PushBack(item);
        }
    }

    // Copies cb into the current Circular Buffer.
    CircularBuffer& operator=(const CircularBuffer& cb) {
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

    // Swaps the current Circular Buffer with cb.
    void Swap(CircularBuffer& cb) {
        std::swap(m_buffer, cb.m_buffer);
        std::swap(m_capacity, cb.m_capacity);
        std::swap(m_size, cb.m_size);
        std::swap(m_back, cb.m_back);
        std::swap(m_front, cb.m_front);
    }

    // Adds item to the back of the Buffer. The front element is overwritten if
    // the Buffer is full. Throws out_of_range if the Buffer is of zero
    // capacity.
    void PushBack(const ContentT& item = ContentT()) {
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

    // Adds item to the front of the Buffer. The back element is overwritten if
    // the Buffer is full. Throws out_of_range if the Buffer is of zero
    // capacity.
    void PushFront(const ContentT& item = ContentT()) {
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

    // Deletes the back element of the Buffer and returns it. Throws
    // out_of_range if the Buffer is empty.
    ContentT& PopBack() {
        // This would throw std::out_of_range if the Buffer is empty
        ContentT& back_element = back();
        m_size--;
        if (IsEmpty()) {
            m_back = m_front;
        }
        else {
            m_back = (m_back - 1 + m_capacity) % m_capacity;
        }
        return back_element;
    }

    // Deletes the front element of the Buffer and returns it. Throws
    // out_of_range if the Buffer is empty.
    ContentT& PopFront() {
        // This would throw std::out_of_range if the Buffer is empty
        ContentT& front_element = front();
        m_size--;
        if (IsEmpty()) {
            m_front = m_back;
        }
        else {
            m_front = (m_front + 1) % m_capacity;
        }
        return front_element;
    }

    // Inserts item into the Buffer at index pos relative to the front element.
    // All the elements starting from pos are shifted. The front element will
    // be overwritten if the Buffer is full. Throws out_of_range if the index
    // is invalid or the Buffer is of zero capacity.
    void Insert(int pos, const ContentT& item = ContentT()) {
        // Insertion after the last element is allowed
        if (pos < 0 || pos > m_size) {
            throw std::out_of_range("Invalid insertion index");
        }

        int old_front = m_front;
        PushBack(); // m_front might change here
        for (int i = m_size - 1; i > pos; i--) {
            (*this)[i] = (*this)[i - 1];
        }

        // Index in the allocated array; pos is index relative to the original
        // front
        int absolute_index = (old_front + pos) % m_capacity;
        m_buffer[absolute_index] = item;
    }

    // Deletes Buffer elements in the range [first, last). Throws out_of_range
    // if one of the indicies is invalid. If first >= last, no action is
    // performed.
    void Erase(int first, int last) {
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

    // Clears the Buffer.
    void Clear() {
        m_size = 0;
        m_back = m_front;
    }

    // Returns pointer to the beginning of allocated memory.
    ContentT* buffer() {
        return m_buffer;
    }
};

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

#endif
