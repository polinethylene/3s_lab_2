#ifndef LAB_2_COMPLEX_H
#define LAB_2_COMPLEX_H

#include <iostream>
#include <cmath>


class Complex{
public:
    float Re;
    float Im;

    Complex(){
        Re = 0;
        Im = 0;
    }
    Complex(float real, float imaginary){
        Re = real;
        Im = imaginary;
    }

    Complex &operator=(const Complex &num) = default;

    Complex &operator+=(const Complex &num) {
        Re += num.Re;
        Im += num.Im;
        return *this;
    }

    Complex operator+(const Complex &num) const {
        float i, j;
        i = this->Re + num.Re;
        j = this->Im + num.Im;
        return Complex(i, j);
    }

    Complex operator-() const {
        float i, j;
        i = -this->Re;
        j = -this->Im;
        return Complex(i, j);
    }

    Complex operator-(const Complex &num) const {
        float i, j;
        i = this->Re - num.Re;
        j = this->Im - num.Im;
        return Complex(i, j);
    }

    Complex operator*(Complex &num) const {
        float i, j;
        i = Re * num.Re - Im * num.Im;
        j = Re * num.Im + num.Re * Im;
        return Complex(i, j);
    }

    Complex operator/(Complex &num) const {
        float i, j, k;
        k = Re * Re + num.Im * num.Im;
        i = (Re * num.Re + Im * num.Im) / k;
        j = (num.Re * Im - Re * num.Im) / k;
        return Complex(i, j);
    }

    friend ostream &operator<<(ostream &out, const Complex &x) {
        if (x.Im < 0)
            out << "(" << x.Re << x.Im << "*i)";
        else
            out << "(" << x.Re << "+" << x.Im << "*i)";
        return out;
    }

    friend istream &operator>>(istream &in, Complex &complex) {
        in >> complex.Re;
        in >> complex.Im;
        return in;
    }

    bool operator==(const Complex &num) const { return !(*this != num); }
    bool operator!=(const Complex &num) const {
        if (abs(this->Re - num.Re) >= numeric_limits<float>::epsilon() ||
            abs(this->Im - num.Im) >= numeric_limits<float>::epsilon())
            return true;
        else
            return false;
    }

    bool operator>(float num) const {
        if (this->Re > num)
            return true;
        else
            return false;
    }

    bool operator>(Complex num) const {
        if (sqrt(this->Im*this->Im+this->Re*this->Re) > sqrt(num.Im*num.Im+num.Re*num.Re))
            return true;
        else
            return false;
    }

    bool operator<=(float num) const {
        return !(*this > num);
    }

    bool operator<=(Complex num) const {
        return !(*this > num);
    }

    bool operator<(float num) const {
        return *this <= num && *this != Complex(num, 0.0);
    }

    bool operator<(Complex num) const {
        return *this <= num && *this != Complex(num.Re,num.Im);
    }

    bool operator>=(float num) const {
        return *this > num || *this == Complex(num, 0.0);
    }

    bool operator>=(Complex num) const {
        return *this > num || *this == Complex(num.Re,num.Im);
    }

    bool operator<(float &num) const {
        if (this->Re < num)
            return true;
        else
            return false;
    }
};

#endif //LAB_2_COMPLEX_H
