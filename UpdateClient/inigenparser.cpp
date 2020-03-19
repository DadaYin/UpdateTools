#include "inigenparser.h"
#include <QSettings>
#include <QCoreApplication>

IniGenParser::IniGenParser(QObject *parent) : QObject(parent)
{

}

ClientBasicInfo IniGenParser::GetBasicInfo()
{
    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/basic.ini";

    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF8");

    ClientBasicInfo basicInfo;
    basicInfo.UpdateDir = settings.value("UpdateDir").toString();
    basicInfo.HttpRootUrl = settings.value("HttpRootUrl").toString();

    return basicInfo;
}
