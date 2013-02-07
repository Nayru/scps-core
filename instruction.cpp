#include "instruction.h"

// Konstruktoren

Instruction::Instruction(const QString instruction_code, const QList<Argument> arguments){
    set_instruction_code(instruction_code);
    set_arguments(arguments);
}

Instruction::Instruction(const Instruction& other){
    set_instruction_code(other.get_instruction_code());
    set_arguments(other.get_arguments());
}

Instruction::Instruction(QString line_of_code){

    line_of_code = line_of_code.trimmed();

    // Kommentare entfernen
    line_of_code.replace(QRegExp("\\s*#.*"),"");
    if(line_of_code.length()==0) line_of_code = QString("noop");

    // Bestandteile erkennen
    QStringList parts;
    QString current_part = "";
    QChar current_char = QChar::Null;
    QChar previous_char = QChar::Null;
    bool string_mode = false;

    for(int index=0;index<line_of_code.length();index++){

        previous_char = current_char;
        current_char = line_of_code.at(index);

        if(current_char=='"' && previous_char!='\\') {
            if(string_mode){
                parts << current_part;
                current_part = "";
            }
            string_mode = !string_mode;
            continue;
        }

        if(current_char=='"' && previous_char=='\\') {
            current_part.remove(current_part.length()-1,1);
        }

        if(current_char==' ' && !string_mode){
            if(current_part.length()>0) parts << current_part;
            current_part = "";
            continue;
        }

        current_part.append(current_char);

    }

    if(current_part.length()>0) parts << current_part;

    // Der erste Teil ist der Instruktionscode
    set_instruction_code(parts.takeFirst());

    // Der Rest wird in Argumente umgewandelt
    QList<Argument> arguments;
    QStringListIterator parts_iterator(parts);
    while(parts_iterator.hasNext()) arguments.append(Argument(parts_iterator.next()));
    set_arguments(arguments);

}

// Destrukor

Instruction::~Instruction(){
    for(int i=0; i<m_arguments.size(); i++) delete m_arguments.at(i);
}

// Getter und Setter

QString Instruction::get_instruction_code() const {
    return QString(m_instruction_code);
}

void Instruction::set_instruction_code(const QString instruction_code){
    m_instruction_code = QString(instruction_code);
}

QList<Argument> Instruction::get_arguments() const {
    QList<Argument> result;
    for(int i=0; i<m_arguments.size(); i++) result.append(Argument(*m_arguments.at(i)));
    return result;
}

void Instruction::set_arguments(const QList<Argument> arguments){
    for(int i=0; i<m_arguments.size(); i++) delete m_arguments.at(i);
    m_arguments.clear();
    for(int j=0; j<arguments.size(); j++) m_arguments.append(new Argument(arguments.at(j)));
}



