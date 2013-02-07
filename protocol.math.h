#ifndef PROTOCOL_MATH_H
#define PROTOCOL_MATH_H

#include <QList>
#include "argument.h"

void initialize_math_functions();

// Arithmetic Functions
void add(QList<Argument> arguments);
void sub(QList<Argument> arguments);
void mul(QList<Argument> arguments);
void neg(QList<Argument> arguments);
void abs(QList<Argument> arguments);
void divexact(QList<Argument> arguments);
void divq(QList<Argument> arguments);
void divqr(QList<Argument> arguments);
void divr(QList<Argument> arguments);
void pow(QList<Argument> arguments);
void powm(QList<Argument> arguments);
void psqrt(QList<Argument> arguments);
void sqrt(QList<Argument> arguments);
void sqrtrem(QList<Argument> arguments);
void fact(QList<Argument> arguments);
void sgn(QList<Argument> arguments);
void mod(QList<Argument> arguments);

// Number Theoretic Functions
void probprime(QList<Argument> arguments);
void nextprime(QList<Argument> arguments);
void gcd(QList<Argument> arguments);
void gcdext(QList<Argument> arguments);
void invert(QList<Argument> arguments);
void jacobi(QList<Argument> arguments);
void legendre(QList<Argument> arguments);

// Logical and Bit Manipulation Functions
void and_(QList<Argument> arguments);
void or_(QList<Argument> arguments);
void xor_(QList<Argument> arguments);
void com(QList<Argument> arguments);
void hamdist(QList<Argument> arguments);
void scan0(QList<Argument> arguments);
void scan1(QList<Argument> arguments);
void setbit(QList<Argument> arguments);
void testbit(QList<Argument> arguments);
void clrbit(QList<Argument> arguments);
void popcount(QList<Argument> arguments);

// Other Functions
void random(QList<Argument> arguments);
void cmp(QList<Argument> arguments);
void max(QList<Argument> arguments);
void min(QList<Argument> arguments);

#endif // PROTOCOL_MATH_H
