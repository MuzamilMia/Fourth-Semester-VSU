#include "Container.h"
#include <algorithm>

template <typename T>
Container<T>::Container(const Container<T>& other) : container(other.container) {}

template <typename T>
Container<T>::Container(const std::vector<T>& data) : container(data) {}

template <typename T>
Container<T>::Container(std::vector<T>&& data) : container(std::move(data)) {}

template <typename T>
typename std::vector<T>::iterator Container<T>::begin() {
    return container.begin();
}

template <typename T>
typename std::vector<T>::iterator Container<T>::end() {
    return container.end();
}

template <typename T>
bool Container<T>::empty() {
    return container.empty();
}

template <typename T>
void Container<T>::clear() {
    container.clear();
}

template <typename T>
void Container<T>::add(const T& val) {
    container.push_back(val);
}

template <typename T>
size_t Container<T>::size() {
    return container.size();
}

template <typename T>
bool Container<T>::remove_by_index(int index) {
    if (index < 0 || static_cast<size_t>(index) >= size()) {
        return false;
    }
    container.erase(container.begin() + index);
    return true;
}

template <typename T>
bool Container<T>::remove_by_value(const T& value) {
    //typename decltype(container)::iterator
    auto it = std::find(container.begin(), container.end(), value); //
    if (it != container.end()) {
        container.erase(it);
        return true;
    }
    return false;
}

template <typename T>
bool Container<T>::change(int index, const T& val) {
    if (index < 0 || static_cast<size_t>(index) >= size()) {
        return false;
    }
    container[index] = val;
    return true;
}

template <typename T>
void Container<T>::print(std::ostream_iterator<T> it) {
    std::copy(container.begin(), container.end(), it);
}

template <typename T>
void Container<T>::read(std::istream_iterator<T> it) {
    std::istream_iterator<T> eos;
    while (it != eos) { // copy
        add(*it);
        ++it;
    }
}

template <typename T>
Container<T> Container<T>::selection(std::function<bool(const T&)> predicate) {
    std::vector<T> result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
    return Container<T>(std::move(result));
}

template <typename T>
T Container<T>::get_index(int index) {
    if (index < 0 || static_cast<size_t>(index) >= size()) {
        throw std::out_of_range("Index out of range!");
    }
    return container[index];
}

// Explicit instantiation for Weapon (to avoid linker errors)
#include "Weapon.h"
template class Container<Weapon>;