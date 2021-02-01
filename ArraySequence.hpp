#pragma once
#include "DynamicArray.hpp"
#include "Sequence.hpp"


template <class T>
class ArraySequence : public Sequence <T> {

public:
    ArraySequence() {
        this->MyArray = new DynamicArray<T>();
    }

    ArraySequence(T* items, int size) {
        this->MyArray = new DynamicArray<T>(items, size);
    }

    ArraySequence(int size) {
        this->MyArray = new DynamicArray<T>(size);
    }

    ArraySequence(Sequence <T>* seq) {
        this->MyArray = new DynamicArray<T>(seq->GetLength());
        for (int i = 0; i < this->MyArray->GetSize(); i++) {
            this->MyArray->Set(i, seq->Get(i));
        }
    }

    virtual ~ArraySequence() {
        delete this->MyArray;
        this->MyArray = nullptr;
    }

    void Set(int index, T item) override {
        this->MyArray->Set(index, item);
    }

    T GetFirst() override {
        return this->MyArray->Get(0);
    }

    T GetLast() override {
        return this->MyArray->Get(this->MyArray->GetSize() - 1);
    }

    T Get(int index) override {
        return this->MyArray->Get(index);
    }

    ArraySequence<T>* GetSubSequence(int startindex, int endindex) override {
        int SubSize = endindex - startindex;
        ArraySequence <T>* SubArray = new ArraySequence <T>(SubSize);
        for (int i = 0; i < SubSize; i++) {
            SubArray->MyArray->Set(i, this->MyArray->Get(i + startindex));
        }
        return SubArray;
    }

    void delete_i(int index) override {
        this->MyArray->delete_i(index);
    }

    int GetLength() override {
        return this->MyArray->GetSize();
    }

    void Append(T item) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        this->MyArray->Set(this->MyArray->GetSize() - 1, item);
    }

    void Prepend(T item) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        for (int i = this->MyArray->GetSize() - 1; i > 0; i--) {
            this->MyArray->Set(i, this->MyArray->Get(i - 1));
        }
        this->MyArray->Set(0, item);
    }

    void InsertAt(T item, int index) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        for (int i = this->MyArray->GetSize() - 1; i > index; i--) {
            this->MyArray->Set(i, this->MyArray->Get(i - 1));
        }
        this->MyArray->Set(index, item);
    }

    ArraySequence <T>* Concat(Sequence <T>* seq) override {
        ArraySequence <T>* newconc = new ArraySequence<T>(this->MyArray->GetSize() + seq->GetLength());
        for (int i = 0; i < this->MyArray->GetSize(); i++) {
            newconc->Set(i, this->MyArray->Get(i));
        }
        for (int i = this->MyArray->GetSize(); i < seq->GetLength() + this->MyArray->GetSize(); i++) {
            newconc->Set(i, seq->Get(i - this->MyArray->GetSize()));
        }
        return newconc;
    }

private:
    DynamicArray <T>* MyArray;

};