#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Five {
public:
    Five();
    Five(const size_t &n, unsigned char t = 0);
    Five(const std::initializer_list<unsigned char> &t);
    Five(const std::string &number);
    Five(const Five &other);
    Five(Five &&other) noexcept;
    virtual ~Five() noexcept;

    Five &operator=(const Five &other);
    Five &operator=(Five &&other) noexcept;

    Five operator+(const Five &other) const;
    Five operator-(const Five &other) const;

    bool operator<(const Five &other) const;
    bool operator>(const Five &other) const;
    bool operator==(const Five &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Five &five);

    std::string toString() const;  // public for tests

private:
    unsigned char *digits;
    size_t size;

    void fromString(const std::string &number);
    int toDecimal() const;
    static Five fromDecimal(int decimal);
};

