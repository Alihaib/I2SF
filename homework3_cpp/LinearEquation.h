#include<iostream>
#include"Function.h"
using namespace std;
class LinearEquation
{
private:
	Function m_func;
	double m_freeNum;
public:
     LinearEquation(const Function& function); // Constructor
    friend LinearEquation operator+( const LinearEquation& lhs, const  LinearEquation& rhs); // Addition operator
    friend LinearEquation operator-( const LinearEquation& lhs,const LinearEquation& rhs); // Subtraction operator
    friend ostream& operator<<(std::ostream& os, const LinearEquation& equation); // Output operator
    int getNumVariables() const;
    double getConstant();
    friend bool PossibleSingleSolution(LinearEquation equations[], int size);
};


