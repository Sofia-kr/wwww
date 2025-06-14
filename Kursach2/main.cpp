#include <iostream>
#include "Digital_counter.h"
#include "Stopwatch.h"
#include "Results.h"
#include "File.h"
#include "Iterator.h"

int main() {
    setlocale(LC_ALL, "ukrainian");

    int countmember = 1;

    Stopwatch timer;
    Results results;
    FileData fileData;
    Iterator iterator;

    Digital_counter counter(0, 10, 2);

    Digital_counter& digitalCounterLinl = counter;
    Digital_counter& stopwatchLink = timer;

    std::cout << "Параметри лiчильника по замовчуванню: ";
    std::cout << counter;
    std::cout << "\nВведiть номер дiї:\n"
        << "1 - налаштування значень лiчильника\n"
        << "2 - збiльшення лiчильника на 1\n"
        << "3 - зменшення лiчильника на 1\n"
        << "4 - зменшення лiчильника на " << counter.getStep() << "\n"
        << "5 - збiльшення лiчильника на " << counter.getStep() << "\n"
        << "6 - показ значення лiчильника\n"
        << "7 - старт таймера\n"
        << "8 - зупинка таймера\n"
        << "9 - мiнiмальний результат забiгу\n"
        << "10 - максимальний результат забiгу\n"
        << "11 - середнiй результат забiгу\n"
        << "12 - ТОП-3 результати\n"
        << "13 - запис у файл\n"
        << "14 - зчитування з файлу\n"
        << "0 - для виходу\n" << std::endl;

    while (true) {
        int min, max, step, input;
      
        std::cout << "Введiть номер дiї: ";
        std::cin >> input;  
        if (input < 0 || input > 14 || std::cin.fail()) {  
           std::cout << "Некоректний ввід! Спробуйте ще раз.\n";  
           std::cin.clear(); 
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
           continue;  
        }
        
        
        switch (input) {
        case 0: {
            std::cout << "\n";
            return 0;
        }
        case 1:
        {
            std::cin >> counter;
            break;
        }
        case 2: {
            counter++;
            break;
        }
        case 3: {
            counter--;
            break;
        }
        case 4: {

            counter -= counter.getStep();
            break;
        }
        case 5: {
            counter += counter.getStep();
            break;
        }
        case 6: {
            digitalCounterLinl.show();
            break;
        }
        case 7: {
            timer.start();
            break;
        }
        case 8: {
            timer.stop();
            stopwatchLink.show();
            results.addResult(countmember, timer, counter.getCounter());
            fileData.addParticipant(countmember);
            int counterIndex = fileData.addCounter(countmember, counter.getCounter());
            fileData.addStopwatch(countmember, counterIndex, timer);
            countmember++;
            timer.reset();
            break;
        }
        case 9: {
            results.min();
            break;
        }
        case 10: {
            results.max();
            break;
        }
        case 11: {
            results.middle();
            break;
        }
        case 12: {
            results.showTopResults();
            break;
        }
        case 13: {
            fileData.saveToFile("C:\\Users\\s8774\\Desktop\\Курсова\\temp_kursak\\Kursach2\\data.txt");

            std::cout << "Результати успiшно записанi у файл results.txt" << std::endl;
            break;
        }
        case 14: {

            fileData.loadFromFile("C:\\Users\\s8774\\Desktop\\Курсова\\temp_kursak\\Kursach2\\data.txt");
            results.loadFromFileData(fileData);
            results.min();
            results.max();
            results.middle();
            results.showTopResults();
            break;
        }
       /* default: {
            std::cout << "Некоректний ввiд! Спробуйте ще раз.\n";
            break;
        }*/
        }

    }
}




