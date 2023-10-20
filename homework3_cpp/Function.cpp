#include "Function.h"

Function::Function()
{
    functionVar = nullptr;
    functionSize = 0;
}

Function::Function(const Function& other)
{
    functionVar = new Variable[functionSize];
    for (int i = 0; i < functionSize; i++) {
        functionVar[i] = other.functionVar[i];
    }

}

Function::~Function()
{
    delete[] functionVar;
}


Function& Function::operator+=(const Variable& var)
{
    Variable* var12 = new Variable[functionSize + 1];

    for (int i = 0; i < functionSize; i++) {
        var12[i] = functionVar[i];
    }
    var12[functionSize] = var;
    delete[] functionVar;
    functionVar = var12;

    functionSize++;

    return  *this;
}


Function& Function::operator-=(const int index)
{
    if (index >= 0 && index < functionSize) {
        char* newVar = new char[functionSize - 1];
        std::memcpy(newVar, functionVar, index * sizeof(char));
        std::memcpy(newVar + index, functionVar + index + 1, (functionSize - index - 1) * sizeof(char));
        --functionSize;
        delete[] functionVar;
        functionVar->getname() = newVar;
    }
    else {
        std::cout << "Index out of bounds." << std::endl;
    }
    return *this;
}

Function Function::operator+(const Function& other) const
{
    Function result(*this);
    for (int i = 0; i < other.functionSize; ++i) {
        bool found = false;
        for (int j = 0; j < result.functionSize; ++j) {
            if (other.functionVar[i] == result.functionVar[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            result += other.functionVar[i];
        }
    }

    return result;
}

Function Function::operator-(const Function& other) const
{
    Function result(*this);
    for (int i = 0; i < other.functionSize; ++i) {
        for (int j = 0; j < result.functionSize; ++j) {
            if (other.functionVar[i] == result.functionVar[j]) {
                result -= j;
                break;
            }
        }
    }
    return result;
}

Function Function::operator*(const Function& other) const
{
    Function result;
    for (int i = 0; i < functionSize; ++i) {
        bool found = false;
        for (int j = 0; j < other.functionSize; ++j) {
            if (functionVar[i] == other.functionVar[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            result += functionVar[i];
        }
    }

    return result;
}

Function Function::operator*(const double factor) const
{
    Function result(*this);
    for (int i = 0; i < result.functionSize; ++i) {
        result.functionVar[i] *= factor;
    }
    return result;
}


Function& Function::operator=(const Function& other)
{
    if (this == &other) {
        return *this;
    }

    if (functionSize != other.functionSize) {
        delete[] functionVar;
        functionSize = other.functionSize;
        functionVar = new Variable[functionSize];
    }

    for (int i = 0; i < functionSize; i++) {
        functionVar[i] = other.functionVar[i];
    }

    return *this;
}



bool Function::operator==(const Function& other) const
{
    if (functionSize != other.functionSize) {
        return false;
    }
    else
    {
        return true;
    }
}

Variable Function::operator[](size_t index) const
{
    if (index >= functionSize) {
        std::cerr << "Index out of bounds!" << std::endl;
        return Variable();
    }
    return functionVar[index];
}



ostream& operator<<(ostream& os, const Function& f)
{
    if (f.functionSize == 0) {
        os << "f(x) = 0";
    }
    else {

        for (int i = 0; i < f.functionSize; i++) {
            os << f.functionVar[i];
            if (i != f.functionSize - 1) {
                os << " + ";
            }
        }
    }
    return os;
}


Variable Function::getvariable(int i)const {
    if (i < 0 || i >= functionSize) {
        cout<<("Invalid variable index")<<endl;
    }
    return functionVar[i];
}

int Function::getsize()const
{
    return functionSize;
}