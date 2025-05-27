#pragma once
class Digital_counter
{
private:
	int counter;
	int min;
	int max; 
	int step;
public:
	Digital_counter(int min, int max, int step);
	Digital_counter(const Digital_counter& copyCounter);
	Digital_counter(Digital_counter&& other);
	~Digital_counter() = default;
	void setCounter(int counter);
	int getCounter() const;
	void setMin(int min);
	int getMin() const;
	void setMax(int max);
	int getMax() const;
	void setStep(int step);
	int getStep() const;

	friend void operator++(Digital_counter counter);
		
	friend void operator--(Digital_counter counter);

	friend void operator+=(Digital_counter counter, int value);

	friend void operator-=(Digital_counter counter, int value);

	Digital_counter& operator=(Digital_counter counter);

	friend void operator<<(Digital_counter counter, int value);

	friend void operator>>(Digital_counter counter, int value);
};

