#include "Stopwatch.h"
#include <iostream>


int Stopwatch::getResult() const { return work_time; }

void Stopwatch::start() {
    if (!is_running) {
        start_time = time(nullptr);
        is_running = true;
        std::cout << "������ ��������!\n";
    }
}

void Stopwatch::stop() {
    if (is_running) {
        work_time += difftime(time(nullptr), start_time);
        is_running = false;
    }
    else {
        std::cout << "������ �� ��������!\n";
    }
}

void Stopwatch::reset() {
    work_time = 0;
    is_running = false;
}

void Stopwatch::show() {
    std::cout << "��� ���i��: " << work_time << " �.\n";
}