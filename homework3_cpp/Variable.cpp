#include "Variable.h"


Variable::Variable() :variablename("\0"), coefficient(0) {}



Variable::Variable(double c) : variablename("\0"), coefficient(c)
{
}

Variable::Variable(double c, const string& n) : variablename(n), coefficient(c)
{
}

Variable::Variable(const Variable& other) : variablename(other.variablename), coefficient(other.coefficient)
{
}

Variable Variable::operator+(const Variable& other) const
{
    if (variablename != other.variablename) {
        cout << "Couldn't be performed(" << variablename << "!=" << other.variablename << ")" << endl;

    }
    return Variable(coefficient + other.coefficient, variablename);
}

Variable Variable::operator-(const Variable& other) const
{
    if (variablename != other.variablename) {
        cout << "Couldn't be performed(" << variablename << "!=" << other.variablename << ")" << endl;

    }
    return Variable(coefficient - other.coefficient, variablename);
}

Variable Variable::operator*(const Variable& other) const
{
    string newName = variablename + other.variablename;
    double newCoeff = coefficient * other.coefficient;
    Variable result(newCoeff, newName);
    return result;
}

Variable Variable::operator*(double c) const
{
    return Variable(coefficient * c, variablename);
}

Variable& Variable::operator+=(const Variable& other)
{
    if (variablename != other.variablename) {
        cout << "Couldn't be performed" << endl;
        return *this;
    }
    else
    {
        coefficient += other.coefficient;
    }
    return *this;
}

Variable& Variable::operator-=(const Variable& other)
{
    if (variablename != other.variablename) {
        cout << "Couldn't be performed(" << variablename << "!=" << other.variablename << ")" << endl;
        return *this;
    }
    coefficient -= other.coefficient;
    return *this;
}

Variable& Variable::operator*=(const Variable& other)
{

    coefficient *= other.coefficient;
    variablename += other.variablename;
    return *this;

    return *this;
}

bool Variable::operator==(const Variable& other) const
{
    return (variablename == other.variablename && coefficient == other.coefficient);
}

Variable& Variable::operator=(const Variable& other)
{
    if (this != &other) {
        // Check if other.name is not empty
        if (!other.variablename.empty()) {
            variablename = other.variablename;
        }
        coefficient = other.coefficient;
    }
    return *this;
}




double Variable::operator()(const char* vars, const double* values) const
{
    double result = coefficient;
    size_t varsLen = strlen(vars);
    for (size_t i = 0; i < variablename.size(); i++) {
        char var = variablename[i];
        bool found = false;
        for (size_t j = 0; j < varsLen; j++) {
            if (vars[j] == var) {
                result *= values[j];
                found = true;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return result;
}

string Variable::getname()const
{
    return variablename;
}

double Variable::getcoefficient()const
{
    return coefficient;
}


ostream& operator<<(ostream& os, const Variable& var)
{
    os << var.coefficient;
    if (!var.variablename.empty()) {
        os << var.variablename;
    }
    return os;
}

int Variable::getExponent() const {
    int exponent = 1;
    for (size_t i = 1; i < variablename.length(); i++) {
        if (variablename[i] == variablename[0]) {
            exponent++;
        }
        else {
            break;
        }
    }
    return exponent;
}