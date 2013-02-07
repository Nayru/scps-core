#include "argument.h"

// Konstruktoren

Argument::Argument(){
    initialize();
}

Argument::Argument(const Argument& other){
    initialize();
    if(other.m_string!=0) set_string(other.get_string());
    if(other.m_integer!=0) set_integer(other.get_integer());
    if(other.m_address!=0) set_address(other.get_address());
}

Argument::Argument(QString code_snippet){

    initialize();

    QRegExp rx_integer("^-?\\d+$");
    QRegExp rx_address("^\\*?\\d+(:\\*?\\d+)*$");

    if(rx_integer.exactMatch(code_snippet)){
        set_integer(code_snippet.toInt());
    }
    else
    if(rx_address.exactMatch(code_snippet)){
        QStringList parts = code_snippet.split(":");
        QList<address_part_t> address;
        for(int i=0; i<parts.size(); i++) {
            address_part_t address_part;
            address_part.dereference = parts.at(i).startsWith(QString("*"));
            address_part.index = address_part.dereference ? parts.at(i).mid(1).toInt() : parts.at(i).toInt();
            address.append(address_part);
        }
        set_address(address);
    }
    else {
        QString string = QString(code_snippet);
        if(string.startsWith('"') && string.endsWith('"')) string = string.mid(1,string.length()-2);
        string = string.replace("\\n","\n").replace("\\r","\r").replace("\\t","\t");
        set_string(string);
    }

}

// Dekonstruktor

Argument::~Argument(){
    clear();
}

// Reflektionen

QString Argument::to_string(){
    QString type = get_type();
    if(type.compare("string")==0) return QString("ArgumentString(\"").append(QString(*m_string)).append(QString("\")"));
    if(type.compare("integer")==0) return QString("ArgumentInteger(").append(QString().setNum(*m_integer)).append(QString(")"));
    if(type.compare("address")==0){
        QString result("ArgumentAddress(");
        for(int i=0; i<m_address->size(); i++) {
            if(m_address->at(i).dereference) result.append(QString("*"));
            result.append(QString().setNum(m_address->at(i).index)).append(":");
        }
        result = result.mid(0,result.length()-1); // Letzten : entfernen
        return result.append(QString(")"));
    }
    return QString("ArgumentNull");
}

QString Argument::get_type(){
    if(m_string!=0) return QString("string");
    if(m_integer!=0) return QString("integer");
    if(m_address!=0) return QString("address");
    return QString("null");
}

// Getter und Setter

void Argument::set_string(const QString string){
    clear();
    m_string = new QString(string);
}

QString Argument::get_string() const {
    return QString(*m_string);
}

void Argument::set_integer(const int integer){
    clear();
    m_integer = new int(integer);
}

int Argument::get_integer() const {
    return int(*m_integer);
}

void Argument::set_address(const QList<address_part_t> address){
    clear();
    m_address = new QList<address_part_t>(address);
}

QList<address_part_t> Argument::get_address() const {
    if(m_address==0) {
        QList<address_part_t> address;
        address_part_t address_part;
        address_part.dereference = false;
        address_part.index = get_integer();
        address.append(address_part);
        return address;
    }
    return QList<address_part_t>(*m_address);
}

// Hilfsfunktionen

void Argument::initialize(){
    m_string = 0;
    m_integer = 0;
    m_address = 0;
}

void Argument::clear(){
    if(m_string!=0){
        delete m_string;
        m_string = 0;
    }
    if(m_integer!=0){
        delete m_integer;
        m_integer = 0;
    }
    if(m_address!=0){
        delete m_address;
        m_address = 0;
    }
}
