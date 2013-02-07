#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QRegExp>
#include <iostream>

struct address_part_t {
    bool dereference;
    int index;
};

class Argument{

public:

    // Konstruktoren
    Argument();
    Argument(const Argument& other);
    Argument(QString code_snippet);

    // Destruktor
    ~Argument();

    // Reflektionen
    QString to_string();
    QString get_type();

    // Getter und Setter
    void set_string(const QString string);
    QString get_string() const;

    void set_integer(const int integer);
    int get_integer() const;

    void set_address(const QList<address_part_t> address);
    QList<address_part_t> get_address() const;

private:

    // Hilfsfunktionen
    void initialize();
    void clear();

    // Member-Variablen
    QString* m_string;
    int* m_integer;
    QList<address_part_t>* m_address;

};

#endif // ARGUMENT_H
