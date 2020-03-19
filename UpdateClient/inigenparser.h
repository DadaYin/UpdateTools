#ifndef INIGENPARSER_H
#define INIGENPARSER_H

#include <QObject>
#include "DataStruct.h"

class IniGenParser : public QObject
{
    Q_OBJECT
public:
    explicit IniGenParser(QObject *parent = nullptr);

    ClientBasicInfo GetBasicInfo();

signals:

public slots:
};

#endif // INIGENPARSER_H
