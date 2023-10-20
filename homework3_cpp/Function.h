#include<iostream>
#include"Variable.h"
using namespace std;
class Function
{
private:
	Variable* functionVar;
	int functionSize;
public:
	Function();
	Function(const Function& other);
	Function& operator+=(const Variable& var);
	Function& operator-=(const int index);
	Function operator+(const Function& other) const;
	Function operator-(const Function& other) const;
	friend ostream& operator<<(ostream& os, const Function& f);
	Function operator*(const Function& other) const;
	Function operator*(const double factor) const;
	Function& operator=(const Function& other);
	bool operator==(const Function& other) const;
	Variable operator[](size_t index) const;
	int getsize()const;
	~Function();
	Variable getvariable(int i)const;
};




