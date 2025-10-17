#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 100;

// Stack implementation using array
class Stack {
private:
    int data[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    void push(int value) {
        if (!isFull()) {
            data[++top] = value;
        } else {
            cout << "Stack overflow!" << endl;
        }
    }

    int pop() {
        if (!isEmpty()) {
            return data[top--];
        }
        cout << "Stack underflow!" << endl;
        return -1;
    }

    int peek() const {
        if (!isEmpty()) {
            return data[top];
        }
        return -1;
    }

    int getSize() const {
        return top + 1;
    }

    int getElement(int index) const {
        if (index >= 0 && index <= top) {
            return data[index];
        }
        return -1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int sum() const {
        int result = 0;
        for (int i = 0; i <= top; i++) {
            result += data[i];
        }
        return result;
    }
};

// Queue implementation using array
class Queue {
private:
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    Queue() : front(0), rear(-1), count(0) {}

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == MAX_SIZE;
    }

    void enqueue(int value) {
        if (!isFull()) {
            rear = (rear + 1) % MAX_SIZE;
            data[rear] = value;
            count++;
        } else {
            cout << "Queue overflow!" << endl;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            int value = data[front];
            front = (front + 1) % MAX_SIZE;
            count--;
            return value;
        }
        cout << "Queue underflow!" << endl;
        return -1;
    }

    int peek() const {
        if (!isEmpty()) {
            return data[front];
        }
        return -1;
    }

    int getSize() const {
        return count;
    }

    int getElement(int index) const {
        if (index >= 0 && index < count) {
            return data[(front + index) % MAX_SIZE];
        }
        return -1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        for (int i = 0; i < count; i++) {
            cout << data[(front + i) % MAX_SIZE] << " ";
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
    
    cout << "=== Laboratory Work #1: Linear Lists (Array Implementation) ===" << endl;
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
