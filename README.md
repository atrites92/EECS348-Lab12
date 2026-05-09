# EECS348-Lab12
Lab 12 - Use AI to generate code

Used ChatGPT Instant on 5/9/2026

First prompt given:

Can you complete this assignment for me? Give me a header file, a .cpp file, and a make file for me to add to a github.

Lab #12: Extracting double-precision numbers from strings (optional)

Objective: Develop proficiency in C/C++ string parsing and numerical validation. The program reads a string and extracts a valid floating-point number embedded within it, supporting scientific notation and handling arbitrary random (garbage) characters.

Motivation (real‑world use cases)

Problems like this arise in practice when numerical data must be extracted from noisy, unstructured text, such as logs produced by sensors, embedded systems, or low‑level controllers. These systems often embed a single meaningful numeric value inside a stream of status messages, labels, units, transmission noise, or corrupted characters. Because the input format cannot be trusted and standard conversion libraries may be unavailable or unsafe, the software must scan the text carefully, ignore irrelevant characters, strictly validate numeric patterns, and reject malformed or out‑of‑range values instead of guessing. This assignment models that situation.

In addition to dealing with random surrounding characters, real‑world data often contains numeric‑looking values that are themselves incorrect. These errors frequently arise from manual data entry or transmission faults, producing strings such as 12.34.56, 123e, or 12E+ that resemble numbers but are not mathematically well‑formed. Defensive and robust programming must never assume such input are formed correctly. Instead, it must carefully validate the number and explicitly reject malformed input to avoid incorrect results, undefined behavior, or system crashes. 

From a secure programming perspective, unvalidated numeric input is also a common source of input‑injection vulnerabilities. Attackers (or faulty upstream components) may deliberately craft strings that exploit weak parsing logic, such as malformed exponents, ambiguous digit sequences, or partial numeric tokens, to trigger undefined behavior, incorrect calculations, or control‑flow errors. Defensive software must therefore treat all input as untrusted, strictly validate numeric structure, and reject malformed values rather than attempting to interpret or “fix” them. This assignment models that defensive mindset by requiring careful validation of numeric patterns before any computation is performed.

What to turn in: A URL to your GitHub repository. Make sure the repository is public, otherwise the TAs won't be able to grade it.

Problem description

Write a C or C++ program that reads a string from the user and extracts a valid floating-point number embedded within it. Each input string contains at most one valid number. If characters matching a numeric pattern are encountered, the entire contiguous sequence must form a valid number. Partial matches are not accepted. The string may contain any mixture of letters, symbols, digits, and whitespace around that number. You cannot use library functions like std::stod, atof, or strtod.

Parsing rule for random (garbage) characters

The parser scans left to right, ignoring any characters that do not belong to a valid number pattern. Once a valid number starts, the parser extracts the complete number.  If multiple sign characters appear consecutively, only the first sign immediately preceding a digit or decimal point is considered part of the number; preceding signs are treated as garbage.

Valid number formats. The extracted number should match one of these patterns:

Integer digits only: 123, -456, +789 (these become double values like 123.0, -456.0, 789.0)

Decimal with a decimal point: 3.14, -0.5, 2.0, +.75 (a decimal point is valid if it has at least one digit either before or after it)

Scientific notation: 1.23e-4, -5.6E+2, 1e3, +.5E-1, -2.E+5

Integers are simply doubles without a fractional part. All valid patterns produce a double value. Assume that the valid inputs will never produce the value -999999.99.

Rules for scientific notation

    The base can be integer or decimal (with or without leading or trailing digits before or after decimal point)
    The exponent must be an integer (no decimal point in exponent)
    The exponent may be signed with + or -
    Valid exponent examples: e10, e-5, E+3, e0
    The extracted numeric value is calculated as base × 10^exponent

Invalid number patterns. The following are NOT valid numbers and should cause the function to return -999999.99:

    Multiple decimal points: 12.34.56
    Missing exponent value: 123e, 12E+
    Sign after digits: 123+45
    Letters inside number: 12a3.45 (The 'a' terminates the sequence '12', but the presence of subsequent numeric characters '3.45' makes the entire string's numeric intent ambiguous, rendering it invalid.)
    Scientific notation with decimal exponent: 1.2e3.4
    Two operators in exponent: 1.2e-+3
    Decimal point with no digits before or after: -.
    Sign alone with no following digits: -
    No digits at all: abc, +++, ...

Input

A single line of text up to 200 characters. The string may contain anything. Each input contains at most one valid floating-point number.

Valid extraction examples
Input string 	Extracted number as double 	Notes
abc123.45def 	123.45 	Random (garbage) before and after
temp: -98.6F 	-98.6 	Negative decimal
value=+1.23e-4v 	0.000123 	Scientific notation with positive sign and negative exponent
--A2.5--- 	2.5 	Random (garbage) characters before number
xyz1e2abc 	100.0 	Scientific notation without decimal
result: -2.E+3end 	-2000.0 	Scientific notation with decimal point and no fractional digits
hello +.75world 	0.75 	Decimal starting with decimal point and plus sign
+-12.34 	-12.34 	Skip garbage +, then extract -12.34
no number here 	(invalid) 	No numeric pattern found

Output requirements

If a valid number is successfully extracted:

Extracted number: ########.####

Where ########.#### is the number formatted to four decimal places using fixed-point notation. Use std::fixed and std::setprecision(4) in C++ or printf("%.4f") in C. Note that the displayed value is rounded to four decimal places. For example, if the extracted double is 0.000123, the output will be 0.0001 due to rounding. 

If no valid number is found:

Invalid input: no valid floating-point number found

Program requirements

Input loop: The main function continuously prompts the user for input until the user enters END (case-sensitive)

Extraction function: Create a function with this prototype in C

double extractNumeric(const char* str);

or in C++

double extractNumeric(const std::string& str);

The extractNumeric function:

    Scans the string left to right

    Ignores random (garbage) characters that are not part of a valid number pattern

    Extracts a valid floating-point number according to the rules above

    If successful, returns the number as a double

    If no valid number is found, returns -999999.99

Parsing constraints

    You may not use any library function that converts strings to numbers
    You must implement the parsing logic yourself using character‑by‑character processing
    You may use standard string functions like isdigit, isalpha, etc. for character classification

Display output: When main receives the returned value from extractNumeric, it displays the output as specified above.

Range handling

    Valid double values range from approximately -1.7e308 to 1.7e308
    If the extracted number would exceed the range of a double, return -999999.99
    Very large exponents like 1e999 should be treated as out of range

Sample run

Enter a string (or 'END' to quit): abc123.45def
Extracted number: 123.4500

Enter a string (or 'END' to quit): value=+1.23e-4v
Extracted number: 0.0001

Enter a string (or 'END' to quit): result: -2.E+3end
Extracted number: -2000.0000

Enter a string (or 'END' to quit): temp -98.6F
Extracted number: -98.6000

Enter a string (or 'END' to quit): +-12.34
Extracted number: -12.3400

Enter a string (or 'END' to quit): --A2.5---
Extracted number: 2.5000

Enter a string (or 'END' to quit): 12.34.56
Invalid input: no valid floating-point number found

Enter a string (or 'END' to quit): 1e+
Invalid input: no valid floating-point number found

Enter a string (or 'END' to quit): hello world
Invalid input: no valid floating-point number found

Enter a string (or 'END' to quit): 99999999999999999999
Invalid input: no valid floating-point number found

Enter a string (or 'END' to quit): END
Program terminated.

--------------------------------------------------------------------------------------------
After testing the output, the program failed the following sample runs:
| Test Case | Your Output | Expected Output |
| :---: | :---: | :---: |
| result: -2.E+3end | Invalid input: no valid floating-point number found | -2000.0000 |
| --A2.5--- | Invalid input: no valid floating-point number found | 2.5000 |
| 99999999999999999999 | 100000000000000016384.0000 | Invalid input: no valid floating-point number found |

The same AI dialog was given the following prompt on 5/9/2026:

You're program failed the following cases according to the given sample runs: 

| Test Case | Your Output | Expected Output |
|result: -2.E+3end | Invalid input: no valid floating-point number found | -2000.0000 |
| --A2.5--- | Invalid input: no valid floating-point number found | 2.5000 |
| 99999999999999999999 | 100000000000000016384.0000 | Invalid input: no valid floating-point number found | 

Please fix these issues.
--------------------------------------------------------------------------------------------
After testing the output, the program failed the following sample run:
| Test Case | Your Output | Expected Output |
| :---: | :---: | :---: |
| 99999999999999999999 | 100000000000000016384.0000 | Invalid input: no valid floating-point number found |

The same AI dialog was given the following prompt on 5/9/2026"

The code you gave passed two of the three tests. However it is still failing with an input of 99999999999999999999 and outputting a number when it shouldn't be. Please fix the final issue.
--------------------------------------------------------------------------------------------
