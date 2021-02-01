#pragma once


#include "LinkedList.hpp"
#include "Sequence.hpp"


template <class T>
class ListSequence : public Sequence <T> {

public:
    ListSequence(T* items, int size) {
        this->list = new LinkedList<T>(items, size);
    }

    ListSequence() {
        this->list = new LinkedList<T>();
    }

    ListSequence(Sequence<T>* seq) {
        this->list = new LinkedList<T>();
        for (int i = 0; i < seq->GetLength(); i++)
            this->list->InsertAt(seq->Get(i), i);
    }

    virtual ~ListSequence() {
        delete this->list;
        this->list = nullptr;
    }

    T GetFirst() override {
        return this->list->GetFirst();
    }

    T GetLast() override {
        return this->list->GetLast();
    }

    T Get(int index) override {
        return this->list->Get(index);
    }

    void InsertAt(T item, int index) override {
        this->list->InsertAt(item, index);
    }

    void Set(int index, T item) override {
        this->list->delete_i(index);
        this->list->InsertAt(item, index);
    }

    ListSequence <T>* GetSubSequence(int startindex, int endindex) override {
        ListSequence <T>* Sublist = new ListSequence<T>();
        for (int i = startindex; i < endindex; i++) {
            Sublist->InsertAt(this->list->Get(i), i - startindex);
        }
        return Sublist;
    }

    int GetLength() override {
        return this->list->GetLength();
    }

    void Append(T item) override {
        this->list->Append(item);
    }

    void delete_i(int index) override {
        this->list->delete_i(index);
    }

    void Prepend(T item) override {
        this->list->Prepend(item);
    }

    ListSequence<T>* Concat(Sequence<T>* seq) override {
        ListSequence<T>* Conclist = new ListSequence<T>();
        for (int i = 0; i < this->list->GetLength(); i++) {
            Conclist->InsertAt(this->list->Get(i), i);
        }
        for (int i = 0; i < seq->GetLength(); i++) {
            Conclist->InsertAt(seq->Get(i), i);
        }
        return Conclist;
    }

private:
    LinkedList <T>* list;

};

