#include "File.h"
#include <fstream>
#include <sstream>
#include "Iterator.h"

void FileData::addParticipant(int id) {
    participants.push_back({ id, {} });
}

int FileData::addCounter(int participantId, Digital_counter counter) {
    for (std::vector<Participant>::iterator it = participants.begin(); it != participants.end(); ++it) {
        Participant& participant = *it;
        if (participant.id == participantId) {
            participant.counters.emplace_back(std::move(counter));
            return participant.counters.size() - 1; 
        }
    }
    return -1; 
}

void FileData::addStopwatch(int participantId, int counterIndex, Stopwatch stopwatch) {
    for (std::vector<Participant>::iterator it = participants.begin(); it != participants.end(); ++it) {
        Participant& participant = *it;
        if (participant.id == participantId) {
            if (counterIndex >= 0 && counterIndex < static_cast<int>(participant.counters.size())) {
                participant.counters[counterIndex].stopwatches.push_back(std::move(stopwatch));
                return;
            }
        }
    }
}

bool FileData::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Помилка вiдкриття файла: " << filename << std::endl;
        return false;
    }

    for (auto it = participants.begin(); it != participants.end(); ++it) {
        const Participant& participant = *it;
        out << "Participant " << participant.id << "\n";

        for (auto counterIt = participant.counters.begin(); counterIt != participant.counters.end(); ++counterIt) {  
               const CounterEntry& counter = *counterIt;  
               out << "Counter " << counter.counter->getCounter() << "\n";  

               for (auto stopwatchIt = counter.stopwatches.begin(); stopwatchIt != counter.stopwatches.end(); ++stopwatchIt) {  
                   const Stopwatch& stopwatch = *stopwatchIt;  
                   out << "Stopwatch " << stopwatch.getResult() << "\n";  
               }  
        }

    }

    out.close();
    return true;
}

bool FileData::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Помилка вiдкриття файлу для читання: " << filename << std::endl;
        return false;
    }

    participants.clear();
    std::string line;
    Participant currentParticipant;
    bool hasParticipant = false;

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Participant") {
            if (hasParticipant) {
                participants.push_back(std::move(currentParticipant));
            }
            currentParticipant = Participant{};
            iss >> currentParticipant.id;
            hasParticipant = true;
        }
        else if (type == "Counter") {
            int value;
            if (iss >> value) {
                CounterEntry counterEntry;
                counterEntry.counter = std::make_unique<Digital_counter>(value);
                currentParticipant.counters.push_back(std::move(counterEntry));
            }
        }
        else if (type == "Stopwatch") {
            double time;
            if (iss >> time && !currentParticipant.counters.empty()) {
                currentParticipant.counters.back().stopwatches.emplace_back(time);
            }
        }
        else {
            std::cout << "Невiдомий тип у файлі: " << line << std::endl;
        }
    }

    if (hasParticipant) {
        participants.push_back(std::move(currentParticipant));
    }

    return true;
}