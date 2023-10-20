#include "LinearEquation.h"

LinearEquation::LinearEquation(const Function& function) {
    // Check if all variables are singular and exponentiated by 1
    for (int i = 0; i < function.getsize(); i++) {
        if (function.getvariable(i).getExponent() != 1) {
            cout << "Error: Function cannot be converted to a linear equation." << endl;
            exit(1);
        }
    }

    // Check if there is a free number in the function
    bool freeNumFound = false;
    for (int i = 0; i < function.getsize(); i++) {
        if (function.getvariable(i).getname() == "") {
            freeNumFound = true;
            m_freeNum = function.getvariable(i).getcoefficient();
            break;
        }
    }

    // Move free number to the right side of the equation
    if (freeNumFound) {
        m_func = Function();
        for (int i = 0; i < function.getsize(); i++) {
            if (function.getvariable(i).getname() != "") {
                m_func += function.getvariable(i);
            }
        }
        m_func -= m_freeNum;
    }
    else {
        m_func = function;
        m_freeNum = 0;
    }
}


LinearEquation operator+(const LinearEquation& lhs, const LinearEquation& rhs) {
    // Check that both equations have the same number of variables
    if (lhs.m_func.getsize() != rhs.m_func.getsize()) {
        cout << "Equations have different numbers of variables" << endl;
        exit(1);
    }

    // Create a new equation to hold the sum
    LinearEquation sum(lhs.m_func);

    // Add each variable from the rhs equation to the sum equation
    for (int i = 0; i < rhs.m_func.getsize(); i++) {
        sum.m_func += rhs.m_func.getvariable(i);
    }

    // Add the free numbers from both equations
    sum.m_freeNum = lhs.m_freeNum + rhs.m_freeNum;

    return sum;
}

LinearEquation operator-(const LinearEquation& lhs, const LinearEquation& rhs) {
    // Check that both equations have the same number of variables
    if (lhs.m_func.getsize() != rhs.m_func.getsize()) {
        cout << "Equations have different numbers of variables" << endl;
        exit(1);
    }

    // Create a new equation to hold the difference
    LinearEquation diff(lhs.m_func);

    // Subtract each variable from the rhs equation from the diff equation
    for (int i = 0; i < rhs.m_func.getsize(); i++) {
        diff.m_func += Variable(-1 * rhs.m_func.getvariable(i).getcoefficient(), rhs.m_func.getvariable(i).getname());

    }

    // Subtract the free number from the rhs equation from the lhs equation
    diff.m_freeNum = lhs.m_freeNum - rhs.m_freeNum;

    return diff;
}

std::ostream& operator<<(std::ostream& os, const LinearEquation& equation)
{
    // Output variables with their coefficients
    for (int i = 0; i < equation.m_func.getsize(); i++) {
        const Variable& var = equation.m_func.getvariable(i);
        if (var.getname() != "") {
            os << var.getcoefficient() << var.getname();
            if (i != equation.m_func.getsize() - 1) {
                os << "+";
            }
        }
    }

    // Output the free number
    if (equation.m_freeNum > 0) {
        os << "+" << equation.m_freeNum;
    }
    else if (equation.m_freeNum < 0) {
        os << equation.m_freeNum;
    }
    os << "=0";
    return os;
}



int LinearEquation::getNumVariables() const {
    int count = 0;
    for (int i = 0; i < m_func.getsize(); i++) {
        const Variable& var = m_func.getvariable(i);
        if (!var.getname().empty()) {
            count++;
        }
    }
    return count;
}

double LinearEquation::getConstant()
{
    return m_freeNum;
}


bool PossibleSingleSolution(LinearEquation eqs[], int size) {
    int numEquations = size;
    int numVariables = eqs[0].getNumVariables();  // Assuming all equations have the same number of variables

    if (numVariables > numEquations) {
        return false;  // More variables than equations, no chance for a single solution
    }

    // Create a matrix to store the coefficients of the variables in the equations
    double coefficients[10][10];
    for (int i = 0; i < numEquations; i++) {
        for (int j = 0; j < numVariables; j++) {
            coefficients[i][j] = eqs[i].getNumVariables();
        }
    }

    // Perform Gaussian elimination to determine if there is a chance for a single solution
    for (int i = 0; i < numEquations; i++) {
        for (int j = i + 1; j < numEquations; j++) {
            double ratio = coefficients[j][i] / coefficients[i][i];
            for (int k = 0; k < numVariables; k++) {
                coefficients[j][k] -= ratio * coefficients[i][k];
            }
        }
    }

    // Check for inconsistencies or contradictions in the reduced row echelon form
    for (int i = 0; i < numEquations; i++) {
        bool allZero = true;
        for (int j = 0; j < numVariables; j++) {
            if (coefficients[i][j] != 0) {
                allZero = false;
                break;
            }
        }
        if (allZero) {
            return false;  // Inconsistent equations, no solution
        }
    }

    // There is a chance for a single solution
    return true;
}
