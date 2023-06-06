
#include <iostream>
#include <vector>
#include <functional>

template <typename T, typename Compare>
bool CompareFunction(Compare CompFunc, T& a, T& b) {
    return CompFunc(a, b);
}

struct Process {
    int Priority;
    int SpentTime;
    int RequiredTime;
};

template <typename T, typename Compare = std::less<T>>
class Heap {
public:
    Heap(int SizeOfHeap) : SizeOfHeap(0) {
        HeapVect = new T[SizeOfHeap];
    }
    Heap(Compare CompFunc) : SizeOfHeap(0), CompFunc(CompFunc) {}
    void FuncPushElem(T Value);

    T FuncPopElem();

    bool IsEmpty() const {
        return (SizeOfHeap == 0);
    }

private:
    //HeapVect = new T[];
    std::vector<T> HeapVect;
    Compare CompFunc;
    int SizeOfHeap;
    void FuncSiftUp(int pos);
    void FuncSiftDown(int pos);
};

template<class T, class Compare>
void Heap<T, Compare>::FuncPushElem(T Value) {
    if (SizeOfHeap >= HeapVect.size()) {
        HeapVect.push_back(Value);
    }
    else {
        HeapVect[SizeOfHeap] = Value;
    }
    FuncSiftUp(SizeOfHeap);
    SizeOfHeap++;
}

template<class T, class Compare>
T Heap<T, Compare>::FuncPopElem() {
    T ResVect = HeapVect[0];
    SizeOfHeap--;
    if (SizeOfHeap > 0) {
        HeapVect[0] = HeapVect[SizeOfHeap];
        FuncSiftDown(0);
    }
    return ResVect;
}


template<class T, class Compare>
void Heap<T, Compare>::FuncSiftUp(int pos) {
    while (pos > 0) {
        int pos_parent = (pos - 1) / 2;
        if (CompareFunction(CompFunc, HeapVect[pos], HeapVect[pos_parent])) {
            std::swap(HeapVect[pos], HeapVect[pos_parent]);
            pos = pos_parent;
        }
        else {
            break;
        }
    }
}

template<class T, class Compare>
void Heap<T, Compare>::FuncSiftDown(int pos) {
    while (true) {
        int child_left = 2 * pos + 1;
        int child_right = 2 * pos + 2;
        int child_smallest = pos;
        if (child_left < SizeOfHeap && CompareFunction(CompFunc, HeapVect[child_left], HeapVect[child_smallest])) {
            child_smallest = child_left;
        }
        if (child_right < SizeOfHeap && CompareFunction(CompFunc, HeapVect[child_right], HeapVect[child_smallest])) {
            child_smallest = child_right;
        }
        if (child_smallest != pos) {
            std::swap(HeapVect[pos], HeapVect[child_smallest]);
            pos = child_smallest;
        }
        else {
            break;
        }
    }
}

int main()
{
    int CountOfProcesses = 0, CountOfSwitches = 0;
    std::cin >> CountOfProcesses;

    std::vector<Process> ProcessVect(CountOfProcesses);
    for (int i = 0; i < CountOfProcesses; ++i)
    {
        std::cin >> ProcessVect[i].Priority >> ProcessVect[i].RequiredTime;
    }

    Heap<Process, std::function<bool(Process, Process)>> HeapVect(
        [](Process Proc1, Process Proc2) {
            return (Proc1.Priority * (Proc1.SpentTime + 1)) > (Proc2.Priority * (Proc2.SpentTime + 1)); }
    );

    for (int i = 0; i < CountOfProcesses; ++i) {
        HeapVect.FuncPushElem(ProcessVect[i]);
    }

    int RunningTime = 0;
    while (!HeapVect.IsEmpty()) {

        Process RunningProcess = HeapVect.FuncPopElem();
        int RemainingTime = RunningProcess.RequiredTime - RunningProcess.SpentTime;
        int ExecutionTime = std::min(RunningProcess.Priority, RemainingTime);
        RunningProcess.SpentTime += ExecutionTime;
        RunningTime += ExecutionTime;
        CountOfSwitches += 1;

        if (RunningProcess.SpentTime >= RunningProcess.RequiredTime) {
            continue;
        }

        HeapVect.FuncPushElem(RunningProcess);
    }
    std::cout << CountOfSwitches << std::endl;
    return 0;
}