#pragma once

template <class T>
class Sequence {
public:
    Sequence() {}
    virtual ~Sequence() {}
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual Sequence <T>* GetSubSequence(int startindex, int endindex) = 0;
    virtual int GetLength() = 0;
    virtual void delete_i(int index) = 0;
    virtual void Set(int index, T item) = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence <T>* Concat(Sequence<T>* seq) = 0;
};
