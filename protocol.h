#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QMap>
#include <QStack>
#include <QList>
#include <QFile>
#include <QString>
#include <QStringList>
#include <iostream>

#include "instruction.h"
#include "data.h"

class Protocol{

public:

    // Methoden
    Protocol(QString source, QStack<Data>* parent_data_stack = 0);
    ~Protocol();
    void run();
    QString dump_data_list();

private:

    // Typedefs
    typedef void (Protocol::*function_pointer)(QList<Argument>);

    // Member-Variablen
    QList<Data*> m_data_list;
    QList<Instruction*> m_instruction_list;
    QMap<QString, function_pointer> m_function_map;
    int m_instruction_counter;
    gmp_randstate_t m_randstate;
    QStack<Data> m_data_stack;
    QStack<Data>* m_parent_data_stack;

    // Methoden
    void initialize_function_map();
    void initialize_randstate();
    void execute_instruction(Instruction instruction);
    Data* data_at_address(Argument address_argument);

    // Funktionen der Laufzeitumgebung
    void seti(QList<Argument> arguments);
    void sets(QList<Argument> arguments);

    #include "protocol.stack.h"
    #include "protocol.math.h"
    #include "protocol.jump.h"

    void outi(QList<Argument> arguments);
    void outs(QList<Argument> arguments);

    void copy(QList<Argument> arguments);
    void size(QList<Argument> arguments);

    void noop(QList<Argument> arguments);
    void exit(QList<Argument> arguments);

    void concat(QList<Argument> arguments);

    bool call_other(Instruction instruction);

};

#endif // PROTOCOL_H
