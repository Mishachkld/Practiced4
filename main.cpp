#include <iostream>
#include <algorithm>
#include <valarray>

#define SIZE 6

void outputArray(std::vector<char> array);

std::vector<char> to2(int number) {   // перевод в 2-ную
    std::vector<char> bitNumber;
    if (number == 0) {
        bitNumber.resize(6, 0);
    } else {
        while (number > 0) {
            bitNumber.push_back((char) (number % 2));
            number /= 2;
        }
    }
    while (bitNumber.size() < SIZE)
        bitNumber.push_back(0);
    return bitNumber;
}

int to10(std::vector<char> number) {   // перевод из 2-ной в 10ую с.ч.
    int tenNumber = 0;
    for (int i = 0; i < 6; i++) {
        tenNumber += ((int) number[i]) * pow(2, i);
    }
    return tenNumber;
}

void writeNum(unsigned __int16 &numbers, std::vector<char> bitNumber,
              int index) {   /// index  - индекс число которое нужно достать(1-ое или 2-ое)
    for (int i = 0; i < 6; i++)
        if ((int) bitNumber[i] == 1)
            numbers |= (1 << (6 * index + i));
        else
            numbers &= ~(1 << (6 * index + i));
}

int readNum(unsigned __int16 &numbers, int index) {
    std::vector<char> bitNimbers;
    for (int i = 0; i < 6; i++)
        if (numbers & (1 << (6 * index + i)))
            bitNimbers.push_back(1);
        else
            bitNimbers.push_back(0);
    int result = to10(bitNimbers);
    return result;
}

int main() {  // макс размер памяти занимаемый числом равен 6 битами. Тогда нам потребуется 2 байта для хранения 2 чисел, т.е. 2 числа занимают 12 бит
    int number;
    unsigned __int16 saveNumbers;

    for (int i = 0; i < 2; i++) {
        std::cin >> number;   // вводиться 2 числа
        writeNum(saveNumbers, to2(number), i);
    }
    for (int i = 0; i < 2; i++) {
        std::cout << readNum(saveNumbers, i) << std::endl; // выводитсья 2 числа в том порядке, в котором были записаны
    }

    return 0;
}

void outputArray(std::vector<char> array) {
    int len = array.size();
    for (int i = 0; i < len; i++) {
        std::cout << (int) array[i];
    }
    std::cout << std::endl;
}


