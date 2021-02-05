/*Вам предстоит в очередной раз слить два отсортированных массива в один большой отсортированный. Чем эта задача отличается от задачи B? Тем, что у вас в решении должно быть задействовано лишь O(1) дополнительной памяти. В качестве послабления, можно делать слияние за .*/
#include <iostream>
#include <vector>
#include <algorithm>

void readVector(size_t &size, std::vector<int> &myVector) {
    std::cin >> size;
    if (myVector.size() == 0) {
        myVector.reserve(size);
    }
    for (int i = 0; i < size; ++i) {
        int number = 0;
        std::cin >> number;
        myVector.push_back(number);
    }
}

void printVector(std::vector<int> &myVector) {
    for (auto &element: myVector) {
        std::cout << element << " ";
    }
    std::cout << '\n';
}

void inPlaceMerge(std::vector<int>::iterator aBegin, std::vector<int>::iterator aEnd,
                  std::vector<int>::iterator bBegin, std::vector<int>::iterator bEnd) {
    size_t firstSize = aEnd - aBegin;
    size_t secondSize = bEnd - bBegin;
    if (firstSize == 0 || secondSize == 0) {
        return;
    }
    if (firstSize == 1 && secondSize == 1) {
        if (*aBegin > *bBegin) {
            std::swap(*aBegin, *bBegin);
        }
        return;
    }
    auto firstPointer = aBegin;
    auto secondPointer = bBegin;
    if (firstSize >= secondSize) {
        firstPointer = std::next(aBegin, firstSize / 2);
        secondPointer = std::lower_bound(bBegin, bEnd, *firstPointer);
    } else {
        secondPointer = std::next(bBegin, secondSize / 2);
        firstPointer = std::upper_bound(aBegin, aEnd, *secondPointer);
    }
    bBegin = std::rotate(firstPointer, bBegin, secondPointer);
    inPlaceMerge(aBegin, firstPointer, firstPointer, bBegin);
    inPlaceMerge(bBegin, secondPointer, secondPointer, bEnd);
}

int main() {
    size_t firstSize = 0, secondSize = 0;
    std::vector<int> vector;
    readVector(firstSize, vector);
    readVector(secondSize, vector);
    auto mid = std::next(vector.begin(), firstSize);
    inPlaceMerge(vector.begin(), mid, mid, vector.end());
    printVector(vector);
    return 0;
}
