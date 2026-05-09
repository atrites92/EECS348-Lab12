#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <limits>
#include "extractNumeric.h"

bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool isPossibleNumberStart(char c) {
    return isDigit(c) || c == '+' || c == '-' || c == '.';
}

bool laterNumericIntentExists(const std::string& str, int startIndex) {
    for (int i = startIndex; i < static_cast<int>(str.length()); i++) {
        if (isDigit(str[i]) || str[i] == '.') {
            return true;
        }

        if ((str[i] == '+' || str[i] == '-') &&
            i + 1 < static_cast<int>(str.length()) &&
            (isDigit(str[i + 1]) || str[i + 1] == '.')) {
            return true;
        }
    }

    return false;
}

double powerOfTen(int exponent, bool& inRange) {
    inRange = true;

    if (exponent > 308) {
        inRange = false;
        return 0.0;
    }

    if (exponent < -308) {
        return 0.0;
    }

    double result = 1.0;
    int count = std::abs(exponent);

    for (int i = 0; i < count; i++) {
        result *= 10.0;
    }

    if (exponent < 0) {
        result = 1.0 / result;
    }

    return result;
}

bool parseFromIndex(const std::string& str, int start, int& end, double& value) {
    int i = start;
    int n = static_cast<int>(str.length());

    int sign = 1;

    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            sign = -1;
        }
        i++;
    }

    double integerPart = 0.0;
    int digitsBeforeDecimal = 0;
    bool hasDigitsBeforeDecimal = false;

    while (i < n && isDigit(str[i])) {
        hasDigitsBeforeDecimal = true;
        digitsBeforeDecimal++;

        if (digitsBeforeDecimal > 18) {
            return false;
        }

        integerPart = integerPart * 10.0 + (str[i] - '0');
        i++;
    }

    double fractionalPart = 0.0;
    double divisor = 10.0;
    bool hasDigitsAfterDecimal = false;

    if (i < n && str[i] == '.') {
        i++;

        while (i < n && isDigit(str[i])) {
            hasDigitsAfterDecimal = true;
            fractionalPart += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    if (!hasDigitsBeforeDecimal && !hasDigitsAfterDecimal) {
        return false;
    }

    double base = integerPart + fractionalPart;

    int exponent = 0;
    int exponentSign = 1;
    bool hasExponent = false;

    if (i < n && (str[i] == 'e' || str[i] == 'E')) {
        hasExponent = true;
        i++;

        if (i < n && (str[i] == '+' || str[i] == '-')) {
            if (str[i] == '-') {
                exponentSign = -1;
            }
            i++;
        }

        bool hasExponentDigits = false;

        while (i < n && isDigit(str[i])) {
            hasExponentDigits = true;
            exponent = exponent * 10 + (str[i] - '0');

            if (exponent > 999) {
                return false;
            }

            i++;
        }

        if (!hasExponentDigits) {
            return false;
        }
    }

    bool inRange = true;
    double result = sign * base;

    if (hasExponent) {
        double multiplier = powerOfTen(exponentSign * exponent, inRange);

        if (!inRange) {
            return false;
        }

        result *= multiplier;
    }

    if (!std::isfinite(result)) {
        return false;
    }

    end = i;
    value = result;
    return true;
}

double extractNumeric(const std::string& str) {
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        if (!isPossibleNumberStart(str[i])) {
            continue;
        }

        int end = i;
        double value = 0.0;

        bool success = parseFromIndex(str, i, end, value);

        if (success) {
            if (laterNumericIntentExists(str, end)) {
                return INVALID_VALUE;
            }

            return value;
        }
    }

    return INVALID_VALUE;
}

int main() {
    std::string input;

    while (true) {
        std::cout << "Enter a string (or 'END' to quit): ";
        std::getline(std::cin, input);

        if (input == "END") {
            std::cout << "Program terminated." << std::endl;
            break;
        }

        double result = extractNumeric(input);

        if (result == INVALID_VALUE) {
            std::cout << "Invalid input: no valid floating-point number found" << std::endl;
        } else {
            std::cout << "Extracted number: "
                      << std::fixed << std::setprecision(4)
                      << result << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
