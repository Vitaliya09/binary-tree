#include "tree.hpp"

auto tree::insert(int val) -> tree_node* {
    std::unique_ptr<tree_node> new_node = std::make_unique<tree_node>();
    new_node->value = val;

    if (!root) {
        root = std::move(new_node);  // Перемещаем новый узел в корень
        return root.get();           // Возвращаем указатель на новый узел
    }

    tree_node* current = root.get();
    tree_node* parent = nullptr;

    while (current) {
        parent = current;
        if (val < current->value) {
            if (current->left) {
                current = current->left.get();
            } else {
                parent->left = std::move(new_node);  // Перемещаем new_node в левого потомка
                return parent->left.get();
            }
        } else if (val > current->value) {
            if (current->right) {
                current = current->right.get();
            } else {
                parent->right = std::move(new_node);  // Перемещаем new_node в правого потомка
                return parent->right.get();
            }
        } else {
            return current;  // Если значение уже существует в дереве
        }
    }

    return nullptr;
}

auto tree::remove(int val) -> bool {
    if (!root) return false;

    tree_node* current = root.get();
    tree_node* parent = nullptr;

    // Ищем элемент, который нужно удалить
    while (current && current->value != val) {
        parent = current;
        if (val < current->value) {
            current = current->left.get();
        } else {
            current = current->right.get();
        }
    }

    if (!current) return false; // Элемент не найден

    // Случай, когда у удаляемого узла нет дочерних элементов
    if (!current->left && !current->right) {
        if (parent) {
            if (parent->left.get() == current) {
                parent->left.reset();  // Освобождаем память
            } else {
                parent->right.reset();  // Освобождаем память
            }
        } else {
            root.reset();  // Если удаляется корень
        }
    }
    // Случай, когда у удаляемого узла только один дочерний элемент
    else if (!current->left || !current->right) {
        std::unique_ptr<tree_node>& child = (current->left) ? current->left : current->right;
        if (parent) {
            if (parent->left.get() == current) {
                parent->left = std::move(child);  // Перемещаем ребенка
            } else {
                parent->right = std::move(child);  // Перемещаем ребенка
            }
        } else {
            root = std::move(child);  // Если удаляется корень
        }
    }
    // Случай, когда у удаляемого узла два дочерних элемента
    else {
        tree_node* successor_parent = current;
        std::unique_ptr<tree_node>& successor = current->right;

        // Ищем наименьший элемент в правом поддереве
        while (successor->left) {
            successor_parent = successor.get();
            successor = std::move(successor->left);  // Здесь используем std::move для перемещения
        }

        // Заменяем значение текущего узла на значение наследника
        current->value = successor->value;

        // Удаляем наследника
        if (successor_parent->left.get() == successor.get()) {
            successor_parent->left = std::move(successor->right);  // Перемещаем правого ребенка наследника
        } else {
            successor_parent->right = std::move(successor->right);  // Перемещаем правого ребенка наследника
        }
    }
    return true;
}

