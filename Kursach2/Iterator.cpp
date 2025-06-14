#include "Iterator.h"

Iterator::Iterator()
    : data(nullptr), current_size(0), max_size(0) {
}

Iterator::~Iterator() {
    delete[] data;
}

void Iterator::resize(size_t new_max_size) {
    Stopwatch* new_data = new Stopwatch[new_max_size];
    for (size_t i = 0; i < current_size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    max_size = new_max_size;
}

void Iterator::add(const Stopwatch& sw) {
    if (current_size >= max_size) {
        resize(max_size == 0 ? 1 : max_size * 2);
    }
    data[current_size++] = sw;
}

size_t Iterator::size() const {
    return current_size;
}

Stopwatch* Iterator::begin() const {
    return data;
}

Stopwatch* Iterator::end() const {
    return data + current_size;
}