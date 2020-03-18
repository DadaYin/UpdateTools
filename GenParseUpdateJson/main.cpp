#include <QCoreApplication>

#include "inigenparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IniGenParser iniGenParser;

    return a.exec();
}
