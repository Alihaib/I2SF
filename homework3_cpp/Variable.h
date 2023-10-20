#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<cstring>
#include<string.h>
using namespace std;

using namespace std;
class Variable {
private:
	string variablename;
	double coefficient;

public:
	Variable();
	Variable(double c);
	Variable(double c, const string& n);
	Variable(const Variable& other);
	Variable operator+(const Variable& other) const;
	Variable operator-(const Variable& other) const;
	Variable operator*(const Variable& other) const;
	Variable operator*(double c) const;
	Variable& operator+=(const Variable& other);
	Variable& operator-=(const Variable& other);
	Variable& operator*=(const Variable& other);
	bool operator==(const Variable& other) const;
	Variable& operator=(const Variable& other);
	double operator()(const char* vars, const double* values) const;
	string getname()const;
	double getcoefficient()const;
	friend ostream& operator<<(ostream& os, const Variable& var);
	int getExponent() const;
};
