#ifndef CIRCULAR_BUFFER_H_INCLUDED
#define CIRCULAR_BUFFER_H_INCLUDED

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
        CircularBuffer();

        // Constructs a copy of cb.
        CircularBuffer(const CircularBuffer& cb);

        // Constructs empty Circular Buffer of requested capacity, which must
        // be non-negative.
        explicit CircularBuffer(int capacity);

        // Constructs Circular Buffer of requested capacity filled with item.
        // capacity must be non-negative.
        CircularBuffer(int capacity, const ContentT& item);
        ~CircularBuffer();

        // Provides index access relative to the front element. The behaviour
        // is undefined if idx is invalid.
        ContentT& operator[](int idx);
        const ContentT& operator[](int idx) const;

        // Provides index access relative to the front element. Throws
        // out_of_range if the index is invalid.
        ContentT& at(int idx);
        const ContentT& at(int idx) const;

        // Returns reference to the front element. Throws out_of_range if the
        // Buffer is empty.
        ContentT& front();
        const ContentT& front() const;

        // Returns reference to the back element. Throws out_of_range if the
        // Buffer is empty.
        ContentT& back();
        const ContentT& back() const;

        // Shifts Circular Buffer so that its front element is moved to the
        // beginning of allocated memory. Returns pointer to the front element.
        // If the Buffer is empty, performs no action and returns nullptr.
        ContentT* Linearize();

        // Returns true if the Buffer is linearized, that is, its front element
        // is located at the beginning of allocated memory.
        bool IsLinearized() const;

        // Shifts Circular Buffer so that the element with index new_beginning
        // is moved to the beginning of allocated memory. Throws out_of_range
        // if the new beginning index is invalid.
        void Rotate(int new_beginning);

        // Returns the number of elements stored in the Buffer.
        int size() const;

        // Returns true if the Buffer size equals zero.
        bool IsEmpty() const;

        // Returns true if the Buffer size equals Buffer capacity.
        bool IsFull() const;

        // Returns the number of free Buffer slots.
        int reserve() const;

        // Returns the capacity of the Buffer.
        int capacity() const;

        // Sets the Buffer capacity and resizes the Buffer accordingly. If
        // new_capacity is less than Buffer size, the excess elements are
        // discarded. The resulting Buffer is linearized. new_capacity
        // must be non-negative.
        void SetCapacity(int new_capacity);

        // Sets the Buffer capacity and resizes the Buffer accordingly. If
        // new_capacity is less than Buffer size, the excess elements are
        // discarded. Otherwise, all free Buffer slots are filled with item.
        // The resulting Buffer is linearized. new_capacity must be
        // non-negative.
        void Resize(int new_capacity, const ContentT& item = ContentT());

        // Copies cb into the current Circular Buffer.
        CircularBuffer& operator=(const CircularBuffer& cb);

        // Swaps the current Circular Buffer with cb.
        void Swap(CircularBuffer& cb);

        // Adds item to the back of the Buffer. The front element is
        // overwritten if the Buffer is full. Throws out_of_range if the
        // Buffer is of zero capacity.
        void PushBack(const ContentT& item = ContentT());

        // Adds item to the front of the Buffer. The back element is
        // overwritten if the Buffer is full. Throws out_of_range if the
        // Buffer is of zero capacity.
        void PushFront(const ContentT& item = ContentT());

        // Deletes the back element of the Buffer and returns it. Throws
        // out_of_range if the Buffer is empty.
        ContentT& PopBack();

        // Deletes the front element of the Buffer and returns it. Throws
        // out_of_range if the Buffer is empty.
        ContentT& PopFront();

        // Inserts item into the Buffer at index pos relative to the front
        // element. All the elements starting from pos are shifted. Throws
        // out_of_range if the index is invalid or the Buffer is of zero
        // capacity.
        void Insert(int pos, const ContentT& item = ContentT());

        // Deletes Buffer elements in the range [first, last). Throws
        // out_of_range if one of the indicies is invalid. If first >= last, no
        // action is performed.
        void Erase(int first, int last);

        // Clears the Buffer.
        void Clear();
};

template <typename ContentT>
bool operator==(const CircularBuffer<ContentT>& cb1,
    const CircularBuffer<ContentT>& cb2);

template <typename ContentT>
bool operator!=(const CircularBuffer<ContentT>& cb1,
    const CircularBuffer<ContentT>& cb2);

#endif
