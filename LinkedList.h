#include <iostream>

class LinkedList {
public:
    // Конструктор по умолчанию, создает пустой список
    LinkedList();

    // Деструктор, освобождает память, занятую элементами списка
    ~LinkedList();

    // Добавляет элемент в конец списка
    void append(int value);

    // Добавляет элемент в начало списка
    void prepend(int value);

    // Добавляет элемент на заданную позицию
    void insert(int value, int pos);

    // Удаляет элемент по значению
    void remove(int value);

    // Удаляет элемент по номеру позиции
    void removeAt(int pos);

    // Ищет элемент по значению
    int find(int value);

    // Возвращает элемент в заданной позиции
    int get(int pos);

    // Выводит все элементы списка
    void print();

    struct Node {
        int data;
        Node* next;
    };

    Node* head;
    int size;
};

// Конструктор по умолчанию, создает пустой список
LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}

// Деструктор, освобождает память, занятую элементами списка
LinkedList::~LinkedList() {
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Добавляет элемент в конец списка
void LinkedList::append(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    size++;
}

// Добавляет элемент в начало списка
void LinkedList::prepend(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;

    head = newNode;
    size++;
}

// Добавляет элемент на заданную позицию
void LinkedList::insert(int value, int pos) {
    if (pos < 0 || pos > size) {
        throw std::out_of_range("Invalid position");
    }

    if (pos == 0) {
        prepend(value);
    } else {
        Node* newNode = new Node;
        newNode->data = value;
        Node* current = head;

        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

// Удаляет элемент по значению
void LinkedList::remove(int value) {
    if (head == nullptr) {
        return;
    }

    if (head->data == value) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        size--;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
        size--;
    }
}

// Удаляет элемент по номеру позиции
void LinkedList::removeAt(int pos) {
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Invalid position");
    }

    if (pos == 0) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        size--;
        return;
    }

    Node* current = head;

    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    Node* toDelete = current->next;
    current->next = current->next->next;
    delete toDelete;
    size--;
}

// Ищет элемент по значению
int LinkedList::find(int value) {
    Node* current = head;
    int pos = 0;

    while (current != nullptr && current->data != value) {
        current = current->next;
        pos++;
    }

    if (current == nullptr) {
        return -1;
    } else {
        return pos;
    }
}

// Возвращает элемент в заданной позиции
int LinkedList::get(int pos) {
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Invalid position");
    }

    Node* current = head;

    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    return current->data;
}

// Выводит все элементы списка
void LinkedList::print() {
    Node* current = head;

    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << std::endl;
}
