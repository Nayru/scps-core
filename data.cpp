#include "data.h"

// Konstruktoren

Data::Data(){
    initialize();
}

Data::Data(const Data& other){
    initialize();
    inherit(other);
}

void Data::inherit(const Data& other){
    clear(true);
    if(other.m_integer!=0) set_integer(other.get_integer());
    if(other.m_string!=0) set_string(other.get_string());
    if(other.m_array!=0){
        m_array = new QList<Data*>;
        for(int i=0; i<other.m_array->size(); i++) m_array->append(new Data(*other.m_array->at(i)));
    }
}

// Destruktor

Data::~Data(){
    clear(true);
}

// Reflektion

QString Data::get_type(){
    if(m_string!=0) return QString("string");
    if(m_integer!=0) return QString("integer");
    return QString("null");
}

QString Data::to_string(){
    QString type = get_type();
    if(type.compare("string")==0) return QString("DataString(\"").append(QString(*m_string)).append(QString("\")"));
    if(type.compare("integer")==0) return QString("DataInteger(").append(QString(m_integer->get_str().c_str())).append(QString(")"));
    return QString("DataNull");
}

// Getter und Setter

void Data::set_string(const QString string){
    clear();
    m_string = new QString(string);
}

QString Data::get_string() const {
    return QString(*m_string);
}

void Data::set_integer(const mpz_class integer){
    clear();
    m_integer = new mpz_class(integer);
}

mpz_class Data::get_integer() const {
    return mpz_class(*m_integer);
}

// Array-Funktionen

Data* Data::get_array_element(const int index){
    if(m_array==0) m_array = new QList<Data*>;
    while(m_array->size()<index+1) m_array->append(new Data());
    return m_array->at(index);
}

int Data::get_array_size() const {
    if(m_array==0) return 0;
    return m_array->size();
}

// Hilfsfunktionen

void Data::clear(bool clear_array){
    if(m_string!=0){
        delete m_string;
        m_string = 0;
    }
    if(m_integer!=0){
        delete m_integer;
        m_integer = 0;
    }
    if(clear_array){
        if(m_array!=0) {
            for(int i=0; i<m_array->size();i++) delete m_array->at(i);
            delete m_array;
            m_array = 0;
        }
    }
}

void Data::initialize(){
    m_string = 0;
    m_integer = 0;
    m_array = 0;
}
