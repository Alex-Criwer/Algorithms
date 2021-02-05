/*В аудитории есть N парт, расположенных вдоль прямой. Необходимо рассадить за них K студентов. Но, так как социальную дистанцию никто не отменял, необходимо максимизировать минимальное расстояние между студентами.
*/

#include <iostream>
#include <vector>

void enterVector(size_t size, std::vector<int> &myVector) {
    myVector.reserve(size);
    for (int i = 0; i < size; ++i) {
        int number = 0;
        std::cin >> number;
        myVector.push_back(number);
    }
}

bool checkIfAppropriate(size_t distance, size_t numberOfStudents, std::vector<int> &coordinates) {
    size_t counterOfStudents = 1;
    int prevStudent = coordinates[0];
    for (auto &element: coordinates) {
        if (element - prevStudent >= distance) {
            ++counterOfStudents;
            prevStudent = element;
        }
    }
    return counterOfStudents >= numberOfStudents;
}

size_t binarySearchByAnswer(const size_t &numberOfDesc, const size_t &numberOfStudents, std::vector<int> &coordinates) {
    int left = 0;
    int right = coordinates.back() - coordinates[0] + 1;
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (checkIfAppropriate(middle, numberOfStudents, coordinates)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    size_t numberOfDesks = 0;
    size_t numberOfStudents = 0;
    std::vector<int> coordinates;
    std::cin >> numberOfDesks >> numberOfStudents;
    enterVector(numberOfDesks, coordinates);
    size_t distance = binarySearchByAnswer(numberOfDesks, numberOfStudents, coordinates);
    std::cout << distance;
    return 0;
}
