#ifndef RESULTS_H
#define RESULTS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Digital_counter.h"
#include "Stopwatch.h"
#include "File.h"


struct Result {
    int participantId;
    double time;
    int counterValue; 
};


class Results {
private:
    std::vector<Result> results;
     
public:
    void loadFromFileData(const FileData& fileData);
    void addResult(int participantId, const Stopwatch& stopwatch , const Digital_counter& counter);
    void showTopResults() const;
    void clearResults();
    double min() const;
    double max() const;
    double middle() const;
    size_t getResultsCount() const { return results.size(); }
    
};

#endif
