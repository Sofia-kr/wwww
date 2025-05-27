#include "Digital_counter.h"
#include <iostream>

using namespace std;

Digital_counter::Digital_counter(Digital_counter&&other) {

}
Digital_counter::Digital_counter(const Digital_counter& copyCounter)
{
	counter = copyCounter.counter;
	min = copyCounter.min;
	max = copyCounter.max;
	step = copyCounter.step;
}
Digital_counter::Digital_counter(int min, int max, int step) {
	counter = 0;
	min = 0;
	max = 100;
	step = 10;
}

void Digital_counter::setCounter(int counter) {
	if (counter >= min && counter <= max) {
		this->counter = counter;
	}
	else {
		counter = min;
		cout << "Значення лічильника скинулося до початкового";
	}
}
int Digital_counter::getCounter() const {
	return counter;
}
void Digital_counter::setMin(int min) {
	this->min = min;
}
int Digital_counter::getMin() const {
	return min;
}
void Digital_counter::setMax(int max) {
	this->max = max;
}
int Digital_counter::getMax() const {
	return max;
}
void Digital_counter::setStep(int step) {
	this->step = step;
}
int Digital_counter::getStep() const {
	if (step > max - min) {
		cout << "Крок не може бути більшим за різницю між max та min";
		return 1;
	}
	else { return step; }
}

