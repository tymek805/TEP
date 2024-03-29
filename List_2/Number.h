#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-unconventional-assign-operator"
#include <string>

#define DEFAULT_LENGTH 10

class Number {
public:
    Number();
    explicit Number(int number);
    Number(int* digits, int length);
    Number(int* digits, int length, bool isNegative);
    Number(const Number& otherNumber);
    ~Number();

    void operator=(int value);
    void operator=(const Number& otherNumber);

    Number operator+(const Number& otherNumber);
    Number operator-(const Number& otherNumber);
    Number operator*(const Number& otherNumber);
    Number operator/(const Number& otherNumber);

    void setIsNegative(bool newIsNegative);
    std::string toString();
    void print();
private:
    int length;
    int* digits;
    bool isNegative;

    Number add(const Number& number, const Number& otherNumber);
    Number subtract(const Number& number, const Number& otherNumber);

    void setNumber(int number);
    void copyNumber(const Number& otherNumber);

    int calculateLength(int number);
    int removeRedundant(int** valuesPointer, int maxLength);
};