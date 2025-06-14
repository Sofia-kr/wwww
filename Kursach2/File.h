#ifndef FILE_DATA_H
#define FILE_DATA_H

#include <vector>
#include <memory> 
#include "Digital_counter.h"
#include "Stopwatch.h"

struct CounterEntry {
    std::unique_ptr<Digital_counter> counter; 
    std::vector<Stopwatch> stopwatches;

    CounterEntry() : counter(std::make_unique<Digital_counter>()) {}
    CounterEntry(Digital_counter c) : counter(std::make_unique <Digital_counter>(std::move(c))) {}

    CounterEntry(const CounterEntry& other)
        : stopwatches(other.stopwatches) {
        if (other.counter)
            counter = std::make_unique<Digital_counter>(*other.counter);
    }

    CounterEntry(CounterEntry&&) = default;
    CounterEntry& operator=(CounterEntry&&) = default;
};

struct Participant {
    int id;
    std::vector<CounterEntry> counters;
};

class FileData {
private:
    std::vector<Participant> participants;
    

public:
    int getParticipantsCount() const { return participants.size(); }  
    const std::vector<Participant>& getParticipants() const { return participants; }
    void addParticipant(int id);
    int addCounter(int participantId, Digital_counter counter);
    void addStopwatch(int participantId, int counterIndex, Stopwatch stopwatch);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename); 
};

#endif