#include "Digital_counter.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Digital_counter::Digital_counter(int value) : counter(value), min(0), max(100), step(1) {
    if (value < min || value > max) {
        counter = min;
        cout << "Значення скинуто до мiнiмуму (" << min << ")\n";
    }
}

int Digital_counter::getCounter() const {
    return counter;
}


Digital_counter::Digital_counter(int min, int max, int step) {
    this->min = min;
    this->max = max;
    this->step = step;
    this->counter = min;
}

Digital_counter::Digital_counter(const Digital_counter& other)
    : counter(other.counter), min(other.min), max(other.max), step(other.step) {
}

Digital_counter::Digital_counter(Digital_counter&& other) noexcept
    : counter(other.counter), min(other.min), max(other.max), step(other.step) {
    other.counter = 0;
}


void Digital_counter::setCounter(int min) {counter = min;}

void Digital_counter::setMin(int min) {
    if (min < max) {
        this->min = min;
        if (counter < min) counter = min;
    }
}

void Digital_counter::setMax(int max) {
    if (max > min) {
        this->max = max;
        if (counter > max) counter = max;
    }
}

void Digital_counter::setStep(int step) {
    if (step > 0 && step <= (max - min)) {
        this->step = step;
    }
}

void Digital_counter::show() {
    cout << "Значення лiчильника: " << counter << " (Дiапазон значень: " << min << "-" << max
        << ", Крок: " << step << ")\n";
}

Digital_counter& Digital_counter::operator=(const Digital_counter& other) { 
    if (this != &other) {
        counter = other.counter;
        min = other.min;
        max = other.max;
        step = other.step;
    }
    return *this;
}

Digital_counter& Digital_counter::operator=(Digital_counter&& other) noexcept { 
    if (this != &other) {
        counter = other.counter;
        min = other.min;
        max = other.max;
        step = other.step;
        other.counter = 0;
    }
    return *this;
}

void Digital_counter::operator()(int max_value, int min_value, int step) { 
    this->max = max_value;
    this->min = min_value;
    this->counter = min_value;
    this->step = step;
};

Digital_counter Digital_counter::operator++(int) {
    if (counter < max) {
        counter++;
    }
    else {
        std::cout << "Лiчильник досяг максимального значення його скинуто у початковий стан" << endl;
        counter = min;
    }

    return *this;
};

Digital_counter Digital_counter::operator--(int) {
    if (counter > min) {
        counter--;
    }
    else {
        cout << "Лiчильник досяг мiнiмального значення!" << endl;
        counter = min;
    }
    return *this;
};

Digital_counter Digital_counter::operator+=(int) { 
    if (max > (counter + step)) {
        counter += step;
    }
    else {
        cout << "Лiчильник досяг максимального значення, його скинуто у початковий стан" << endl;
        counter = min;
    }

    return *this;
};

Digital_counter Digital_counter::operator-=(int) {
    if (counter > (counter + min)) {
        counter -= step;
    }
    else {
        cout << "Лiчильник досяг мiнiмального значення!" << endl;
        counter = min;
    }
    return *this;
};

std::ostream& operator<<(std::ostream& os, const Digital_counter& dc) {
    os << "\nЗначення лiчильника: " << dc.counter
        << "\nМаксимальне значення лiчильника: " << dc.min
        << "\nМiнiмальне значення лiчильника: " << dc.max
        << "\nКрок лiчильника: " << dc.step;
    return os;
}
std::istream& operator>>(std::istream& is, Digital_counter& dc) {
    int min, max, step;

    std::cout << "Введiть мiнiмальне значення: ";
    is >> min; 
    while (min <= 0) {
        if (std::cin.fail()) {
            std::cout << "Некоректний ввiд! Спробуйте ще раз.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
		std::cout << "Мiнiмальне значення не може бути меншим або рiвним нулю!" << std::endl;
        std::cout << "Введiть мiнiмальне значення: ";
        is >> min;
    }
    std::cout << "Введiть максимальне значення: ";
	is >> max;
    while (max <= 0) {
        if (std::cin.fail()) {
            std::cout << "Некоректний ввiд! Спробуйте ще раз.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
		std::cout << "Максимальне значення не може бути меншим або рiвним нулю!" << std::endl;
        std::cout << "Введiть максимальне значення: ";
        is >> max;
    }

    while (max <= min) {

        std::cout << "Максимальне значення не може бути меншим за мiнiмальне значення!" << std::endl;
        std::cout << "Введiть максимальне значення лiчильника: ";
        is >> max;
    }

    std::cout << "Введіть крок: ";
    is >> step;

    while (step <= 0 || step > (max - min)) {
        if (std::cin.fail()) {
            std::cout << "Некоректний ввiд! Спробуйте ще раз.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << "Крок не може бути бiльшим за рiзницю мiж мiнiмальним i максимальним елементом!" << std::endl;
        std::cout << "Введiть крок: ";
        is >> step;
    }

    dc = Digital_counter(min, max, step); 
    return is;
}
