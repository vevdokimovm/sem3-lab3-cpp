#pragma once


#include <stdexcept>

constexpr auto IndexOutOfRangeEx = "Index out of range";

template <class T>
class DynamicArray {

public:
    DynamicArray() {
        this->size = 0;
        this->items = nullptr;
    }

    DynamicArray(T* items, int size) {
        this->items = items;
        this->items = new T[size];
        this->size = size;
        for (int i = 0; i < this->size; i++) {
            this->items[i] = items[i];
        }
    }

    DynamicArray(int size) {
        this->items = new T[size];
        this->size = size;
    }

    DynamicArray(const DynamicArray <T>& dynamicArray) {
        this->size = dynamicArray.size;
        this->items = new T[this->size];
        for (int i = 0; i < dynamicArray.size; i++) {
            this->items[i] = dynamicArray.items[i];
        }
    }

    ~DynamicArray() {
        this->size = 0;
        delete[] this->items;
    }

    T Get(int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeEx);
        return this->items[index];
    }

    int GetSize() {
        return this->size;
    }

    void Set(int index, T value) {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeEx);
        this->items[index] = value;
    }

    void Resize(int newSize) {
        T* items_tmp = new T[newSize];
        if (newSize > this->size) {
            for (int i = 0; i < this->size; i++) {
                items_tmp[i] = this->items[i];
            }
            this->size = newSize;
        }
        else {
            for (int i = 0; i < newSize; i++) {
                items_tmp[i] = this->items[i];
            }
            this->size = newSize;
        }
        delete[] this->items;
        this->items = items_tmp;
    }

    void delete_i(int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeEx);
        const int NewSize = this->size - 1;
        T* tmp = new T[NewSize];
        for (int i = 0; i < NewSize; i++) {
            if (i < index) {
                tmp[i] = this->items[i];
            }
            else {
                tmp[i] = this->items[i + 1];
            }
        }
        this->size--;
        delete[] this->items;
        this->items = tmp;
    }

private:
    T* items;
    int size;

};
