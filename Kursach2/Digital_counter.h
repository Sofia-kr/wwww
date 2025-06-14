#pragma once
#include <iostream>
class Digital_counter
{
private:
	int counter;
	int min;
	int max; 
	int step;
public:
    Digital_counter(int value = 0);
    Digital_counter(int min, int max, int step = 1);
    Digital_counter(const Digital_counter& other);
    Digital_counter(Digital_counter&& other) noexcept;
    Digital_counter& operator=(const Digital_counter& other);
    Digital_counter& operator=(Digital_counter&& other) noexcept;

    void setCounter(int value);
    int getCounter() const;

    void setMin(int min);
	int getMin() const { return min; }

    void setMax(int max);
	int getMax() const { return max; } 
    void setStep(int step);
	int getStep() const { return step; }
    
    virtual void show();


    void operator ()(int max_value, int min_value, int step);
    Digital_counter operator ++(int);
    Digital_counter operator --(int);
    Digital_counter operator +=(int);
    Digital_counter operator -=(int);

    friend std::ostream& operator<<(std::ostream& os, const Digital_counter& dc);
    friend std::istream& operator>>(std::istream& is, Digital_counter& dc);

};

