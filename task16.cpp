#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

const int MAX_SIZE = 10;

// ===== Решение а) с использованием массивов =====

class ArrayStack {
    int data[MAX_SIZE];
    int top;
public:
    ArrayStack() : top(-1) {
        memset(data, 0, sizeof(data));
    }

    void push(int value) {
        data[++top] = value;
    }

    bool pop(int &value) {
        if (top < 0) return false;
        value = data[top--];
        return true;
    }

    bool isEmpty() const {
        return top < 0;
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (top < 0) {
            std::cout << "пуст" << std::endl;
            return;
        }
        std::cout << "[";
        for (int i = 0; i <= top; i++) {
            std::cout << data[i];
            if (i < top) std::cout << " ";
        }
        std::cout << "]" << std::endl;
    }

    int sum() const {
        int s = 0;
        for (int i = 0; i <= top; i++) s += data[i];
        return s;
    }
};

class ArrayQueue {
    int data[MAX_SIZE];
    int size;
public:
    ArrayQueue() : size(0) {
        memset(data, 0, sizeof(data));
    }

    void enqueue(int value) {
        data[size++] = value;
    }

    bool dequeue(int &value) {
        if (size == 0) return false;
        value = data[0];
        for (int i = 0; i < size - 1; i++) data[i] = data[i + 1];
        size--;
        return true;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (size == 0) {
            std::cout << "пуста" << std::endl;
            return;
        }
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << " ";
        }
        std::cout << "]" << std::endl;
    }
};

// ===== Решение б) с использованием динамических списков =====

struct Node {
    int value;
    Node *next;
    Node(int v, Node *n = nullptr) : value(v), next(n) {}
};

class LinkedStack {
    Node *top;
public:
    LinkedStack() : top(nullptr) {}
    LinkedStack(const LinkedStack &) = delete;
    LinkedStack &operator=(const LinkedStack &) = delete;

    ~LinkedStack() {
        while (top) {
            Node *tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    void push(int value) {
        top = new Node(value, top);
    }

    bool pop(int &value) {
        if (!top) return false;
        value = top->value;
        Node *tmp = top;
        top = top->next;
        delete tmp;
        return true;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (!top) {
            std::cout << "пуст" << std::endl;
            return;
        }
        std::cout << "[";
        Node *curr = top;
        while (curr) {
            std::cout << curr->value;
            if (curr->next) std::cout << " ";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
    }

    int sum() const {
        int s = 0;
        Node *curr = top;
        while (curr) {
            s += curr->value;
            curr = curr->next;
        }
        return s;
    }
};

class LinkedQueue {
    Node *front;
    Node *rear;
public:
    LinkedQueue() : front(nullptr), rear(nullptr) {}
    LinkedQueue(const LinkedQueue &) = delete;
    LinkedQueue &operator=(const LinkedQueue &) = delete;

    ~LinkedQueue() {
        while (front) {
            Node *tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    void enqueue(int value) {
        Node *newNode = new Node(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue(int &value) {
        if (!front) return false;
        value = front->value;
        Node *tmp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete tmp;
        return true;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (!front) {
            std::cout << "пуста" << std::endl;
            return;
        }
        std::cout << "[";
        Node *curr = front;
        while (curr) {
            std::cout << curr->value;
            if (curr->next) std::cout << " ";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
    }
};

// ===== Задача 16: решение на массивах =====

void solveWithArrays() {
    std::cout << "Решение с использованием массивов" << std::endl;

    ArrayStack stack;
    int stackSize = rand() % 6 + 3;
    std::cout << "Формирование исходного стека (" << stackSize << " элементов):" << std::endl;
    for (int i = 0; i < stackSize; i++) {
        int value = rand() % 20 + 1;
        stack.push(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    ArrayQueue queue;
    int queueSize = rand() % 6 + 3;
    std::cout << "\nФормирование исходной очереди (" << queueSize << " элементов):" << std::endl;
    for (int i = 0; i < queueSize; i++) {
        int value = rand() % 20 + 1;
        queue.enqueue(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    std::cout << "\n--- Исходные данные ---" << std::endl;
    stack.print("Стек");
    queue.print("Очередь");

    int stackSum = stack.sum();
    std::cout << "\nСумма элементов стека: " << stackSum << std::endl;

    std::cout << "\nОбработка очереди:" << std::endl;
    ArrayStack resultStack;
    ArrayQueue tempQueue;

    int value;
    while (!queue.isEmpty()) {
        queue.dequeue(value);
        tempQueue.enqueue(value);

        if (stackSum % value != 0) {
            resultStack.push(value);
            std::cout << "  " << value << ": сумма " << stackSum
                      << " НЕ делится на " << value << " -> добавлен в новый стек" << std::endl;
        } else {
            std::cout << "  " << value << ": сумма " << stackSum
                      << " делится на " << value << " -> пропущен" << std::endl;
        }
    }

    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(value);
        queue.enqueue(value);
    }

    std::cout << "\n--- Результат ---" << std::endl;
    stack.print("Исходный стек");
    queue.print("Исходная очередь");
    resultStack.print("Новый стек");
}

// ===== Задача 16: решение на динамических списках =====

void solveWithLinkedLists() {
    std::cout << "\n\nРешение с использованием динамических списков" << std::endl;

    LinkedStack stack;
    int stackSize = rand() % 6 + 3;
    std::cout << "Формирование исходного стека (" << stackSize << " элементов):" << std::endl;
    for (int i = 0; i < stackSize; i++) {
        int value = rand() % 20 + 1;
        stack.push(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    LinkedQueue queue;
    int queueSize = rand() % 6 + 3;
    std::cout << "\nФормирование исходной очереди (" << queueSize << " элементов):" << std::endl;
    for (int i = 0; i < queueSize; i++) {
        int value = rand() % 20 + 1;
        queue.enqueue(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    std::cout << "\n--- Исходные данные ---" << std::endl;
    stack.print("Стек");
    queue.print("Очередь");

    int stackSum = stack.sum();
    std::cout << "\nСумма элементов стека: " << stackSum << std::endl;

    std::cout << "\nОбработка очереди:" << std::endl;
    LinkedStack resultStack;
    LinkedQueue tempQueue;

    int value;
    while (!queue.isEmpty()) {
        queue.dequeue(value);
        tempQueue.enqueue(value);

        if (stackSum % value != 0) {
            resultStack.push(value);
            std::cout << "  " << value << ": сумма " << stackSum
                      << " НЕ делится на " << value << " -> добавлен в новый стек" << std::endl;
        } else {
            std::cout << "  " << value << ": сумма " << stackSum
                      << " делится на " << value << " -> пропущен" << std::endl;
        }
    }

    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(value);
        queue.enqueue(value);
    }

    std::cout << "\n--- Результат ---" << std::endl;
    stack.print("Исходный стек");
    queue.print("Исходная очередь");
    resultStack.print("Новый стек");
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    std::cout << "Лабораторная работа: Стеки и очереди" << std::endl;

    solveWithArrays();

    solveWithLinkedLists();

    return 0;
}
