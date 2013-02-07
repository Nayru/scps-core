#include <QCoreApplication>
#include <QFile>
#include <iostream>
#include "argument.h"
#include "protocol.h"
#include "data.h"
#include "gmpxx.h"
#include "gmp.h"

using namespace std;

int main(int argc, char *argv[])
{

    if(argc<2){
        cout << "Aufruf: scps-core [DATEI]" << endl;
        exit(1);
    }

    // Lese die Beispieldatei
    QFile file(argv[1]);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Protocol example(file.readAll());
        example.run();
    } else {
        cout << "Die Datei\"" << argv[1] << "\" ist nicht vorhanden oder konnte nicht geöffnet werden." << endl;
        exit(1);
    }

    cout << endl;
    exit(0);


}
