#pragma once


#include "ArraySequence.hpp"

template <typename T>
Sequence <T>* bubble_sort(Sequence <T>* seq, int (*cmp)(T, T)) {
    for (int i = 0; i < seq->GetLength(); i++) {
        for (int j = 0; j < seq->GetLength() - 1; j++) {
            if (cmp(seq->Get(j), seq->Get(j + 1))) { // j > j + 1?
                T tmp = seq->Get(j);
                seq->Set(j, seq->Get(j + 1));
                seq->Set(j + 1, tmp);
            }
        }
    }
    return seq;
}


template <typename T>
void merge(Sequence<T>* seq, int (*cmp)(T, T), int left, int mid, int right) {
    int i, j, k;
    int left_leng = mid - left + 1;       // ����� ���� ��������� ���������
    int right_leng = right - mid;


    ArraySequence<T> first_tmp(left_leng), second_tmp(right_leng);               // �������� ��������� ��������
    Sequence<T>* left_seq = &first_tmp;
    Sequence<T>* right_seq = &second_tmp;

    for (i = 0; i < left_leng; i++) {                   // ��������� � ��� ��������
        left_seq->Set(i, seq->Get(i + left));
    }
    for (j = 0; j < right_leng; j++) {
        right_seq->Set(j, seq->Get(mid + 1 + j));
    }

    i = 0; j = 0; k = left;          // �������� �������

    while (i < left_leng && j < right_leng) {             // ���� �� �� ��������� ��������� ���� �� ������� - ��������
        if (cmp(right_seq->Get(j), left_seq->Get(i))) {           // ������� �����
            seq->Set(k, left_seq->Get(i));
            i++;
        }
        else {
            seq->Set(k, right_seq->Get(j));            // ������� � ������������(���� ����) ������
            j++;
        }
        k++;
    }                                      // ������������ ���� �������� 

    while (i < left_leng) {              // ������� ��� �� ������ ��� �� ������� ����������
        seq->Set(k, left_seq->Get(i));
        i++;
        k++;
    }

    while (j < right_leng) {
        seq->Set(k, right_seq->Get(j));
        j++;
        k++;
    }
}


template <typename T>
void merge_sort(Sequence<T>* seq, int (*cmp)(T, T), int left, int right) {
    if (left < right) { // (l + r) / 2 == l + (r - l)/ 2 ���� ��� �������
        int mid = left + (right - left) / 2;  // ����� �������

        merge_sort(seq, cmp, left, mid);
        merge_sort(seq, cmp, mid + 1, right);    //���������� 

        merge(seq, cmp, left, mid, right);         // ���������� �������
    }
}

template <typename T>
Sequence <T>* merge_sort_for_seq(Sequence <T>* seq, int (*cmp)(T, T)) {
    if (seq->GetLength())
        merge_sort(seq, cmp, 0, seq->GetLength() - 1);
    return seq;
}


template <typename T>
class BST_for_sort {
private:
    struct node {
        T data;
        node* left;
        node* right;
    };
    node* root;
    int count_for_KLP;
    void destroy_tree(node* branch) {
        if (branch != nullptr) {
            destroy_tree(branch->left);
            destroy_tree(branch->right);
            delete branch;
        }
    }

    int cmp_for_BST(T a, T b) {
        if (a > b)
            return 1;
        return 0;
    }

    void insert_help(node* branch, T item) {    
        node* cur = branch;
        if (cmp_for_BST(cur->data, item)) {
            if (cur->left != nullptr) {
                insert_help(cur->left, item);
            }
            else {
                cur->left = new node;
                cur->left->data = item;
                cur->left->left = nullptr;
                cur->left->right = nullptr;
            }
        }
        else {
            if (cur->right != nullptr) {
                insert_help(cur->right, item);
            }
            else {
                cur->right = new node;
                cur->right->data = item;
                cur->right->left = nullptr;
                cur->right->right = nullptr;
            }
        }
    }


    Sequence<T>* LKP_help(node* branch, Sequence<T>* seq) {
        node* tmp = branch; // KLP
        if (tmp) {
            LKP_help(branch->left, seq);
            seq->Set(this->count_for_KLP, branch->data);
            this->count_for_KLP++;
            LKP_help(branch->right, seq);;
        }
        return seq;
    }

public:
    BST_for_sort() {
        this->root = nullptr;
        count_for_KLP = 0;
    };

    ~BST_for_sort() {
        destroy_tree(this->root);
        count_for_KLP = 0;
    };

    Sequence <T>* LKP(Sequence<T>* seq) {
        return LKP_help(this->root, seq);
    }

    void insert(T item) {
        if (this->root != nullptr)
            insert_help(this->root, item);
        else {
            this->root = new node;
            this->root->data = item;
            this->root->right = nullptr;
            this->root->left = nullptr;
        }
    }
};


template <typename T>
Sequence<T>* sort_with_tree(Sequence<T>* seq, int (*cmp)(T, T)) {
    BST_for_sort<T> assist_tree;
    for (int i = 0; i < seq->GetLength(); i++) {
        assist_tree.insert(seq->Get(i));
    }
    return assist_tree.LKP(seq);
}
