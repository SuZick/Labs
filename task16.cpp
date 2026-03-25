#include <iostream>
#include <vector>
#include <random>
#include <ctime>

// ===== Решение а) с использованием массивов (vector) =====

class ArrayStack {
    std::vector<int> data;
public:
    void push(int value) {
        data.push_back(value);
    }

    bool pop(int &value) {
        if (data.empty()) return false;
        value = data.back();
        data.pop_back();
        return true;
    }

    bool isEmpty() const {
        return data.empty();
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (data.empty()) {
            std::cout << "пуст" << std::endl;
            return;
        }
        std::cout << "[";
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << " ";
        }
        std::cout << "]" << std::endl;
    }

    int sum() const {
        int s = 0;
        for (int v : data) s += v;
        return s;
    }
};

class ArrayQueue {
    std::vector<int> data;
public:
    void enqueue(int value) {
        data.push_back(value);
    }

    bool dequeue(int &value) {
        if (data.empty()) return false;
        value = data.front();
        data.erase(data.begin());
        return true;
    }

    bool isEmpty() const {
        return data.empty();
    }

    void print(const std::string &name) const {
        std::cout << name << ": ";
        if (data.empty()) {
            std::cout << "пуста" << std::endl;
            return;
        }
        std::cout << "[";
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << " ";
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

// ===== Вспомогательный генератор случайных чисел =====

static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

int randInt(int lo, int hi) {
    return std::uniform_int_distribution<int>(lo, hi)(rng);
}

// ===== Задача 16: решение на массивах =====

void solveWithArrays() {
    std::cout << "Решение с использованием массивов" << std::endl;

    ArrayStack stack;
    int stackSize = randInt(3, 8);
    std::cout << "Формирование исходного стека (" << stackSize << " элементов):" << std::endl;
    for (int i = 0; i < stackSize; i++) {
        int value = randInt(1, 20);
        stack.push(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    ArrayQueue queue;
    int queueSize = randInt(3, 8);
    std::cout << "\nФормирование исходной очереди (" << queueSize << " элементов):" << std::endl;
    for (int i = 0; i < queueSize; i++) {
        int value = randInt(1, 20);
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
    int stackSize = randInt(3, 8);
    std::cout << "Формирование исходного стека (" << stackSize << " элементов):" << std::endl;
    for (int i = 0; i < stackSize; i++) {
        int value = randInt(1, 20);
        stack.push(value);
        std::cout << "  Добавлен элемент: " << value << std::endl;
    }

    LinkedQueue queue;
    int queueSize = randInt(3, 8);
    std::cout << "\nФормирование исходной очереди (" << queueSize << " элементов):" << std::endl;
    for (int i = 0; i < queueSize; i++) {
        int value = randInt(1, 20);
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
    std::cout << "Лабораторная работа: Стеки и очереди" << std::endl;

    solveWithArrays();

    solveWithLinkedLists();

    return 0;
}
