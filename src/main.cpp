#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <limits>
#include "extractNumeric.h"

bool isNumberChar(char c) {
    return std::isdigit(c) || c == '+' || c == '-' || c == '.' || c == 'e' || c == 'E';
}

double powerOfTen(int exponent) {
    double result = 1.0;

    if (exponent > 308 || exponent < -308) {
        return std::numeric_limits<double>::infinity();
    }

    for (int i = 0; i < std::abs(exponent); i++) {
        result *= 10.0;
    }

    return exponent >= 0 ? result : 1.0 / result;
}

double parseCandidate(const std::string& s, bool& valid) {
    valid = false;

    int i = 0;
    int n = s.length();

    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        if (s[i] == '-') {
            sign = -1;
        }
        i++;
    }

    double integerPart = 0.0;
    bool hasDigitsBeforeDecimal = false;

    while (i < n && std::isdigit(s[i])) {
        hasDigitsBeforeDecimal = true;
        integerPart = integerPart * 10 + (s[i] - '0');

        if (integerPart > std::numeric_limits<double>::max() / 10.0) {
            return INVALID_VALUE;
        }

        i++;
    }

    double fractionPart = 0.0;
    double divisor = 10.0;
    bool hasDigitsAfterDecimal = false;

    if (i < n && s[i] == '.') {
        i++;

        while (i < n && std::isdigit(s[i])) {
            hasDigitsAfterDecimal = true;
            fractionPart += (s[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    if (!hasDigitsBeforeDecimal && !hasDigitsAfterDecimal) {
        return INVALID_VALUE;
    }

    double base = integerPart + fractionPart;

    int exponent = 0;
    int exponentSign = 1;
    bool hasExponent = false;

    if (i < n && (s[i] == 'e' || s[i] == 'E')) {
        hasExponent = true;
        i++;

        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') {
                exponentSign = -1;
            }
            i++;
        }

        bool hasExponentDigits = false;

        while (i < n && std::isdigit(s[i])) {
            hasExponentDigits = true;
            exponent = exponent * 10 + (s[i] - '0');

            if (exponent > 999) {
                return INVALID_VALUE;
            }

            i++;
        }

        if (!hasExponentDigits) {
            return INVALID_VALUE;
        }
    }

    if (i != n) {
        return INVALID_VALUE;
    }

    double result = sign * base;

    if (hasExponent) {
        double multiplier = powerOfTen(exponentSign * exponent);

        if (!std::isfinite(multiplier)) {
            return INVALID_VALUE;
        }

        result *= multiplier;
    }

    if (!std::isfinite(result)) {
        return INVALID_VALUE;
    }

    valid = true;
    return result;
}

double extractNumeric(const std::string& str) {
    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        if (std::isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '.') {
            int start = i;

            if ((str[i] == '+' || str[i] == '-') &&
                i + 1 < static_cast<int>(str.length()) &&
                (str[i + 1] == '+' || str[i + 1] == '-')) {
                continue;
            }

            int end = start;

            while (end < static_cast<int>(str.length()) && isNumberChar(str[end])) {
                end++;
            }

            std::string candidate = str.substr(start, end - start);

            bool valid = false;
            double value = parseCandidate(candidate, valid);

            if (valid) {
                return value;
            }

            bool containsDigit = false;
            for (char c : candidate) {
                if (std::isdigit(c)) {
                    containsDigit = true;
                }
            }

            if (containsDigit) {
                return INVALID_VALUE;
            }
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
