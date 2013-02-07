#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QList>
#include <gmpxx.h>
#include <gmp.h>

class Data {

public:

    // Konstruktoren
    Data();
    Data(const Data& other);
    void inherit(const Data& other);

    // Destruktor
    ~Data();

    // Reflektion
    QString to_string();
    QString get_type();

    // Getter und Setter
    void set_string(const QString string);
    QString get_string() const;

    void set_integer(const mpz_class integer);
    mpz_class get_integer() const;

    // Array-Funktionen
    Data* get_array_element(const int index);
    int get_array_size() const;

private:

    // Hilfsfunktionen
    void initialize();
    void clear(bool clear_array=false);

    // Member-Variablen
    QString* m_string;
    mpz_class* m_integer;
    QList<Data*>* m_array;

};

#endif // DATA_H
