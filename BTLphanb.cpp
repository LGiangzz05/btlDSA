#include <bits/stdc++.h>

using namespace std;

struct Node {
    float data;
    Node* next;
    Node* prev;
    Node(float value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoubleList {
private:
    Node* head;
    Node* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}

// Them phan tu vào dau danh sach
    void push_front(float value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
    }

// Them phan tu vao cuoi danh sach
    void push_back(float value) {
        Node* newNode = new Node(value);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = tail;
    }

// Xoa phan tu dau danh sach
    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

// Xoa phan tu cuoi danh sach
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

// Xoa phan tu trung nhau, giu lai phan tu dau tien
    void remove_duplicates() {
        unordered_set<float> seen;
        Node* current = head;
        while (current) {
            if (seen.count(current->data)) {
                Node* Delete = current;
                if (Delete->prev) Delete->prev->next = Delete->next;
                if (Delete->next) Delete->next->prev = Delete->prev;
                if (Delete == head) head = Delete->next;
                if (Delete == tail) tail = Delete->prev;
                current = current->next;
                delete Delete;
            } else {
                seen.insert(current->data);
                current = current->next;
            }
        }
    }

// Sap xep danh sach tang dan
    void sort() {
        if (!head) return;
        for (Node* i = head; i->next; i = i->next) {
            for (Node* j = i->next; j; j = j->next) {
                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
            }
        }
    }

// Chen phan tu vào danh sach da sap xep
    void insert_sorted(float value) {
        Node* newNode = new Node(value);
        if (!head || head->data >= value) {
            push_front(value);
            return;
        }

        Node* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        if (current->next) current->next->prev = newNode;
        newNode->prev = current;
        current->next = newNode;

        if (!newNode->next) tail = newNode;
    }

// Ap dung ham fun vao tung phan tu trong danh sach
    void transform(function<float(float)> fun) {
        Node* current = head;
        while (current) {
            current->data = fun(current->data);
            current = current->next;
        }
    }

// Xuat danh sach theo chieu nguoc lai
    void print_reverse() const {
        Node* current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

// Xuat danh sach theo chieu xuoi
    void print_forward() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoubleList list;
    int n;
	float x;

// Nhap danh sach so nguyen
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        list.push_back(x);
    }

// Xoa phan tu trung nhau
    cout<< "Day sau khi xoa cac phan tu trung nhau:";
    list.remove_duplicates();
    list.print_forward();

// Bien doi tung phan tu: f(x) = (x^2 - 7x + 3) / 100
    cout<< "Day sau khi bien doi tung phan tu theo f(x):";
    list.transform([](float x) { return ((x*x - 7*x + 3)/100); });
    list.print_forward();

// Xoa phan tu trung nhau sau khi bien doi
    list.remove_duplicates();

// Sap xep danh sach tang dan
    cout << "Day sau khi bien doi va sap xep tang dan:";
    list.sort();
    list.print_forward();

// Nhap x và chèn vào danh sách do dãy van tang dan
    cout << "Nhap phan tu can chen: ";
    cin >> x;
    list.insert_sorted(x);

// Xuat danh sách theo chieu nguoc lai
    cout << "Danh sach cuoi cung theo thu tu giam dan: ";
    list.print_reverse();

    return 0;
}

