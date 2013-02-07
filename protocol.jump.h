#ifndef PROTOCOL_JUMP_H
#define PROTOCOL_JUMP_H

#include <QList>
#include "argument.h"

void initialize_jump_functions();

void jz(QList<Argument> arguments);
void j(QList<Argument> arguments);
void ja(QList<Argument> arguments);
void jne(QList<Argument> arguments);
void je(QList<Argument> arguments);
void js(QList<Argument> arguments);
void jns(QList<Argument> arguments);
void jnz(QList<Argument> arguments);
void jl(QList<Argument> arguments);
void jnl(QList<Argument> arguments);
void jle(QList<Argument> arguments);
void jnle(QList<Argument> arguments);
void jg(QList<Argument> arguments);
void jng(QList<Argument> arguments);
void jge(QList<Argument> arguments);
void jnge(QList<Argument> arguments);

#endif // PROTOCOL_JUMP_H
