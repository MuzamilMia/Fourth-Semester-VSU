#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <functional>
#include <iterator>
#include <ostream>

template <typename T>
class Container {
private:
    std::vector<T> container;

public:
    Container() = default;
    Container(const Container<T>& other);
    Container(const std::vector<T>& data);
    Container(std::vector<T>&& data);

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    bool empty();
    void clear();
    void add(const T& val);
    size_t size();
    bool remove_by_index(int index);
    bool remove_by_value(const T& value);
    bool change(int index, const T& val);
    void print(std::ostream_iterator<T> it);
    void read(std::istream_iterator<T> it);
    Container<T> selection(std::function<bool(const T&)> predicate);
    T get_index(int index);

    friend std::ostream& operator<<(std::ostream& out, Container& cont) {
        std::ostream_iterator<T> it(out, "\n");
        cont.print(it);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Container& cont) {
        std::istream_iterator<T> it(in);
        cont.read(it);
        return in;
    }
};

#endif // CONTAINER_H