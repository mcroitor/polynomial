#ifndef MC_POLYNOMIAL_H_
#define MC_POLYNOMIAL_H_
#include <deque>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace mc {

    template<class TYPE>
    class polynomial {
        std::deque<TYPE>coefficients;

    public:
        polynomial();
        polynomial(TYPE);
        polynomial(TYPE, size_t); // monomial
        polynomial(const polynomial<TYPE>&);
        polynomial(std::deque<TYPE>);
#if __cplusplus >= 201103L
        polynomial(std::initializer_list<TYPE>);
#endif

        // add additional monomials with coeff 0
        void extend(size_t);
        // remove leaders monomials with coef 0
        void normalize();

        polynomial<TYPE> operator=(const polynomial<TYPE>&);
        void operator+=(const polynomial<TYPE>&);
        void operator-=(const polynomial<TYPE>&);
        void operator*=(const polynomial<TYPE>&);
        void operator/=(const polynomial<TYPE>&);
        TYPE operator[](const size_t);
        const TYPE operator[](const size_t) const;
        TYPE operator()(const TYPE) const;

        bool equal(const polynomial<TYPE>&) const;

        const size_t degree() const;
    };

    template<class TYPE>
    polynomial<TYPE> operator+(const polynomial<TYPE>&, const polynomial<TYPE>&);
    template<class TYPE>
    polynomial<TYPE> operator-(const polynomial<TYPE>&, const polynomial<TYPE>&);
    template<class TYPE>
    polynomial<TYPE> operator*(const polynomial<TYPE>&, const polynomial<TYPE>&);
    template<class TYPE>
    polynomial<TYPE> operator/(const polynomial<TYPE>&, const polynomial<TYPE>&);
    template<class TYPE>
    polynomial<TYPE> operator%(const polynomial<TYPE>&, const polynomial<TYPE>&);
    template<class TYPE>
    bool operator==(const polynomial<TYPE>&, const polynomial<TYPE>&);

    template<class TYPE>
    std::istream& operator>>(std::istream&, polynomial<TYPE>&);
    template<class TYPE>
    std::ostream& operator<<(std::ostream&, const polynomial<TYPE>&);

    template<class TYPE>
    polynomial<TYPE>::polynomial() {
        coefficients.push_back(TYPE());
    }

    template<class TYPE>
    polynomial<TYPE>::polynomial(const polynomial<TYPE>& p) {
        coefficients.insert(coefficients.end(), p.coefficients.begin(), p.coefficients.end());
    }

    template<class TYPE>
    polynomial<TYPE>::polynomial(TYPE p) {
        coefficients.push_back(p);
    }

    template<class TYPE>
    polynomial<TYPE>::polynomial(TYPE value, size_t degree) {
        extend(degree);
        coefficients.push_back(value);
        normalize();
    }

#if __cplusplus >= 201103L
    template<class TYPE>
    polynomial<TYPE>::polynomial(std::initializer_list<TYPE> p) {
        coefficients.insert(coefficients.end(), p.begin(), p.end());
        normalize();
    }
#endif

    template<class TYPE>
    polynomial<TYPE>::polynomial(std::deque<TYPE> p) {
        coefficients.insert(coefficients.end(), p.begin(), p.end());
        normalize();
    }

    template<class TYPE>
    polynomial<TYPE> polynomial<TYPE>::operator=(const polynomial<TYPE>& p) {
        coefficients.clear();
        coefficients.insert(coefficients.end(), p.coefficients.begin(), p.coefficients.end());
        return *this;
    }

    template<class TYPE>
    void polynomial<TYPE>::extend(size_t size) {
        if (coefficients.size() < size) {
            coefficients.insert(coefficients.end(), size - coefficients.size(), TYPE());
        }
    }

    template<class TYPE>
    void polynomial<TYPE>::normalize() {
        while (coefficients.size() > 1 && *(coefficients.rbegin()) == TYPE()) {
            coefficients.pop_back();
        }
    }

    template<class TYPE>
    void polynomial<TYPE>::operator+=(const polynomial<TYPE>& p) {
        polynomial<TYPE> tmp(p);
        size_t max = degree() > tmp.degree() ? degree() : tmp.degree();
        size_t index;
        this->extend(max + 1);
        tmp.extend(max + 1);
        for (index = 0; index != coefficients.size(); ++index) {
            coefficients[index] += tmp[index];
        }
        normalize();
    }

    template<class TYPE>
    void polynomial<TYPE>::operator-=(const polynomial<TYPE>& p) {
        polynomial<TYPE> tmp(p);
        size_t max = degree() > tmp.degree() ? degree() : tmp.degree();
        size_t index;
        this->extend(max + 1);
        tmp.extend(max + 1);
        for (index = 0; index != coefficients.size(); ++index) {
            coefficients[index] -= tmp[index];
        }
        normalize();
    }

    template<class TYPE>
    void polynomial<TYPE>::operator*=(const polynomial<TYPE>& p) {
        polynomial<TYPE> tmp;
        tmp.extend(degree() + p.degree() + 1);
        size_t i, j;
        for (i = 0; i != coefficients.size(); ++i) {
            for (j = 0; j != p.coefficients.size(); ++j) {
                tmp.coefficients[i + j] += coefficients[i] * p.coefficients[j];
            }
        }

        *this = tmp;
        normalize();
    }

    template<class TYPE>
    void polynomial<TYPE>::operator/=(const polynomial<TYPE>& p) {
        std::deque<TYPE> result;
        TYPE value;
        while (degree() >= p.degree()) {
            value = coefficients.back() / p.coefficients.back();
            result.push_front(value);
            *this -= polynomial<TYPE>(value, degree() - p.degree()) * p;
            normalize();
        }
        *this = polynomial<TYPE>(result);
        normalize();
    }

    template<class TYPE>
    TYPE polynomial<TYPE>::operator[](const size_t index) {
        return coefficients[index];
    }

    template<class TYPE>
    const TYPE polynomial<TYPE>::operator[](const size_t index) const {
        return coefficients[index];
    }

    template<class TYPE>
    TYPE polynomial<TYPE>::operator()(const TYPE value) const {
        TYPE result = TYPE();
        typename std::deque<TYPE>::const_reverse_iterator ri = coefficients.rbegin();
        while (ri != coefficients.rend()) {
            result *= value;
            result += *ri;
            ++ri;
        }
        return result;
    }

    template<class TYPE>
    bool polynomial<TYPE>::equal(const polynomial<TYPE>& p) const {
        if (p.degree() != degree()) {
            return false;
        }
        TYPE top1 = coefficients.back(),
                top2 = p.coefficients.back();
        typename std::deque<TYPE>::const_iterator i = coefficients.begin(),
                j = p.coefficients.begin();
        while (i != coefficients.end()) {
            if (*i * top2 != *j * top1) {
                return false;
            }
            ++i;
            ++j;
        }
        return true;
    }

    template<class TYPE>
    const size_t polynomial<TYPE>::degree() const {
        return coefficients.size() - 1;
    }

    template<class TYPE>
    polynomial<TYPE> operator+(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        polynomial<TYPE> tmp(p1);
        tmp += p2;
        return tmp;
    }

    template<class TYPE>
    polynomial<TYPE> operator-(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        polynomial<TYPE> tmp(p1);
        tmp -= p2;
        return tmp;
    }

    template<class TYPE>
    polynomial<TYPE> operator*(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        polynomial<TYPE> tmp(p1);
        tmp *= p2;
        return tmp;
    }

    template<class TYPE>
    polynomial<TYPE> operator/(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        polynomial<TYPE> tmp(p1);
        tmp /= p2;
        return tmp;
    }

    template<class TYPE>
    polynomial<TYPE> operator%(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        polynomial<TYPE> tmp = p1 / p2;
        tmp *= p2;
        return p1 - tmp;
    }

    template<class TYPE>
    bool operator==(const polynomial<TYPE>& p1, const polynomial<TYPE>& p2) {
        return p1.equal(p2);
    }

    template<class TYPE>
    std::istream& operator>>(std::istream& in, polynomial<TYPE>& p) {
        std::deque<TYPE> c;
        std::copy(std::istream_iterator<TYPE>(in), std::istream_iterator<TYPE>(), std::inserter(c, c.end()));
        p = polynomial<TYPE>(c);
        return in;
    }

    template<class TYPE>
    std::ostream& operator<<(std::ostream& out, const polynomial<TYPE>& p) {
        if (p.degree() == 0) {
            out << p[0];
        } else {
            if (p[0] != TYPE()) {
                out << p[0] << " + ";
            }
            for (size_t i = 1; i != p.degree(); ++i) {
                if (p[i] != TYPE()) {
                    out << "x ^ " << i << " * " << p[i] << " + ";
                }
            }
            out << "x ^ " << p.degree() << " * " << p[p.degree()];
        }
        return out;
    }
}

#endif
