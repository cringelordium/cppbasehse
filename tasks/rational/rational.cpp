#include <rational.h>

Rational::Rational() : numer_(0), denom_(1) {

    Set(numer_, denom_);
}

Rational::Rational(int value) : numer_(value), denom_(1) {

    Set(numer_, denom_);
}  // NOLINT

Rational::Rational(int numer, int denom) : numer_(numer), denom_(denom) {

    Set(numer_, denom_);
}

int Rational::GetNumerator() const {

    return numer_;
}

int Rational::GetDenominator() const {

    return denom_;
}

void Rational::SetNumerator(int value) {

    numer_ = value;

    Set(numer_, denom_);
}

void Rational::SetDenominator(int value) {

    denom_ = value;

    Set(numer_, denom_);
}
Rational& operator+=(Rational& lhs, const Rational& rhs) {

    lhs.numer_ = lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_;
    lhs.denom_ *= rhs.denom_;

    lhs = Rational(lhs.numer_, lhs.denom_);

    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {

    int64_t new_numer = static_cast<int64_t>(lhs.numer_) * rhs.numer_;
    int64_t new_denom = static_cast<int64_t>(lhs.denom_) * rhs.denom_;

    int64_t gcd = std::gcd(new_numer, new_denom);
    new_numer /= gcd;
    new_denom /= gcd;

    lhs.numer_ = static_cast<int>(new_numer);
    lhs.denom_ = static_cast<int>(new_denom);

    return lhs;
}

Rational& operator++(Rational& ratio) {

    ratio.numer_ += ratio.denom_;

    return ratio;
}

Rational& operator--(Rational& ratio) {

    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {

    int numer = 0;
    char slash = '/';

    if (is >> numer) {

        char next_char = '/';
        if (is.get(next_char) && next_char == slash) {

            int denom = 0;
            if (is >> denom) {

                ratio.Set(numer, denom);

            } else {

                throw std::invalid_argument("Invalid input");
            }
        } else {

            is.putback(next_char);
            ratio.Set(numer, 1);
        }
    } else {

        throw std::invalid_argument("Invalid input");
    }

    return is;
}

void Rational::Set(int64_t numer, int64_t denom) {

    if (!denom) {
        throw RationalDivisionByZero{};
    }
    if (numer * denom < 0) {

        numer_ = static_cast<int>(-std::abs(numer));
        denom_ = static_cast<int>(std::abs(denom));
    } else {

        numer_ = static_cast<int>(std::abs(numer));
        denom_ = static_cast<int>(std::abs(denom));
    }

    int64_t gcd = std::gcd(numer_, denom_);
    numer_ /= static_cast<int>(gcd);
    denom_ /= static_cast<int>(gcd);
}

Rational operator+(const Rational& ratio) {

    return ratio;
}

Rational operator-(const Rational& ratio) {

    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {

    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetDenominator());

    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {

    lhs.SetNumerator(lhs.GetNumerator() * rhs.GetDenominator());
    lhs.SetDenominator(lhs.GetDenominator() * rhs.GetNumerator());

    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {

    int new_numer = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
    int new_denom = lhs.GetDenominator() * rhs.GetDenominator();

    return Rational(new_numer, new_denom);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {

    int new_numer = lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator();
    int new_denom = lhs.GetDenominator() * rhs.GetDenominator();

    return Rational(new_numer, new_denom);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {

    int64_t new_numer = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetNumerator();
    int64_t new_denom = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();

    int64_t gcd = std::gcd(new_numer, new_denom);
    new_numer /= gcd;
    new_denom /= gcd;

    return Rational(static_cast<int>(new_numer), static_cast<int>(new_denom));
}

Rational operator/(const Rational& lhs, const Rational& rhs) {

    return Rational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
}

Rational operator++(Rational& ratio, int) {

    Rational tmp = ratio;

    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());

    return tmp;
}

Rational operator--(Rational& ratio, int) {

    Rational tmp = ratio;

    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());

    return tmp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < lhs.GetDenominator() * rhs.GetNumerator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() == lhs.GetDenominator() * rhs.GetNumerator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {

    if (ratio.GetDenominator() == 1) {

        os << ratio.GetNumerator();
    } else {
        if (ratio.GetNumerator() < 0) {

            os << "-";
        }

        os << std::abs(ratio.GetNumerator()) << '/' << ratio.GetDenominator();
    }

    return os;
}
