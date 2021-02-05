/*Реализовать класс UnorderedSet — упрощенный аналог std::unordered_set, реализующий операции вставки (Insert), удаления (Erase) и поиска элемента (Find) за константное (в среднем) время.

std::unordered_set реализован посредством хеш-таблицы. Хеш-таблица представляет собой массив списков. Каждому элементу с помощью хеш-функции (отображения из множества элементов во множество целых неотрицательных чисел) ставится в соответствие индекс его позиции в массиве. При этом индексы некоторых объектов могут совпадать, для решения этих «коллизий» каждый элемент массива представляет собой связный список элементов, попавших в эту ячейку.

Таким образом, вставка элемента — это вычисление позиции элемента с помощью хеш-функции, и вставка в конец соответствующего списка (если его там ранее не было). Удаление — вычисление позиции элемента в массиве и удаление из соответствующего списка. Поиск — вычисление позиции + поиск в списке. Для простоты методы Insert и Erase могут возвращать void, а Find — bool.

Чтобы уменьшить вероятность коллизий при добавлении большого числа элементов, массив нужно периодически расширять (при достижении числа вставленных элементов равным размеру массива), при этом позиции вставленных элементов нужно пересчитывать заново (элемент, который был в одной позиции, в расширенном массиве может оказаться в другой). Начальную вместимость UnorderedSet установите равной 100 и расширяйте в константное число раз при превышении вместимости.

В этой задаче запрещено использовать ассоциативные контейнеры STL, но можно использовать последовательные. В качестве хеш-функции используйте шаблонный функтор std::hash и взятие остатка для получения индекса.

Решите с помощью нее следующую задачу. Реализуйте структуру данных типа «множество строк». Хранимые строки — непустые последовательности длиной не более 10 символов, состоящие из строчных латинских букв. Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству. Максимальное количество элементов в хранимом множестве не превосходит 106.

*/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

template<class T, class Hash, class Equal>
class HashTable {
    size_t capacity = 100;
    size_t size     = 0;
    std::vector<std::list<T>> hashTable;
    Hash hash;
    Equal equal;
public:
    HashTable():
        capacity  (100),
        size      (0),
        hashTable (capacity, std::list<T> (0))
    { }

    HashTable(const size_t &capacity);

    HashTable<T, Hash, Equal> &operator=(const HashTable<T, Hash, Equal> &that);

    void Insert(const T &element);

    void Erase(const T &element);

    bool Find(const T &element) const;

    bool checkIfToRehash() const;

    void rehash();

    void operation(const char &request, const T &str);
};

template<class T, class Hash, class Equal>
void HashTable<T, Hash, Equal>::Insert(const T &element) {
    size_t newIndex = hash(element) % capacity;
    if (!Find(element)) {
        hashTable[newIndex].push_back(element);
        ++size;
    }
    if (checkIfToRehash()) {
        rehash();
    }
}

template<class T, class Hash, class Equal>
void HashTable<T, Hash, Equal>::Erase(const T &element) {
    size_t newIndex = hash(element) % capacity;
    if (Find(element)) {
        auto it = std::find(hashTable[newIndex].begin(), hashTable[newIndex].end(), element);
        hashTable[newIndex].erase(it);
        --size;
    }
}

template<class T, class Hash, class Equal>
bool HashTable<T, Hash, Equal>::Find(const T &element) const {
    size_t newIndex = hash(element) % capacity;
    for (auto i = hashTable[newIndex].begin(); i != hashTable[newIndex].end(); i = std::next(i)) {
        if (equal(*i, element)) {
            return true;
        }
    }
    return false;
}

template<class T, class Hash, class Equal>
bool HashTable<T, Hash, Equal>::checkIfToRehash() const {
    return size >= capacity;
}

template<class T, class Hash, class Equal>
void HashTable<T, Hash, Equal>::rehash() {
    HashTable<T, Hash, Equal> temp(capacity * 2);
    for (int i = 0; i < capacity; ++i) {
        for (auto iter = hashTable[i].begin(); iter != hashTable[i].end(); iter = std::next(iter)) {
            temp.Insert(*iter);
        }
    }
    *this = temp;
    temp.hashTable.clear();
}

template<class T, class Hash, class Equal>
HashTable<T, Hash, Equal>::HashTable(const size_t &capacity):
    capacity  (capacity),
    size      (0),
    hashTable (capacity, std::list<T> (0))
{ }

template<class T, class Hash, class Equal>
HashTable<T, Hash, Equal> &HashTable<T, Hash, Equal>::operator=(const HashTable<T, Hash, Equal> &that) {
    this->capacity = that.capacity;
    this->size = that.size;
    this->hashTable = that.hashTable;
    return *this;
}

template<class T, class Hash, class Equal>
void HashTable<T, Hash, Equal>::operation(const char &request, const T &str) {
    if (request == '+') {
        Insert(str);
    } else if (request == '-') {
        Erase(str);
    } else if (request == '?') {
        if (Find(str)) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}


int main() {
    HashTable<std::string, std::hash<std::string>, std::equal_to<std::string>> hashTable;
    char request;
    std::string str = "";
    while ((request = getchar()) != '#') {
        std::cin >> str;
        hashTable.operation(request, str);
        std::cin.get ();
    }
    return 0;
}

