#include <iostream>
#include "Number.h"


Number::Number() {
    length = DEFAULT_LENGTH;
    digits = new int[length];
    isNegative = false;
}

Number::Number(int number){
    setNumber(number);
}

Number::Number(int* digits, int length) {
    this->digits = digits;
    this->length = length;
    this->isNegative = false;
}

Number::Number(int* digits, int length, bool isNegative){
    this->digits = digits;
    this->length = length;
    this->isNegative = isNegative;
}

Number::Number(const Number& otherNumber){
    copyNumber(otherNumber);
}

Number::~Number() {
    delete digits;
}

void Number::operator=(const int value) {
    delete digits;
    setNumber(value);
}

void Number::operator=(const Number& otherNumber){
    delete digits;
    copyNumber(otherNumber);
}

Number Number::operator+(const Number& otherNumber) {
    // TODO implement negative number support
    int maxLength = std::max(length, otherNumber.length) + 1;
    int* values = new int[maxLength];
    values[maxLength - 1] = 0;

    int carry = 0;
    for (int i = 0; i < maxLength; i++) {
        int sum = carry;
        if (i < length)
            sum += digits[i];
        if (i < otherNumber.length)
            sum += otherNumber.digits[i];

        carry = (sum >= 10);
        values[i] = (sum % 10);
    }
    maxLength = removeRedundant(&values, maxLength);
    return {values, maxLength, false};
}

Number Number::operator-(const Number& otherNumber){
    int maxLength = std::max(length, otherNumber.length);
    int* values = new int[maxLength];

    int borrow = 0;
    for (int i = 0; i < maxLength; i++) {
        int diff = borrow;
        if (i < length)
            diff += digits[i];
        if (i < otherNumber.length)
            diff -= otherNumber.digits[i];

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        values[i] = diff;
    }
//    std::cout << values[0] << std::endl;
    maxLength = removeRedundant(&values, maxLength);
    return {values, maxLength};
}

Number Number::operator*(const Number& otherNumber){
    int maxLength = length + otherNumber.length;
    int* result = new int[maxLength];
    for (int i = 0; i < maxLength; i++)
        result[i] = 0;

    int shift = 0;

    int p = 0;
    int q;

    for (int i = 0; i < length; i++) {
        int carry = 0;
        q = 0;
        for (int j = 0; j < otherNumber.length; j++) {
            int mul = digits[i] * otherNumber.digits[i] + result[p + q] + carry;
            carry = mul / 10;
            result[p + q] = mul % 10;
            q++;
        }

        if (carry > 0)
            result[p + q] += carry;
        p++;
    }
    return Number(result, maxLength, !(isNegative == otherNumber.isNegative));
}

Number Number::operator/(const Number& otherNumber){
    int* result = new int[length];
    for (int i = 0; i < length; i++)
        result[i] = 0;

    int idx = 0;
    int temp = digits[idx];
    int divisor = 0;
    for (int i = 0; i < otherNumber.length; i++)
        divisor += i * 10 + otherNumber.digits[i];

    while (temp < divisor)
        temp = temp * 10 + digits[++idx];

    int sum = 0;
    while (length > idx) {
        sum += temp / divisor;
        temp = (temp % divisor) * 10 + digits[++idx];
    }

    for (int i = 0; sum > 0; i++){
        result[i] = sum % 10;
        sum /= 10;
    }

    return Number(result, length, !(isNegative == otherNumber.isNegative));
}

void Number::setNumber(int number){
    isNegative = number < 0;

    // TODO implement negative implementation

    length = calculateLength(number);
    digits = new int[length];

    for (int i = 0; i < length; i++) {
        digits[i] = number % 10;
        number /= 10;
    }
}

void Number::copyNumber(const Number& otherNumber){
    length = otherNumber.length;
    isNegative = otherNumber.isNegative;
    digits = new int[length];
    for (int i = 0; i < length; i++)
        digits[i] = otherNumber.digits[i];
}

int Number::calculateLength(int number){
    int size = 0;
    while (number != 0) {
        number /= 10;
        size++;
    }
    return size;
}

int Number::removeRedundant(int** valuesPointer, int maxLength) {
    int* values = *valuesPointer;
    if (values[maxLength - 1] != 0)
        return maxLength;

    int curLength = maxLength;
    int* curValues;
    for (int i = maxLength - 1; i >= 0; i--) {
        if (values[i] != 0 || i == 0) {
            if (curValues == nullptr)
                curValues = new int[curLength];
            curValues[i] = values[i];
        } else curLength--;
    }

    delete values;
    *valuesPointer = curValues;
    return curLength > 0 ? curLength : 1;
}

std::string Number::toString(){
    std::string outputString;
    outputString = isNegative ? '-' : '+';

    for (int i = length - 1; i >= 0; i--)
        outputString += char(digits[i] + 48);

    return outputString;
}

void Number::print(){
    std::cout << toString() << std::endl;
}