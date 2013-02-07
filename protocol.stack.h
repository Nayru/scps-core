#ifndef PROTOCOL_STACK_H
#define PROTOCOL_STACK_H

#include <QList>
#include "argument.h"

void initialize_stack_functions();

void push(QList<Argument> arguments);
void pop(QList<Argument> arguments);
void pushi(QList<Argument> arguments);
void pushs(QList<Argument> arguments);
void pushpi(QList<Argument> arguments);
void pushps(QList<Argument> arguments);
void poppi(QList<Argument> arguments);
void popps(QList<Argument> arguments);

#endif // PROTOCOL_STACK_H
