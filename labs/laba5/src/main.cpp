#include <iostream>
#include <string>
#include <memory_resource>
#include "List.cpp"

// Структура с несколькими полями
struct ComplexType {
    int id;
    std::string name;
    double value;

    // Для удобного вывода
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        return os << "ComplexType{id: " << obj.id << ", name: \"" << obj.name << "\", value: " << obj.value << "}";
    }

    // Для сравнения
    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name && value == other.value;
    }
};

// Основная функция
int main() {
    // Используем специальный memory_resource для управления памятью
    DynamicMemoryResource resource;

    // Пример работы с простыми типами (int)
    List<int> intList(&resource);
    intList.PushBack(10);
    intList.PushBack(20);
    intList.PushFront(5);

    std::cout << "Contents of intList: ";
    for (auto it = intList.Begin(); it != intList.End(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Удаление элемента из начала и конца
    intList.PopFront();
    intList.PopBack();
    std::cout << "After popping front and back, intList: ";
    for (auto it = intList.Begin(); it != intList.End(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Пример работы со сложными типами (ComplexType)
    List<ComplexType> complexList(&resource);
    complexList.PushBack({1, "First", 10.5});
    complexList.PushBack({2, "Second", 20.75});
    complexList.PushFront({0, "Zero", 5.0});

    std::cout << "Contents of complexList:\n";
    for (auto it = complexList.Begin(); it != complexList.End(); ++it) {
        std::cout << *it << "\n";
    }

    // Поиск элемента
    ComplexType target = {2, "Second", 20.75};
    auto found = complexList.Find(target);
    if (found != complexList.End()) {
        std::cout << "Found element: " << *found << "\n";
    } else {
        std::cout << "Element not found\n";
    }

    // Удаление элемента
    if (found != complexList.End()) {
        complexList.Erase(found);
        std::cout << "After erasing the found element, complexList:\n";
        for (auto it = complexList.Begin(); it != complexList.End(); ++it) {
            std::cout << *it << "\n";
        }
    }

    // Очистка списка
    complexList.Clear();
    std::cout << "After clearing, complexList is empty: " << std::boolalpha << complexList.IsEmpty() << "\n";

    return 0;
}
