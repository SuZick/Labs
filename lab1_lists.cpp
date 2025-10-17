#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// Stack implementation using linked list
class Stack {
private:
    Node* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        Node* temp = top;
        int value = temp->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }

    int peek() const {
        if (!isEmpty()) {
            return top->data;
        }
        return -1;
    }

    int getSize() const {
        return size;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    int sum() const {
        int result = 0;
        Node* current = top;
        while (current != nullptr) {
            result += current->data;
            current = current->next;
        }
        return result;
    }

    // Helper function to get element at index (for processing)
    int getElement(int index) const {
        Node* current = top;
        int currentIndex = 0;
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        if (current != nullptr) {
            return current->data;
        }
        return -1;
    }
};

// Queue implementation using linked list
class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow!" << endl;
            return -1;
        }
        Node* temp = front;
        int value = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    int peek() const {
        if (!isEmpty()) {
            return front->data;
        }
        return -1;
    }

    int getSize() const {
        return size;
    }

    int getElement(int index) const {
        Node* current = front;
        int currentIndex = 0;
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        if (current != nullptr) {
            return current->data;
        }
        return -1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Function to fill stack with random elements
void fillStack(Stack& stack, int size) {
    for (int i = 0; i < size; i++) {
        stack.push(rand() % 50 + 1); // Random numbers from 1 to 50
    }
}

// Function to fill queue with random elements
void fillQueue(Queue& queue, int size) {
    for (int i = 0; i < size; i++) {
        queue.enqueue(rand() % 50 + 1); // Random numbers from 1 to 50
    }
}

// Main algorithm: create new stack from queue elements that sum of stack doesn't divide by
Stack processData(Stack& originalStack, Queue& originalQueue) {
    Stack resultStack;
    
    // Calculate sum of all elements in stack
    int stackSum = originalStack.sum();
    
    cout << "\nSum of stack elements: " << stackSum << endl;
    
    if (stackSum == 0) {
        cout << "Stack sum is 0, cannot perform division check" << endl;
        return resultStack;
    }
    
    // Process queue elements
    int queueSize = originalQueue.getSize();
    cout << "\nChecking queue elements:" << endl;
    
    for (int i = 0; i < queueSize; i++) {
        int element = originalQueue.getElement(i);
        if (stackSum % element != 0) {
            cout << "Element " << element << " - sum " << stackSum 
                 << " % " << element << " = " << (stackSum % element) 
                 << " (not divisible, adding to result)" << endl;
            resultStack.push(element);
        } else {
            cout << "Element " << element << " - sum " << stackSum 
                 << " % " << element << " = 0 (divisible, skipping)" << endl;
        }
    }
    
    return resultStack;
}

int main() {
    srand(time(0));
    
    cout << "=== Laboratory Work #1: Linear Lists (Linked List Implementation) ===" << endl;
    cout << "Task: From queue elements that the sum of stack elements does NOT divide by," << endl;
    cout << "      form a new stack." << endl << endl;
    
    // Create initial stack and queue
    Stack originalStack;
    Queue originalQueue;
    
    // Random sizes for stack and queue
    int stackSize = rand() % 8 + 3;  // 3 to 10 elements
    int queueSize = rand() % 10 + 5; // 5 to 14 elements
    
    cout << "Generating random stack with " << stackSize << " elements..." << endl;
    fillStack(originalStack, stackSize);
    
    cout << "Generating random queue with " << queueSize << " elements..." << endl;
    fillQueue(originalQueue, queueSize);
    
    // Display initial data
    cout << "\n--- Initial Data ---" << endl;
    originalStack.display();
    originalQueue.display();
    
    // Process data
    cout << "\n--- Processing ---" << endl;
    Stack resultStack = processData(originalStack, originalQueue);
    
    // Display result
    cout << "\n--- Result ---" << endl;
    resultStack.display();
    
    cout << "\nOriginal data structures remain unchanged:" << endl;
    originalStack.display();
    originalQueue.display();
    
    return 0;
}
