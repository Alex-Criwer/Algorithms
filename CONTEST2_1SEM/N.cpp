#include<iostream>
using namespace std;

void swap(int* pointer1, int* pointer2) {
    int temp = *pointer1;
    *pointer1 = *pointer2;
    *pointer2 = temp;
}

int* findTheMedian(int* begin, int* end) {
    int* median = begin + (end - begin) / 2;
    if ((*begin < *median && *begin > *end) || (*begin > *median && *begin < *end)) {
        swap(begin, end);
    }
    else if((*median > *begin && *median < *end) || (*median < *begin && *median > *end)) {
        swap(median,end);
    }
    return end;
}

void partition(int* begin, int* end, int*& i, int*& j) {
    int* pivot = findTheMedian(begin,end);
    int* leftOfEqualElements = begin - 1;
    int* rightOfEqualElements = end;
    while(i <= j) {
        while(*i < *pivot) {
            ++i;
        }
        while(*j > *pivot){
            --j;
        }
        if(i >= j) {
            break;
        }
        swap(i,j);
        if(*i == *pivot) {
            ++leftOfEqualElements;
            swap(i,leftOfEqualElements);
        }
        ++i;
        if(*j == *pivot) {
            --rightOfEqualElements;
            swap(j,rightOfEqualElements);
        }
        --j;
    }
    swap(i,end);
    j = i - 1;
    ++i;
    for (int* pointer = begin; pointer <= leftOfEqualElements; ++pointer, --j) {
        swap(pointer, j);
    }
    for (int* pointer = end - 1; pointer >= rightOfEqualElements; --pointer, ++j) {
        swap(pointer, i);
    }
}

void quickSort(int* begin, int* end) {
    if(begin <= end) {
        int *i = begin;
        int *j = end - 1;
        partition(begin,end,i,j);
        quickSort(begin,j);
        quickSort(i,end);
    }
}

int main() {
    int size;
    cin >> size;
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i] ;
    }
    int* begin = array;
    int* end = array+ size - 1;
    quickSort(begin,end);

    for (int i = 0; i < size; ++i) {
        if( (i + 1) % 10 == 0)
        cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}
