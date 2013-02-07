#include "protocol.h"

void Protocol::initialize_jump_functions(){
    m_function_map["j"] = &Protocol::j;
    m_function_map["ja"] = &Protocol::ja;
    m_function_map["jz"] = &Protocol::jz;
    m_function_map["jne"] = &Protocol::jne;
    m_function_map["je"] = &Protocol::je;
    m_function_map["js"] = &Protocol::js;
    m_function_map["jns"] = &Protocol::jns;
    m_function_map["jnz"] = &Protocol::jnz;
    m_function_map["jl"] = &Protocol::jl;
    m_function_map["jnl"] = &Protocol::jnl;
    m_function_map["jle"] = &Protocol::jle;
    m_function_map["jnle"] = &Protocol::jnle;
    m_function_map["jg"] = &Protocol::jg;
    m_function_map["jng"] = &Protocol::jng;
    m_function_map["jge"] = &Protocol::jge;
    m_function_map["jnge"] = &Protocol::jge;
}

void Protocol::jz(QList<Argument> arguments){
    mpz_class value = data_at_address(arguments[1])->get_integer();
    if(mpz_cmp_ui(value.get_mpz_t(),0)==0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::j(QList<Argument> arguments){
    m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::ja(QList<Argument> arguments){
    m_instruction_counter = data_at_address(arguments[0])->get_integer().get_ui()-1;
}

void Protocol::jne(QList<Argument> arguments){
    Data* operant_1 = data_at_address(arguments[1]);
    Data* operant_2 = data_at_address(arguments[2]);
    if(operant_1->get_type().compare(operant_2->get_type())==0){
        if(operant_1->get_type().compare(QString("string"))==0){
            QString string_1 = operant_1->get_string();
            QString string_2 = operant_2->get_string();
            if(string_1.compare(string_2)!=0) m_instruction_counter = arguments[0].get_integer()-1;
        }
        if(operant_1->get_type().compare(QString("integer"))==0){
            mpz_class integer_1 = operant_1->get_integer();
            mpz_class integer_2 = operant_2->get_integer();
            if(mpz_cmp(integer_1.get_mpz_t(),integer_2.get_mpz_t())!=0) m_instruction_counter = arguments[0].get_integer()-1;
        }
    } else m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::je(QList<Argument> arguments){
    Data* operant_1 = data_at_address(arguments[1]);
    Data* operant_2 = data_at_address(arguments[2]);
    if(operant_1->get_type().compare(operant_2->get_type())==0){
        if(operant_1->get_type().compare(QString("string"))==0){
            QString string_1 = operant_1->get_string();
            QString string_2 = operant_2->get_string();
            if(string_1.compare(string_2)==0) m_instruction_counter = arguments[0].get_integer()-1;
        }
        if(operant_1->get_type().compare(QString("integer"))==0){
            mpz_class integer_1 = operant_1->get_integer();
            mpz_class integer_2 = operant_2->get_integer();
            if(mpz_cmp(integer_1.get_mpz_t(),integer_2.get_mpz_t())==0) m_instruction_counter = arguments[0].get_integer()-1;
        }
    }
}

void Protocol::js(QList<Argument> arguments){
    mpz_class value = data_at_address(arguments[1])->get_integer();
    if(mpz_sgn(value.get_mpz_t())==1) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jns(QList<Argument> arguments){
    mpz_class value = data_at_address(arguments[1])->get_integer();
    if(mpz_sgn(value.get_mpz_t())==-1) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jnz(QList<Argument> arguments){
    mpz_class value = data_at_address(arguments[1])->get_integer();
    if(mpz_cmp_ui(value.get_mpz_t(),0)!=0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jl(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())<0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jnl(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())>=0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jle(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())<=0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jnle(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())>0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jg(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())>0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jng(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())<=0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jge(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())>=0) m_instruction_counter = arguments[0].get_integer()-1;
}

void Protocol::jnge(QList<Argument> arguments){
    mpz_class operant_1 = data_at_address(arguments[1])->get_integer();
    mpz_class operant_2 = data_at_address(arguments[2])->get_integer();
    if(mpz_cmp(operant_1.get_mpz_t(),operant_2.get_mpz_t())<0) m_instruction_counter = arguments[0].get_integer()-1;
}
