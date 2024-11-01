#include "five.h"

// Дефолтный конструктор
Five::Five() : digits(nullptr), size(0) {}

// Конструктор по размеру и значению
Five::Five(const size_t &n, unsigned char val) : size(n) {
    if (val > 4) throw std::invalid_argument("Invalid digit for base 5.");
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = val;  
    }
}

// Конструктор по списку инициализации
Five::Five(const std::initializer_list<unsigned char> &t) : size(t.size()) {
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto &val : t) {
        if (val > 4) throw std::invalid_argument("Invalid digit for base 5.");
        digits[i++] = val;
    }
}

// Конструктор по строке
Five::Five(const std::string &number) : digits(nullptr), size(0) {
    fromString(number);
}

// Конструктор копирования
Five::Five(const Five &other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];  
    }
}

// Конструктор перемещения
Five::Five(Five &&other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

// Деструктор
Five::~Five() noexcept {
    delete[] digits;
}

// Оператор присваивания
Five &Five::operator=(const Five &other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            digits[i] = other.digits[i];  
        }
    }
    return *this;
}

// Оператор присваивания перемещением
Five &Five::operator=(Five &&other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        size = other.size;

        other.digits = nullptr;
        other.size = 0;
    }
    return *this;
}

// Сложения
Five Five::operator+(const Five &other) const {
    int decimal_sum = toDecimal() + other.toDecimal();
    return fromDecimal(decimal_sum);
}

// Вычитания
Five Five::operator-(const Five &other) const {
    int decimal_diff = toDecimal() - other.toDecimal();
    if (decimal_diff < 0) throw std::invalid_argument("Resulting number is negative.");
    return fromDecimal(decimal_diff);
}

// Сравнения
bool Five::operator<(const Five &other) const {
    return toDecimal() < other.toDecimal();
}

bool Five::operator>(const Five &other) const {
    return toDecimal() > other.toDecimal();
}

bool Five::operator==(const Five &other) const {
    return toDecimal() == other.toDecimal();
}

// Вывод в поток
std::ostream &operator<<(std::ostream &out, const Five &five) {
    out << five.toString();
    return out;
}

// Преобразование из строки
void Five::fromString(const std::string &number) {
    size = number.size();
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        if (number[size - 1 - i] < '0' || number[size - 1 - i] > '4') {
            throw std::invalid_argument("Invalid character in the number.");
        }
        digits[i] = number[size - 1 - i] - 48;
    }
}

// Преобразование в строку
std::string Five::toString() const {
    std::string result(size, '0');
    for (size_t i = 0; i < size; ++i) {
        result[size - 1 - i] = digits[i] + 48;
    }
    return result;
}

// Преобразование из 5СС в 10СС
int Five::toDecimal() const {
    int decimal = 0;
    int base = 1;
    for (size_t i = 0; i < size; ++i) {
        decimal += digits[i] * base;
        base *= 5;
    }

    return decimal;
}

// Преобразование из 10СС в 5СС
Five Five::fromDecimal(int decimal) {

    if (decimal == 0) return Five("0");

    std::string result;
    int temp_decimal = decimal;

    int num_digits = 0;
    while (temp_decimal > 0) {
        temp_decimal /= 5;
        ++num_digits;
    }

    result.resize(num_digits); 

    for (int i = num_digits - 1; i >= 0; --i) {
        result[i] = (decimal % 5) + 48;
        decimal /= 5;
    }

    return Five(result);
}
