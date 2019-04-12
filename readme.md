# Polynomial - just polynomials

## Description

The _Polynomial Library_ represents a template class for manipulating with polynomials:
__a0 + a1 * x + a2 * x^2 + ... + an * x^n__. 

## TODO

I want to add next methods:
 * finding roots of polynomials;
 * derivative;
 * integral (without constant C)

## Example

```C++
mc::polynomial<double> p1 = {1, 2, 1};
mc::polynomial<double> p2 = {1, 1};
mc::polynomial<double> p = p1 + p2;

std::cout << p(-2);
```

## Interface

```C++
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
}
```
