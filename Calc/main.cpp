//
//  main.cpp
//  tescplusplus
//
//  Created by Роман Путинцев on 21.10.2021.
//

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>

class Calculator {
    
private:
    static bool isMorePriority(char a, char b) {
        std::unordered_map<char, uint8_t> priorities = {
            {'+', 0},
            {'-', 0},
            {'*', 1},
            {'/', 1}
        };
        
        return priorities[a] > priorities[b];
    }
    
    static bool isNumber(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
    
    static double calculate(double a, double b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '/':
                return a / b;
            case '*':
                return  a * b;
        }
        
        return 0;
    }
    
    static double solveReversePolandNotationExpr(const std::string& expr) {
        std::stack<double> operands;
        std::istringstream ss(expr);
        std::string op;
        
        while (ss >> op) {
            if (isNumber(op)) {
                operands.push(std::stod(op));
            } else { // isOperator
                double second = operands.top();
                operands.pop();
                double first = operands.top();
                operands.pop();
                double result = calculate(first, second, op[0]);
                operands.push(result);
            }
        }
        
        double result = operands.top();
        
        return result;
    }
    
    static void exprToReversePolandNotation(const std::string& inputExpr, std::string& outputExpr) {
        std::istringstream ss(inputExpr);
        std::string op;
        std::stack<char> operatorStack;
        char delimiter = ' ';
        
        while (ss >> op) {
            if (isNumber(op)) {
                outputExpr.append(op);
                outputExpr.push_back(delimiter);
            } else { // isOperator or bracket
                
                if (op[0] == '(') {
                    operatorStack.push('(');
                    continue;;
                }
                
                if (op[0] == ')') {
                    while (operatorStack.top() != '(') {
                        outputExpr.push_back(operatorStack.top());
                        outputExpr.push_back(delimiter);
                        operatorStack.pop();
                    }
                    
                    operatorStack.pop();
                    
                    continue;
                }
                
                if (!operatorStack.empty() &&  isMorePriority(operatorStack.top(), op[0])) {
                    outputExpr.push_back(operatorStack.top());
                    outputExpr.push_back(delimiter);
                    operatorStack.pop();
                }
                
                operatorStack.push(op[0]);
                continue;
            }
        }
        
        while (!operatorStack.empty()) {
            outputExpr.push_back(operatorStack.top());
            outputExpr.push_back(delimiter);
            operatorStack.pop();
        }
        
    }
    
public:
    static double solve(const std::string& expr) {
        if (!expr.empty()) {
            std::string polNotation;
            exprToReversePolandNotation(expr, polNotation);
            return solveReversePolandNotationExpr(polNotation);
        } else {
            return 0;
        }
    }
};

int main(int argc, const char * argv[]) {
    
    while(true) {
        std::string expr;
        std::getline(std::cin, expr);

        std::cout << "Ans: " << Calculator::solve(expr) << std::endl;
    }
    return 0;
}
