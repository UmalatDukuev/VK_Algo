

#include <iostream>

class Stack {
public:
    Stack() : Size(0), SizeOfBuffer(8) {
        DataOfQueue = new int[SizeOfBuffer];
    };

    ~Stack() {
        delete[] DataOfQueue;
    };

    bool IsEmpty() {
        if (Size == 0)
            return true;
        else
            return false;
    };

    void PushValue(int Value) {

        if (SizeOfBuffer <= Size) {
            DoubleBuffer();
        }
        DataOfQueue[Size] = Value;
        Size++;
    };
    int PopValue() {
        if (IsEmpty() == true) {
            std::cout << "Stack is empty" << std::endl;
            return 0;
        }
        Size--;
        return DataOfQueue[Size];
    };
private:
    int Size;
    int SizeOfBuffer;
    int* DataOfQueue;
    void DoubleBuffer() {
        int* NewDataOfQueue = new int[SizeOfBuffer * 2];
        SizeOfBuffer *= 2;
        for (int i = 0; i < Size; i++) {
            NewDataOfQueue[i] = DataOfQueue[i];
        }
        delete[] DataOfQueue;
        DataOfQueue = NewDataOfQueue;
    };
};

class Queue {
private:
    Stack Stack1;
    Stack Stack2;
public:
    void PushValue(int Value) {
        Stack1.PushValue(Value);
    };
    bool IsEmpty() {
        if (Stack1.IsEmpty() == true && Stack2.IsEmpty() == true)
            return true;
        else
            return false;

    };
    int PopValue() {
        if (IsEmpty() == true) {
            std::cout << "Queue is empty" << std::endl;
            return 0;
        }
        if (Stack2.IsEmpty()) {
            while (!Stack1.IsEmpty()) {
                Stack2.PushValue(Stack1.PopValue());
            }
        }
        return Stack2.PopValue();

    };

};


int main()
{
    std::string Answer = "YES";

    int NumberOfCommands = 0, a = 0, b = 0;
    std::cin >> NumberOfCommands;
    Queue Q;
    for (int i = 0; i < NumberOfCommands; i++) {
        std::cin >> a >> b;
        if (a == 2) {
            int tmp = -1;
            if (!Q.IsEmpty()) {
                tmp = Q.PopValue();
            }
            if (b != tmp)
                Answer = "NO";
        }
        else if (a == 3) {
            Q.PushValue(b);
        }
    }
    std::cout << Answer << std::endl;
    return 0;
}
