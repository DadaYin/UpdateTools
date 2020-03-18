#include "inigenparser.h"
#include "DataStruct.h"
#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>

#include "jsongenparser.h"


IniGenParser::IniGenParser(QObject *parent) : QObject(parent)
{
    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/basic.ini";

    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF8");

    BasicInfo basicInfo;
    basicInfo.MainVersion = settings.value("MainVersion").toString();
    basicInfo.UpdateDir = settings.value("UpdateDir").toString();
    basicInfo.HttpRootUrl = settings.value("HttpRootUrl").toString();

    QList<QString> fileList;
    FindFile(basicInfo.UpdateDir, basicInfo.UpdateDir,fileList);

    QList<OneUpdateFileInfo> UpdateFileInfoList;
    for(int i=0; i<fileList.size(); i++)
    {
        QString absoluteName = basicInfo.UpdateDir + "/" + fileList[i];

        OneUpdateFileInfo oneInfo;
        oneInfo.RelativeName = fileList[i];
        oneInfo.LatestVersion = basicInfo.MainVersion;
        oneInfo.MD5 = getFileMd5(absoluteName);
        oneInfo.Url = basicInfo.HttpRootUrl + fileList[i];
        oneInfo.ReleaseNote = "";

        UpdateFileInfoList.push_back(oneInfo);
    }

    UpdateJsonInfo jsonInfo;
    jsonInfo.MainVersion = basicInfo.MainVersion;
    jsonInfo.DescribeSize = 0;
    jsonInfo.Describe.clear();

    jsonInfo.FileSize = UpdateFileInfoList.size();
    jsonInfo.UpdateFileInfoList = UpdateFileInfoList;

    JsonGenParser jsonGen;
    if(jsonGen.GenUpdateJson(jsonInfo, "update.json"))
    {
        qDebug() << "Gen Json File Success!";
    }
    else
    {
        qDebug() << "Gen Json File Failed!";
    }


    UpdateJsonInfo tmpJson;
    jsonGen.ParseUpdateJson("update3.json", tmpJson);

    jsonGen.GenUpdateJson(tmpJson, "update2.json");
}

int IniGenParser::FindFile(const QString &_filePath, const QString& _relativefilePath, QList<QString>& _fileList)
{
    QDir dir(_filePath);
        if (!dir.exists()) {
            return -1;
        }

      //取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
        dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

        //文件夹优先
        dir.setSorting(QDir::DirsFirst);

        //转化成一个list
        QFileInfoList list = dir.entryInfoList();
        if(list.size()< 1 ) {
            return -1;
        }
        int i=0;

        //递归算法的核心部分
        do{
            QFileInfo fileInfo = list.at(i);
            //如果是文件夹，递归
            bool bisDir = fileInfo.isDir();
            if(bisDir) {
                FindFile(fileInfo.filePath(), _relativefilePath, _fileList);
            }
            else{
                //去除前面的目录名字，改为相对文件名
                QString relativeFileName = fileInfo.filePath().remove(0, _relativefilePath.size() + 1);
                _fileList.push_back(relativeFileName);
            }//end else
            i++;
        } while(i < list.size());

        return i;
}

QByteArray IniGenParser::getFileMd5(const QString &_fileName)
{
    QFile theFile(_fileName);
    theFile.open(QIODevice::ReadOnly);
    QByteArray md5 = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
    theFile.close();

    return md5.toHex();
}
