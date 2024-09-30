#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void AddToHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void AddToTail(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void DeleteFromHead() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    void DeleteFromTail() {
        if (tail == nullptr) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }

    void DeleteAll() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void Show() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void InsertAt(int position, T value) {
        if (position < 0 || position > size) return;
        if (position == 0) AddToHead(value);
        else if (position == size) AddToTail(value);
        else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* temp = head;
            for (int i = 0; i < position - 1; i++) temp = temp->next;
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }
    }

    void DeleteAt(int position) {
        if (position < 0 || position >= size) return;
        if (position == 0) DeleteFromHead();
        else if (position == size - 1) DeleteFromTail();
        else {
            Node<T>* temp = head;
            for (int i = 0; i < position; i++) temp = temp->next;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
    }

    int Find(T value) {
        Node<T>* temp = head;
        int position = 0;
        while (temp != nullptr) {
            if (temp->data == value) return position;
            temp = temp->next;
            position++;
        }
        return -1;
    }

    int Replace(T oldValue, T newValue) {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == oldValue) {
                temp->data = newValue;
                count++;
            }
            temp = temp->next;
        }
        return count;
    }

    void Reverse() {
        Node<T>* temp = nullptr;
        Node<T>* current = head;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) head = temp->prev;
    }
};