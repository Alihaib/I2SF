#include <iostream>
#include "LinearEquation.h"

using namespace std;


int main() {
    Variable v[][3] = {
        {Variable(4.5, ""), Variable(7.2, "x"), Variable(1, "y")},
        {Variable(2.5, "x"), Variable(3.2, "y"), Variable(4, "z")},
        {Variable(2.1, ""), Variable(3.6, "y"), Variable(5.5, "z")}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "the variable is: " << v[i][j] << endl;
        }
    }

    Function f[3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            f[i] += v[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        cout << "f" << i + 1 << ": " << f[i] << endl;
    }

    LinearEquation eq[] = { LinearEquation(f[0]), LinearEquation(f[1]), LinearEquation(f[2]) };
    for (int i = 0; i < 3; i++) {
        cout << "eq" << i + 1 << ": " << eq[i] << endl;
    }

    // Call the PossibleSingleSolution function and capture the result
    bool hasSingleSolution = PossibleSingleSolution(eq, 1);

    // Print the result
    cout << "Possible Single Solution: " << boolalpha << hasSingleSolution << endl;

    return 0;
}


