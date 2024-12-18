#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int value, Node* next = nullptr, Node* prev = nullptr) : data(value), next(next), prev(prev) {}
};

class DoubleLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    int grow;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0), grow(1) {}

    void AddToHead(int value) {
        Node* newNode = new Node(value, head, nullptr);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void AddToTail(int value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void DeleteFromTail() {
        if (IsEmpty()) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* beforeLast = tail->prev;
            beforeLast->next = nullptr;
            delete tail;
            tail = beforeLast;
        }
        size--;
    }

    bool IsEmpty() const {
        return head == nullptr;
    }

    void Show() const {
        for (Node* current = head; current != nullptr; current = current->next) {
            cout << current->data << " ";
        }
        cout << "\n";
    }

    void Clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int growValue = 1) {
        grow = growValue;
        if (newSize < size) {
            while (size > newSize) {
                DeleteFromTail();
            }
        }
        else {
            for (int i = size; i < newSize; ++i) {
                AddToTail(0); // Adding default value 0 to fill the size
            }
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    void FreeExtra() {
        while (size < GetUpperBound() + 1) {
            DeleteFromTail();
        }
    }

    void RemoveAll() {
        Clear();
    }

    int GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void SetAt(int index, int value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void Add(int value) {
        if (size == GetUpperBound() + 1) {
            SetSize(size + grow);
        }
        AddToTail(value);
    }

    void Append(const DoubleLinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            Add(current->data);
            current = current->next;
        }
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        if (this == &other) return *this;
        Clear();
        Node* current = other.head;
        while (current != nullptr) {
            Add(current->data);
            current = current->next;
        }
        return *this;
    }

    ~DoubleLinkedList() {
        Clear();
    }
};

int main() {
    DoubleLinkedList list;
    list.AddToHead(10);
    list.AddToHead(20);
    list.AddToHead(30);
    list.Show();

    list.DeleteFromTail();
    list.Show();

    list.AddToTail(77);
    list.AddToTail(75);
    list.AddToTail(73);
    list.Show();

    cout << "Upper Bound: " << list.GetUpperBound() << "\n";

    cout << "Size: " << list.GetSize() << "\n";

    list.Add(88);
    list.Add(99);
    list.Show();

    list.SetSize(6, 2);
    list.Show();

    list.SetAt(2, 99);
    list.Show();

    cout << "GetAt(2): " << list.GetAt(2) << "\n";

    DoubleLinkedList otherList;
    otherList.Add(100);
    otherList.Add(200);

    list.Append(otherList);
    list.Show();

    return 0;
}
