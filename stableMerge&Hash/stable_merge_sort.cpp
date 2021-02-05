/*Ваша цель — реализовать стабильную сортировку для следующей задачи.

Выведите фамилии и имена абитуриентов, подавших документы на поступление на ПМИ ФПМИ в порядке убывания их среднего балла по ЕГЭ.

Про каждого ученика известны их фамилии, имена и баллы ЕГЭ по следующим предметам: информатика, математика и русский язык.

Да, легенда та же самая, но это на значит, что можно просто копипастить код из прошлой задачи. Опять же вас ждут два нововведения:

[-] Нельзя использовать дополнительную память при сортировке.
[+] Можно писать сортировку за .*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Student {
    std::string firstName_;
    std::string secondName_;
    size_t points;

    Student() {
        firstName_ = "";
        secondName_ = "";
        points = 0;
    }

    Student(std::string firstName, std::string secondName, const size_t infPoint, const size_t mathPoints,
            const size_t rusPoints) {
        firstName_ = firstName;
        secondName_ = secondName;
        points = infPoint + mathPoints + rusPoints;
    }
};


void enterListOfApplicants(const size_t &size, std::vector<Student> &students) {
    std::string firstName, secondName;
    size_t infPoints = 0, mathPoint = 0, rusPoints = 0;
    students.reserve(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> firstName >> secondName >> infPoints >> mathPoint >> rusPoints;
        students.emplace_back(firstName, secondName, infPoints, mathPoint, rusPoints);
    }
}

void printListOfApplicants(std::vector<Student> &students) {
    for (auto &element: students) {
        std::cout << element.firstName_ << ' ' << element.secondName_ << '\n';
    }
}

bool myCmp(const Student &lhs, const Student &rhs) {
    return lhs.points> rhs.points;
}


template<typename Cmp>
void inPlaceMerge(std::vector<Student>::iterator aBegin, std::vector<Student>::iterator aEnd,
                  std::vector<Student>::iterator bBegin, std::vector<Student>::iterator bEnd, Cmp cmp) {
    size_t firstSize = std::distance(aBegin, aEnd);
    size_t secondSize = std::distance(bBegin, bEnd);
    if (firstSize == 0 || secondSize == 0) {
        return;
    }
    if (firstSize == 1 && secondSize == 1) {
        if (cmp(*bBegin, *aBegin)) {
            std::swap(*aBegin, *bBegin);
        }
        return;
    }
    auto firstPointer = aBegin;
    auto secondPointer = bBegin;
    if (firstSize >= secondSize) {
        firstPointer = std::next(aBegin, firstSize / 2);
        secondPointer = std::lower_bound(bBegin, bEnd, *firstPointer, cmp);
    } else {
        secondPointer = std::next(bBegin, secondSize / 2);
        firstPointer = std::upper_bound(aBegin, aEnd, *secondPointer, cmp);
    }
    bBegin = std::rotate(firstPointer, bBegin, secondPointer);
    inPlaceMerge(aBegin, firstPointer, firstPointer, bBegin, cmp);
    inPlaceMerge(bBegin, secondPointer, secondPointer, bEnd, cmp);
}

template<typename Cmp>
void MergeSort(std::vector<Student>::iterator begin, std::vector<Student>::iterator end, Cmp cmp) {
    int distance = end - begin;
    if (distance <= 1) {
        return;
    }
    auto middle = std::next(begin, distance / 2);
    MergeSort(begin, middle, cmp);
    MergeSort(middle, end, cmp);
    inPlaceMerge(begin, middle, middle, end, cmp);
}


int main() {
    size_t numberOfApplicants = 0;
    std::cin >> numberOfApplicants;
    std::vector<Student> listOfApplicants;
    enterListOfApplicants(numberOfApplicants, listOfApplicants);
    MergeSort(listOfApplicants.begin(), listOfApplicants.end(), myCmp);
    printListOfApplicants(listOfApplicants);
    return 0;
}
