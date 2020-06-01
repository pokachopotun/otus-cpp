#pragma once

#include <cstdlib>
#include <new>
#include <memory>

namespace NCustomAllocator {

int GetVersion();

template<typename T>
struct TNodeImpl {
    TNodeImpl(T data)
        : Data(data)
        , Next(nullptr)
    {

    }

    T Data;
    TNodeImpl<T>* Next;
};

template<typename TData>
class TCustomLinkedListIterator;

template<typename TData, typename TAllocator = std::allocator<TData>>
class TCustomLinkedList {
private:
    using TDataType = TData;
    using TNode = TNodeImpl<TData>;
    using TNodeAllocator = typename TAllocator::template rebind<TNode>::other;

    TNodeAllocator NodeAllocator;

    TNode* Head = nullptr;
    TNode* Tail = nullptr;

public:
    void Add(TData value) {
        TNode* newNode = NodeAllocator.allocate(1);
        std::allocator_traits<TNodeAllocator>::construct(NodeAllocator, newNode, value);
        if (Head == nullptr) {
            Head = newNode;
        } else {
            Tail->Next = newNode;
        }
        Tail = newNode;
    }

    friend class TCustomLinkedListIterator<TData>;
    friend class TCustomLinkedListIterator<const TData>;

    using iterator = TCustomLinkedListIterator<TData>;
    using const_iterator = TCustomLinkedListIterator<const TData>;

    iterator begin() {
        return iterator(Head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    ~TCustomLinkedList() {
        while (Head != nullptr) {
            TNode* cur = Head;
            Head = Head->Next;
            std::allocator_traits<TNodeAllocator>::destroy(NodeAllocator, cur);
            NodeAllocator.deallocate(cur, 1);
        }
    }
};

template<typename TData>
class TCustomLinkedListIterator : public std::iterator<std::input_iterator_tag, TData> {
private:
    using TNode = TNodeImpl<TData>;

    TNode* It = nullptr;

public:
    TCustomLinkedListIterator(TNode* it)
        : It(it)
    {

    }

    TCustomLinkedListIterator(const TCustomLinkedListIterator& other) = default;

    bool operator==(const TCustomLinkedListIterator& other) const {
        return It == other.It;
    }

    bool operator!=(const TCustomLinkedListIterator& other) const {
        return !operator==(other);
    }

    typename TCustomLinkedListIterator::reference operator*() const {
        return It->Data;
    }

    TCustomLinkedListIterator& operator++() {
        It = It->Next;
        return *this;
    }
};

}
