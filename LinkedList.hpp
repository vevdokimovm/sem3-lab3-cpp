#pragma once
#include <stdexcept>

template <class T>
class LinkedList {

struct node

public:
    LinkedList(T* items, int count) {
        this->size = count;
        node* cur = head;
        for (int i = 0; i < this->size; i++) {
            cur->items = items[i];
            node* tmp = new node;
            cur->next = tmp;
            cur = cur->next;
        }
    }

    LinkedList() {
        this->head = new node;
        this->size = 0;
    }

    LinkedList(const LinkedList <T>& linkedlist) {
        this->size = linkedlist.size;
        node* cur1 = this->head;
        node* cur2 = linkedlist.head;
        for (int i = 0; i < this->size; i++) {
            cur1->items = cur2->items;
            node* tmp = new node;
            cur1->next = tmp;
            cur1 = tmp;
            cur2 = cur2->next;
        }
    }

    ~LinkedList() {
        for (int i = 0; i < this->size; i++) {
            node* cur = this->head->next;
            delete this->head;
            this->head = cur;
        }
        this->size = 0;
    }


    T GetFirst() {
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);
        return this->head->items;
    }

    T GetLast() {
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);
        node* cur = new node;
        cur = this->head;
        if (this->size == 1)
            return this->head->items;
        else {
            for (int i = 0; i < this->size - 1; i++) {
                cur = cur->next;
            }
            return cur->items;
        }
    }

    void delete_i(int index) {
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);

        if (index == 0) {
            node* tmp = new node;
            tmp = this->head;
            this->head = this->head->next;
            delete tmp;
        }

        else if (index == this->size - 1) {
            node* tmp = new node;
            tmp = this->head;
            for (int i = 0; i < this->size - 1; i++) {
                tmp = tmp->next;
            }
            delete tmp;
        }
        else {
            node* tmp = new node;
            tmp = this->head;
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
            }
            node* cur = new node;
            cur = tmp;
            tmp = tmp->next;
            cur->next = tmp->next;
            delete tmp;
        }
        this->size--;

    }

    T Get(int index) {
        if (index < 0 || index >= this->size) throw out_of_range(IndexOutOfRangeEx);
        if (index == 0)
            return head->items;
        else {
            node* cur = new node;
            cur = this->head;
            for (int i = 0; i < index; i++)
                cur = cur->next;
            return cur->items;
        }
    }

    LinkedList <T>* GetSubList(int startindex, int endindex) {
        if (startindex < 0 || endindex < startindex) throw out_of_range(IndexOutOfRangeEx);
        LinkedList <T>* newLIST = new LinkedList <T>;
        newLIST->size = endindex - startindex;
        node* cur1 = new node;
        cur1 = this->head;
        node* cur2 = new node;
        cur2 = newLIST->head;
        for (int i = 0; i < endindex; i++) {
            if (i >= startindex) {
                cur2->items = cur1->items;
                node* tmp = new node;
                cur2->next = tmp;
                cur2 = tmp;
            }
            cur1 = cur1->next;
        }
        return newLIST;
    }

    int GetLength() {
        return size;
    }

    void Prepend(T item) {
        node* new_elem = new node;
        if (this->size == 0) {
            this->head->items = item;
            this->head->next = new_elem;
        }
        else {
            new_elem->next = head;
            head = new_elem;
            new_elem->items = item;
        }
        this->size++;
    }

    void Append(T item) {
        node* new_elem = new node;
        if (this->size == 0) {
            this->head->items = item;
            this->head->next = new_elem;
            this->size++;
        }
        else {
            new_elem = this->head;
            for (int i = 0; i < this->size; i++) {
                new_elem = new_elem->next;
            }
            new_elem->items = item;
            node* new_next = new node;
            new_elem->next = new_next;
            this->size++;
        }
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > this->size) throw out_of_range(IndexOutOfRangeEx);
        node* new_elem = new node;
        if (index == 0) {
            new_elem->next = head;
            head = new_elem;
        }
        else {
            node* cur = new node;
            cur = head;
            for (int i = 0; i < index - 1; i++) {
                cur = cur->next;
            }
            new_elem->next = cur->next;
            cur->next = new_elem;
        }
        new_elem->items = item;
        this->size++;
    }

    LinkedList <T>* Concat(LinkedList<T>* list) {
        LinkedList <T>* newLIST = new LinkedList<T>;
        newLIST->size = this->size + list->size;
        node* cur1 = newLIST->head;
        node* cur2 = this->head;
        if (this->size == 0)
            return list;
        else if (list->size == 0)
            return this;
        else {
            for (int i = 0; i < this->size; i++) {
                cur1->items = cur2->items;
                node* tmp = new node;
                cur1->next = tmp;
                cur1 = tmp;
                cur2 = cur2->next;
            }
            cur2 = list->head;
            for (int i = 0; i < list->size; i++) {
                cur1->items = cur2->items;
                node* tmp = new node;
                cur1->next = tmp;
                cur1 = tmp;
                cur2 = cur2->next;
            }
            return newLIST;
        }
    }

private:
    int size;
    struct node {
        T items;
        node* next;
    };
    node* head = new node;

};
