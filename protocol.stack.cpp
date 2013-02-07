#include "protocol.h"

using namespace std;

void Protocol::initialize_stack_functions(){
    m_function_map["poppi"] = &Protocol::poppi;
    m_function_map["popps"] = &Protocol::popps;
    m_function_map["pushpi"] = &Protocol::pushpi;
    m_function_map["pushps"] = &Protocol::pushps;
    m_function_map["push"] = &Protocol::push;
    m_function_map["pushi"] = &Protocol::pushi;
    m_function_map["pushs"] = &Protocol::pushs;
    m_function_map["pop"] = &Protocol::pop;
}

void Protocol::poppi(QList<Argument> arguments){
    mpz_class value;
    if(m_parent_data_stack==0){
        cout << arguments[1].get_string().toStdString();
        cin >> value;
    } else {
        value = m_parent_data_stack->pop().get_integer();
    }
    data_at_address(arguments[0])->set_integer(value);
}

void Protocol::popps(QList<Argument> arguments){
    QString value;
    if(m_parent_data_stack==0){
        cout << arguments[1].get_string().toStdString();
        string std_value;
        cin >> std_value;
        value = QString(std_value.c_str());
    } else {
        value = m_parent_data_stack->pop().get_string();
    }
    data_at_address(arguments[0])->set_string(value);
}

void Protocol::pushpi(QList<Argument> arguments){
    mpz_class value = data_at_address(arguments[0])->get_integer();
    if(m_parent_data_stack==0){
        cout << arguments[1].get_string().toStdString();
        cout << value << endl;
    } else {
        Data data_value;
        data_value.set_integer(value);
        m_parent_data_stack->push(data_value);
    }
}

void Protocol::pushps(QList<Argument> arguments){
    QString value = data_at_address(arguments[0])->get_string();
    if(m_parent_data_stack==0){
        cout << arguments[1].get_string().toStdString();
        cout << value.toStdString() << endl;
    } else {
        Data data_value;
        data_value.set_string(value);
        m_parent_data_stack->push(data_value);
    }
}

void Protocol::push(QList<Argument> arguments){
    m_data_stack.push(*data_at_address(arguments[0]));
}

void Protocol::pushi(QList<Argument> arguments){
    Data value;
    value.set_integer(mpz_class(arguments[0].get_integer()));
    m_data_stack.push(value);
}

void Protocol::pushs(QList<Argument> arguments){
    Data value;
    value.set_string(QString(arguments[0].get_string()));
    m_data_stack.push(value);
}

void Protocol::pop(QList<Argument> arguments){
    data_at_address(arguments[0])->inherit(m_data_stack.pop());
}
