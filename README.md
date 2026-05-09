# EECS348-Lab12

## Lab 12 - Use AI to Generate Code

**AI tool used:** ChatGPT Instant  
**Date used:** May 9, 2026

---

## Assignment Overview

The goal of this lab was to test how well AI could generate working code for a C/C++ programming assignment. The assignment required a program that extracts a valid double-precision floating-point number from a string containing random or garbage characters.

The final program needed to include:

- A header file
- A `.cpp` source file
- A Makefile
- A working input loop
- A custom numeric parser
- No use of conversion functions such as `std::stod`, `atof`, or `strtod`

---

## Original Prompt Given to AI

Can you create for me? Give me a header file, a .cpp file, and a make file for me to add to a github. </br>
-- (Copy and pasted entire assignment from Canvas page into the prompt) --

---

## First Testing Results

After testing the output, the AI-generated program failed the following sample runs:

| Test Case | AI Output | Expected Output |
| :--- | :--- | :--- |
| `result: -2.E+3end` | `Invalid input: no valid floating-point number found` | `-2000.0000` |
| `--A2.5---` | `Invalid input: no valid floating-point number found` | `2.5000` |
| `99999999999999999999` | `100000000000000016384.0000` | `Invalid input: no valid floating-point number found` |

---

## Second Prompt Given to AI

```text
You're program failed the following cases according to the given sample runs:

| Test Case | Your Output | Expected Output |
|result: -2.E+3end | Invalid input: no valid floating-point number found | -2000.0000 |
| --A2.5--- | Invalid input: no valid floating-point number found | 2.5000 |
| 99999999999999999999 | 100000000000000016384.0000 | Invalid input: no valid floating-point number found |

Please fix these issues.
```

---

## Second Testing Results

After testing the updated output, the program passed two of the three previously failing cases.

It still failed the following sample run:

| Test Case | AI Output | Expected Output |
| :--- | :--- | :--- |
| `99999999999999999999` | `100000000000000016384.0000` | `Invalid input: no valid floating-point number found` |

---

## Third Prompt Given to AI

```text
The code you gave passed two of the three tests. However it is still failing with an input of 99999999999999999999 and outputting a number when it shouldn't be. Please fix the final issue.
```

---

## Final Result

The final code given by the AI passed all sample test cases.

---

## Summary

This assignment tested how well AI could generate working code from a description.

The AI generated a mostly correct solution on the first attempt, but the initial code failed several important edge cases. After two rounds of specific feedback using failed test cases, the final version passed all provided sample tests.

Overall, the AI successfully produced working assignment code within three prompts.
