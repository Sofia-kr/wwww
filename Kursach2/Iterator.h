#ifndef ITERATOR_H
#define ITERATOR_H
#include "Stopwatch.h"


class Iterator {
private:
    Stopwatch* data;     
    size_t current_size;  
    size_t max_size;      

public:
    Iterator();
    ~Iterator();
    void resize(size_t new_max_size);
    void add(const Stopwatch& sw);
    size_t size() const;
    Stopwatch* begin() const;
    Stopwatch* end() const;
};
#endif

