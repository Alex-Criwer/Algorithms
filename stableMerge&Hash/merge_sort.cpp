/*Ваша цель — реализовать стабильную сортировку для следующей задачи.

Выведите фамилии и имена абитуриентов, подавших документы на поступление на ПМИ ФПМИ в порядке убывания их среднего балла по ЕГЭ.

Про каждого ученика известны их фамилии, имена и баллы ЕГЭ по следующим предметам: информатика, математика и русский язык.*/

#include <iostream>
#include <vector>
#include <string>

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
        std::cout << element.firstName_ << " " << element.secondName_ << '\n';
    }
}

void merge(std::vector<Student>::iterator firstBegin,
           std::vector<Student>::iterator firstEnd,
           std::vector<Student>::iterator secondBegin,
           std::vector<Student>::iterator secondEnd) {
    size_t firstSize = firstEnd - firstBegin;
    size_t secondSize = secondEnd - secondBegin;
    std::vector<Student> result;
    result.reserve(firstSize + secondSize);
    auto i = firstBegin;
    auto j = secondBegin;
    while (i != firstEnd && j != secondEnd) {
        if ((*i).points >= (*j).points) {
            result.push_back(*i);
            i = std::next(i);
        } else {
            result.push_back(*j);
            j = std::next(j);
        }
    }
    while (i != firstEnd) {
        result.push_back(*i);
        i = std::next(i);
    }
    while (j != secondEnd) {
        result.push_back(*j);
        j = std::next(j);
    }
    std::copy(result.begin(), result.end(), firstBegin);
}

void MergeSort(std::vector<Student>::iterator begin,
               std::vector<Student>::iterator end) {
    int distance = end - begin;
    if (distance <= 1) {
        return;
    }
    auto middle = std::next(begin, distance / 2);
    MergeSort(begin, middle);
    MergeSort(middle, end);
    merge(begin, middle, middle, end);
}

int main() {
    size_t numberOfApplicants = 0;
    std::cin >> numberOfApplicants;
    std::vector<Student> listOfApplicants;
    enterListOfApplicants(numberOfApplicants, listOfApplicants);
    MergeSort(listOfApplicants.begin(), listOfApplicants.end());
    printListOfApplicants(listOfApplicants);
    return 0;
}
