#include "Results.h"
#include "Stopwatch.h"
#include "Digital_counter.h"
#include "Iterator.h"
#include <algorithm>
#include <numeric>
#include <iostream>


void Results::loadFromFileData(const FileData& fileData) {
    results.clear(); 

    for (const auto& participant : fileData.getParticipants()) {
        for (const auto& counter : participant.counters) {
            Iterator swIterator;

            for (const auto& stopwatch : counter.stopwatches) {
                swIterator.add(stopwatch);
            }

            for (Stopwatch* it = swIterator.begin(); it != swIterator.end(); ++it) {
                Result r;
                r.participantId = participant.id;
                r.time = it->getResult();
                r.counterValue = counter.counter->getCounter();
                results.push_back(r);
            }
        }
    }
}

void Results::addResult(int participantId, const Stopwatch& stopwatch, const Digital_counter& counter) {
   Result r;  
   r.participantId = participantId;  
   r.time = stopwatch.getResult();
   r.counterValue = counter.getCounter();  
   results.push_back(r);  
}

double Results::min() const {
    if (results.empty())
        return 0.0;

    double min_time = results[0].time;

    for (std::vector<Result>::const_iterator it = results.begin(); it != results.end(); ++it) {
        if (it->time < min_time) {
            min_time = it->time;
        }
    }

    std::cout << "Мiнiмальний результат: " << min_time << std::endl;
    return min_time;
} 


double Results::max() const {
    if (results.empty())
        return 0.0;

    double max_time = results[0].time;

    for (const auto& result : results) {
        if (result.time > max_time) {
            max_time = result.time;
        }
    }

    std::cout << "Максимальний результат: " << max_time << std::endl;
    return max_time;
}

double Results::middle() const {
    if (results.empty())
        return 0.0;
    Iterator it;
    double sum = 0.0;
    for (const auto& result : results) {
        sum += result.time;
    }

    double average = sum / results.size();
    std::cout << "Середнє значення часу: " << average << std::endl;
    return average;
}
bool compareByTime(const Result& a, const Result& b) {
    return a.time < b.time;
}

void Results::showTopResults() const {
    if (results.empty()) {
        std::cout << "Немає iнформацiї про результати\n";
        return;
    }

    auto sorted = results;
    std::sort(sorted.begin(), sorted.end(), compareByTime);

    std::cout << "\nТоп 3 переможця:\n";
    size_t limit = std::min<size_t>(3, sorted.size());
    for (size_t i = 0; i < limit; ++i) {
        std::cout << i + 1 << ". Учасник " << sorted[i].participantId
            << " - Час: " << sorted[i].time << "с, Значення лiчильника: "
            << sorted[i].counterValue << "\n";
    }
}

void Results::clearResults() {
    results.clear();
}