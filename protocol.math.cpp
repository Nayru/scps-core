#include "protocol.h"

void Protocol::initialize_math_functions(){

    // Arithmetic Functions
    m_function_map["add"] = &Protocol::add;
    m_function_map["sub"] = &Protocol::sub;
    m_function_map["mul"] = &Protocol::mul;
    m_function_map["neg"] = &Protocol::neg;
    m_function_map["abs"] = &Protocol::abs;
    m_function_map["divexact"] = &Protocol::divexact;
    m_function_map["divq"] = &Protocol::divq;
    m_function_map["divqr"] = &Protocol::divqr;
    m_function_map["divr"] = &Protocol::divr;
    m_function_map["pow"] = &Protocol::pow;
    m_function_map["powm"] = &Protocol::powm;
    m_function_map["psqrt"] = &Protocol::psqrt;
    m_function_map["sqrt"] = &Protocol::sqrt;
    m_function_map["sqrtrem"] = &Protocol::sqrtrem;
    m_function_map["fact"] = &Protocol::fact;
    m_function_map["sgn"] = &Protocol::sgn;
    m_function_map["mod"] = &Protocol::mod;

    // Number Theoretic Functions
    m_function_map["probprime"] = &Protocol::probprime;
    m_function_map["nextprime"] = &Protocol::nextprime;
    m_function_map["gcd"] = &Protocol::gcd;
    m_function_map["gcdext"] = &Protocol::gcdext;
    m_function_map["invert"] = &Protocol::invert;
    m_function_map["jacobi"] = &Protocol::jacobi;
    m_function_map["legendre"] = &Protocol::legendre;

    // Logical and Bit Manipulation Functions
    m_function_map["and"] = &Protocol::and_;
    m_function_map["or"] = &Protocol::or_;
    m_function_map["xor"] = &Protocol::xor_;
    m_function_map["com"] = &Protocol::com;
    m_function_map["hamdist"] = &Protocol::hamdist;
    m_function_map["scan0"] = &Protocol::scan0;
    m_function_map["scan1"] = &Protocol::scan1;
    m_function_map["testbit"] = &Protocol::testbit;
    m_function_map["setbit"] = &Protocol::setbit;
    m_function_map["clrbit"] = &Protocol::clrbit;
    m_function_map["popcount"] = &Protocol::popcount;

    // Other Functions
    m_function_map["random"] = &Protocol::random;
    m_function_map["cmp"] = &Protocol::cmp;
    m_function_map["max"] = &Protocol::max;
    m_function_map["min"] = &Protocol::min;

}

// Arithmetic Functions

void Protocol::add(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(operant_1+operant_2);
}

void Protocol::sub(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(operant_1-operant_2);
}

void Protocol::mul(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_mul(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::neg(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_neg(result.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::abs(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_abs(result.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::divexact(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_divexact(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::divq(QList<Argument> arguments){
    int mode = arguments[3].get_integer();
    mpz_class n = data_at_address(arguments[1])->get_integer();
    mpz_class d = data_at_address(arguments[2])->get_integer();
    mpz_class q;
    switch(mode){
        case 0: mpz_cdiv_q(q.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 1: mpz_fdiv_q(q.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 2: mpz_tdiv_q(q.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
    }
    data_at_address(arguments[0])->set_integer(q);
}

void Protocol::divqr(QList<Argument> arguments){
    int mode = arguments[4].get_integer();
    mpz_class n = data_at_address(arguments[2])->get_integer();
    mpz_class d = data_at_address(arguments[3])->get_integer();
    mpz_class q, r;
    switch(mode){
        case 0: mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 1: mpz_fdiv_qr(q.get_mpz_t(),r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 2: mpz_tdiv_qr(q.get_mpz_t(),r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
    }
    data_at_address(arguments[0])->set_integer(q);
    data_at_address(arguments[1])->set_integer(r);
}

void Protocol::divr(QList<Argument> arguments){
    int mode = arguments[3].get_integer();
    mpz_class n = data_at_address(arguments[1])->get_integer();
    mpz_class d = data_at_address(arguments[2])->get_integer();
    mpz_class r;
    switch(mode){
        case 0: mpz_cdiv_r(r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 1: mpz_fdiv_r(r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
        case 2: mpz_tdiv_r(r.get_mpz_t(),n.get_mpz_t(),d.get_mpz_t()); break;
    }
    data_at_address(arguments[0])->set_integer(r);
}

void Protocol::pow(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_pow_ui(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_ui());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::powm(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class operant_3 = data_at_address(arguments[3])->get_integer();
    mpz_class result;
    mpz_powm(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t(),operant_3.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::psqrt(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_perfect_square_p(operant_1.get_mpz_t())));
}

void Protocol::sqrt(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_sqrt(result.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::sqrtrem(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[2])->get_integer();
    mpz_class result_1, result_2;
    mpz_sqrtrem(result_1.get_mpz_t(),result_2.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result_1);
    data_at_address(arguments[1])->set_integer(result_2);
}

void Protocol::fact(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_fac_ui(result.get_mpz_t(),operant_1.get_ui());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::sgn(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_sgn(operant_1.get_mpz_t())));
}

void Protocol::mod(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_mod(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

// Number Theoretic Functions

void Protocol::probprime(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result(mpz_probab_prime_p(operant_1.get_mpz_t(),25));
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::nextprime(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_nextprime(result.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::gcd(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_gcd(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::gcdext(QList<Argument> arguments){
    mpz_class a = data_at_address(arguments[3])->get_integer();
    mpz_class b = data_at_address(arguments[4])->get_integer();
    mpz_class g, s, t;
    mpz_gcdext(g.get_mpz_t(),s.get_mpz_t(),t.get_mpz_t(),a.get_mpz_t(),b.get_mpz_t());
    data_at_address(arguments[0])->set_integer(g);
    data_at_address(arguments[1])->set_integer(s);
    data_at_address(arguments[2])->set_integer(t);
}

void Protocol::invert(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_invert(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::jacobi(QList<Argument> arguments){
    mpz_class a = data_at_address(arguments[1])->get_integer();
    mpz_class b = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_jacobi(a.get_mpz_t(),b.get_mpz_t())));
}

void Protocol::legendre(QList<Argument> arguments){
    mpz_class a = data_at_address(arguments[1])->get_integer();
    mpz_class b = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_legendre(a.get_mpz_t(),b.get_mpz_t())));
}

// Logical and Bit Manipulation Functions

void Protocol::and_(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_and(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::or_(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_ior(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::xor_(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result;
    mpz_xor(result.get_mpz_t(),operant_1.get_mpz_t(),operant_2.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::com(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_com(result.get_mpz_t(),operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::hamdist(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_hamdist(operant_1.get_mpz_t(),operant_2.get_mpz_t())));
}

void Protocol::scan0(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_scan0(operant_1.get_mpz_t(),operant_2.get_ui())));
}

void Protocol::scan1(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_scan1(operant_1.get_mpz_t(),operant_2.get_ui())));
}

void Protocol::testbit(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_tstbit(operant_1.get_mpz_t(),operant_2.get_ui())));
}

void Protocol::setbit(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result(operant_1);
    mpz_setbit(result.get_mpz_t(),operant_2.get_ui());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::clrbit(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    mpz_class result(operant_1);
    mpz_clrbit(result.get_mpz_t(),operant_2.get_ui());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::popcount(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_popcount(operant_1.get_mpz_t())));
}

// Other Functions

void Protocol::random(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class result;
    mpz_urandomm(result.get_mpz_t(),m_randstate,operant_1.get_mpz_t());
    data_at_address(arguments[0])->set_integer(result);
}

void Protocol::cmp(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer(mpz_class(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())));
}

void Protocol::max(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer((operant_1<operant_2)?operant_2:operant_1);
}

void Protocol::min(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    data_at_address(arguments[0])->set_integer((operant_1<operant_2)?operant_1:operant_2);
}
