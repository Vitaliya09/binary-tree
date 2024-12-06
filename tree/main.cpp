#include <iostream>
#include "tree.hpp"

void print_tree(tree_node* node) {
    if (node) {
        print_tree(node->left.get());
        std::cout << node->value << " ";
        print_tree(node->right.get());
    }
}

int main() {
    // Создаем дерево
    tree t;

    // Тестируем вставку элементов
    std::cout << "Вставка значений: 10, 5, 20, 3, 7, 15, 25\n";
    t.insert(10);
    t.insert(5);
    t.insert(20);
    t.insert(3);
    t.insert(7);
    t.insert(15);
    t.insert(25);

    // Выводим дерево после вставки
    std::cout << "Дерево после вставок: ";
    print_tree(t.root.get());
    std::cout << std::endl;

    // Тестируем удаление элементов
    std::cout << "\nУдаление значений: 5, 20, 3\n";
    t.remove(5);
    t.remove(20);
    t.remove(3);

    // Выводим дерево после удаления
    std::cout << "Дерево после удаления: ";
    print_tree(t.root.get());
    std::cout << std::endl;

    // Тестируем повторное удаление (значение уже отсутствует)
    std::cout << "\nПовторное удаление значений: 5, 20, 3 (должен вернуть false)\n";
    if (!t.remove(5)) std::cout << "Значение 5 не найдено\n";
    if (!t.remove(20)) std::cout << "Значение 20 не найдено\n";
    if (!t.remove(3)) std::cout << "Значение 3 не найдено\n";

    // Вставляем новые элементы
    std::cout << "\nВставка значений: 2, 8, 12\n";
    t.insert(2);
    t.insert(8);
    t.insert(12);

    // Выводим дерево после повторной вставки
    std::cout << "TДерево после новых вставок: ";
    print_tree(t.root.get());
    std::cout << std::endl;

    return 0;
}
