#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QChar>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <argument.h>
#include <iostream>

class Instruction {

public:

    // Konstruktoren
    Instruction(const QString instruction_code, const QList<Argument> arguments);
    Instruction(const Instruction& other);
    Instruction(QString line_of_code);

    // Destruktor
    ~Instruction();

    // Getter und Setter
    QString get_instruction_code() const;
    void set_instruction_code(const QString instruction_code);

    QList<Argument> get_arguments() const;
    void set_arguments(const QList<Argument> arguments);

private:

    // Member-Variablen
    QString m_instruction_code;
    QList<Argument*> m_arguments;

};

#endif // INSTRUCTION_H
