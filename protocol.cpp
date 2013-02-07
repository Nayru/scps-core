#include "protocol.h"

using namespace std;

Protocol::Protocol(QString source, QStack<Data>* parent_data_stack){

    // Initialisierungen
    m_parent_data_stack = parent_data_stack;
    initialize_function_map();
    initialize_randstate();

    // Instruktionsliste aus dem Quellcode erstellen
    QStringList lines = source.split("\n");
    QStringListIterator line_iterator(lines);
    while(line_iterator.hasNext()) m_instruction_list.append(new Instruction(line_iterator.next()));

}

Protocol::~Protocol(){
    for(int i=0; i<m_data_list.size(); i++) delete m_data_list.at(i);
    for(int j=0; j<m_instruction_list.size(); j++) delete m_instruction_list.at(j);
}

void Protocol::run(){
    m_instruction_counter = 0;
    while(m_instruction_counter<m_instruction_list.size()){
        execute_instruction(*m_instruction_list.at(m_instruction_counter));
        m_instruction_counter++;
    }

}

void Protocol::initialize_function_map(){
    initialize_jump_functions();
    initialize_math_functions();
    initialize_stack_functions();
    m_function_map["seti"] = &Protocol::seti;
    m_function_map["sets"] = &Protocol::sets;
    m_function_map["copy"] = &Protocol::copy;
    m_function_map["size"] = &Protocol::size;
    m_function_map["outi"] = &Protocol::outi;
    m_function_map["outs"] = &Protocol::outs;
    m_function_map["noop"] = &Protocol::noop;
    m_function_map["exit"] = &Protocol::exit;
    m_function_map["concat"] = &Protocol::concat;
}

void Protocol::initialize_randstate(){
    QFile dev_urandom("/dev/urandom");
    dev_urandom.open(QIODevice::ReadOnly);
    char seed[16];
    dev_urandom.read(seed,16);
    dev_urandom.close();
    mpz_class mpz_seed;
    mpz_import(mpz_seed.get_mpz_t(),16,1,1,0,0,seed);
    gmp_randinit_default(m_randstate);
    gmp_randseed(m_randstate,mpz_seed.get_mpz_t());
}

Data* Protocol::data_at_address(Argument address_argument){
    QList<address_part_t> address = address_argument.get_address();
    address_part_t address_part = address.takeFirst();
    int index = address_part.dereference ? m_data_list.at(address_part.index)->get_integer().get_ui() : address_part.index;
    while(m_data_list.size()<index+1) m_data_list.append(new Data());
    Data* result = m_data_list.at(index);
    while(!address.empty()) {
        address_part = address.takeFirst();
        index = address_part.dereference ? m_data_list.at(address_part.index)->get_integer().get_ui() : address_part.index;
        result = result->get_array_element(index);
    }
    return result;
}

QString Protocol::dump_data_list(){
    QString result, index;
    for(int i=0;i<m_data_list.size();i++) result.append(index.setNum(i)).append(": ").append(m_data_list.at(i)->to_string()).append("\n");
    return result;
}

void Protocol::execute_instruction(Instruction instruction){

    //cout << (m_instruction_counter) << ": calling " << instruction.get_instruction_code().toStdString() << endl;

    if(m_function_map.contains(instruction.get_instruction_code())) (this->*m_function_map[instruction.get_instruction_code()])(instruction.get_arguments());
    else if(!call_other(instruction)) {
        cout << "Unbekannter Instruktions-Code \"" << instruction.get_instruction_code().toStdString() << "\"" << endl;
        std::exit(1);
    }

    //cout << endl;

}

void Protocol::seti(QList<Argument> arguments){
    data_at_address(arguments[0])->set_integer(mpz_class(arguments[1].get_integer()));
}

void Protocol::sets(QList<Argument> arguments){
    data_at_address(arguments[0])->set_string(arguments[1].get_string());
}

void Protocol::outi(QList<Argument> arguments){
    cout << data_at_address(arguments[0])->get_integer();
}

void Protocol::outs(QList<Argument> arguments){
    cout << data_at_address(arguments[0])->get_string().toStdString();
}

void Protocol::noop(QList<Argument> arguments){
    Q_UNUSED(arguments);
}

void Protocol::copy(QList<Argument> arguments){
    data_at_address(arguments[0])->inherit(*data_at_address(arguments[1]));
}

void Protocol::size(QList<Argument> arguments){
    data_at_address(arguments[0])->set_integer(data_at_address(arguments[1])->get_array_size());
}

void Protocol::exit(QList<Argument> arguments){
    Q_UNUSED(arguments);
    m_instruction_counter = m_instruction_list.size();
}

void Protocol::concat(QList<Argument> arguments){
    QString operant_1 = data_at_address(arguments[1])->get_string();
    QString operant_2 = data_at_address(arguments[2])->get_string();
    data_at_address(arguments[0])->set_string(operant_1.append(operant_2));
}

bool Protocol::call_other(Instruction instruction){
    // Gleichnamige Datei im Protokoll-Verzeichnis suchen
    QFile file(QString("protocols/").append(instruction.get_instruction_code().append(".prot")));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QList<Argument> arguments = instruction.get_arguments();
        int original_stack_size = m_data_stack.size();
        for(int i=0; i<arguments.length(); i++) m_data_stack.push(*data_at_address(arguments.at(i)));
        Protocol other(file.readAll(),&m_data_stack);
        other.run();
        int number_of_returns = (m_data_stack.size()-original_stack_size)/2;
        for(int i=number_of_returns-1; i>=0; i--) data_at_address(arguments[i])->inherit(m_data_stack.pop());
        while(m_data_stack.size()>original_stack_size) m_data_stack.pop();
        return true;
    }
    return false;
}
