#include <iostream>
#include <string>
#include "LinkedList.h" // Подключаем реализацию связного списка

// Класс для реализации стека
class Stack {
public:
    Stack(); // Конструктор класса Stack

    ~Stack(); // Деструктор класса Stack

    bool isEmpty(); // Проверяет, пуст ли стек

    void push(char value); // Добавляет элемент в стек

    char pop(); // Удаляет и возвращает верхний элемент стека

    char peek(); // Возвращает верхний элемент стека без удаления

private:
    LinkedList list; // Связный список для хранения элементов стека
};

Stack::Stack() {} // Реализация конструктора Stack

Stack::~Stack() {} // Реализация деструктора Stack

bool Stack::isEmpty() {
    return list.size == 0; // Проверяет, пуст ли стек (размер списка равен 0)
}

void Stack::push(char value) {
    list.prepend(value); // Добавляет элемент в начало списка (верх стека)
}

char Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty"); // Если стек пуст, выбрасывается исключение
    }

    char value = list.get(0); // Получаем верхний элемент стека
    list.removeAt(0); // Удаляем верхний элемент из списка
    return value; // Возвращаем удаленный элемент
}

char Stack::peek() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty"); // Если стек пуст, выбрасывается исключение
    }

    return list.get(0); // Возвращает верхний элемент стека без удаления
}

// Класс для реализации очереди
class Queue {
public:
    Queue(); // Конструктор класса Queue

    ~Queue(); // Деструктор класса Queue

    bool isEmpty(); // Проверяет, пуста ли очередь

    void enqueue(char value); // Добавляет элемент в очередь

    char dequeue(); // Удаляет и возвращает первый элемент очереди

    char peek(); // Возвращает первый элемент очереди без удаления

private:
    LinkedList list; // Связный список для хранения элементов очереди
};

Queue::Queue() {} // Реализация конструктора Queue

Queue::~Queue() {} // Реализация деструктора Queue

bool Queue::isEmpty() {
    return list.size == 0; // Проверяет, пуста ли очередь (размер списка равен 0)
}

void Queue::enqueue(char value) {
    list.append(value); // Добавляет элемент в конец списка (конец очереди)
}

char Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty"); // Если очередь пуста, выбрасывается исключение
    }

    char value = list.get(0); // Получаем первый элемент очереди
    list.removeAt(0); // Удаляем первый элемент из списка
    return value; // Возвращаем удаленный элемент
}

char Queue::peek() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty"); // Если очередь пуста, выбрасывается исключение
    }

    return list.get(0); // Возвращает первый элемент очереди без удаления
}

// Класс для реализации инфиксного калькулятора
class InfixCalculator {
public:
    InfixCalculator(); // Конструктор класса InfixCalculator

    int calculate(const std::string& expression); // Вычисляет результат инфиксного выражения

private:
    std::string convertToPostfix(const std::string& expression); // Преобразует инфиксное выражение в постфиксное
    bool isOperator(char c); // Проверяет, является ли символ оператором
    bool isOperand(char c); // Проверяет, является ли символ операндом (числом)
    int getPrecedence(char c); // Возвращает приоритет оператора
    bool hasHigherPrecedence(char op1, char op2); // Проверяет, имеет ли оператор op1 более высокий приоритет, чем оператор op2
};

InfixCalculator::InfixCalculator() {} // Реализация конструктора InfixCalculator

int InfixCalculator::calculate(const std::string& expression) {
    std::string postfix = convertToPostfix(expression); // Преобразуем инфиксное выражение в постфиксное
    Stack stack; // Создаем стек для выполнения вычислений

    for (char c : postfix) {
        if (isOperand(c)) {
            stack.push(c - '0'); // Если символ является операндом, преобразуем его в число и помещаем в стек
        } else if (isOperator(c)) {
            int operand2 = stack.pop(); // Извлекаем второй операнд из стека
            int operand1 = stack.pop(); // Извлекаем первый операнд из стека
            int result;

            switch (c) {
                case '+':
                    result = operand1 + operand2; // Выполняем сложение
                    break;
                case '-':
                    result = operand1 - operand2; // Выполняем вычитание
                    break;
                case '*':
                    result = operand1 * operand2; // Выполняем умножение
                    break;
                case '/':
                    if (operand2 == 0) {
                        throw std::runtime_error("Division by zero"); // Если второй операнд равен 0, выбрасываем исключение
                    }
                    result = operand1 / operand2; // Выполняем деление
                    break;
            }

            stack.push(result); // Результат вычисления помещаем в стек
        }
    }

    return stack.pop(); // Возвращаем окончательный результат вычислений
}

std::string InfixCalculator::convertToPostfix(const std::string& expression) {
    std::string postfix; // Строка для хранения постфиксного выражения
    Stack operatorStack; // Стек для хранения операторов
    Queue outputQueue; // Очередь для хранения выходных данных

    for (char c : expression) {
        if (isspace(c)) {
            continue; // Если символ является пробелом, игнорируем его
        } else if (isOperand(c)) {
            outputQueue.enqueue(c); // Если символ является операндом, добавляем его в очередь
        } else if (isOperator(c)) {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(' && hasHigherPrecedence(operatorStack.peek(), c)) {
                outputQueue.enqueue(operatorStack.pop()); // Пока стек не пуст, оператор на вершине стека не является открывающей скобкой
                // и оператор на вершине стека имеет более высокий приоритет, чем текущий оператор,
                // извлекаем оператор из стека и добавляем его в очередь
            }
            operatorStack.push(c); // Добавляем текущий оператор в стек
        } else if (c == '(') {
            operatorStack.push(c); // Если символ является открывающей скобкой, добавляем его в стек
        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                outputQueue.enqueue(operatorStack.pop()); // Пока стек не пуст и оператор на вершине стека не является открывающей скобкой,
                // извлекаем оператор из стека и добавляем его в очередь
            }

            if (operatorStack.isEmpty()) {
                throw std::runtime_error("Mismatched parentheses"); // Если стек пуст, выбрасываем исключение, так как скобки не согласованы
            }

            operatorStack.pop(); // Извлекаем открывающую скобку из стека
        } else {
            throw std::runtime_error("Invalid character"); // Если символ не является ни операндом, ни оператором, выбрасываем исключение
        }
    }

    while (!operatorStack.isEmpty()) {
        if (operatorStack.peek() == '(') {
            throw std::runtime_error("Mismatched parentheses"); // Если на вершине стека находится открывающая скобка, выбрасываем исключение,
            // так как скобки не согласованы
        }
        outputQueue.enqueue(operatorStack.pop()); // Извлекаем оставшиеся операторы из стека и добавляем их в очередь
    }

    while (!outputQueue.isEmpty()) {
        postfix += outputQueue.dequeue(); // Извлекаем элементы из очереди и добавляем их в постфиксную строку
    }

    return postfix; // Возвращаем постфиксное выражение
}

bool InfixCalculator::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/'); // Проверяет, является ли символ оператором
}

bool InfixCalculator::isOperand(char c) {
    return (c >= '0' && c <= '9'); // Проверяет, является ли символ операндом (числом)
}

int InfixCalculator::getPrecedence(char c) {
    if (c == '+' || c == '-') {
        return 1; // Возвращает приоритет оператора + или -
    } else if (c == '*' || c == '/') {
        return 2; // Возвращает приоритет оператора * или /
    } else {
        return 0; // Возвращает приоритет для других символов (открывающая скобка, закрывающая скобка и т. д.)
    }
}

bool InfixCalculator::hasHigherPrecedence(char op1, char op2) {
    int precedence1 = getPrecedence(op1); // Получаем приоритет для оператора op1
    int precedence2 = getPrecedence(op2); // Получаем приоритет для оператора op2

    if (precedence1 == precedence2) {
        return true; // Если операторы имеют одинаковый приоритет, возвращаем true
    }

    return precedence1 > precedence2; // Иначе возвращаем результат сравнения приоритетов
}

int main() {
    InfixCalculator calculator;
    std::string expression;

    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, expression);

    try {
        int result = calculator.calculate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    return 0;
}
