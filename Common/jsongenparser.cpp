#include "jsongenparser.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonParseError>

#include <QFile>
#include <QTextStream>

#include "util.h"

JsonGenParser::JsonGenParser(QObject *parent) : QObject(parent)
{

}

bool JsonGenParser::GenUpdateJson(const UpdateJsonInfo &_updateJsonInfo, const QString &_fileName)
{
    QJsonObject json;

    QJsonArray descArray = GenDescribeJson(_updateJsonInfo.Describe);
    QJsonArray updateFileArray = GenUpdateFileJson(_updateJsonInfo.UpdateFileInfoList);

    json.insert("MainVersion", _updateJsonInfo.MainVersion);

    json.insert("DescribeSize", _updateJsonInfo.DescribeSize);
    json.insert("Describe", QJsonValue(descArray));

    json.insert("FileSize", _updateJsonInfo.FileSize);
    json.insert("UpdateFileInfoList", QJsonValue(updateFileArray));

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);
    QString strJson(byteArray);

    QFile file(_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << strJson.toUtf8();

    file.close();

    return true;
}

bool JsonGenParser::ParseUpdateJson(const QString &_fileName, UpdateJsonInfo &_updateJsonInfo)
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray byteArray = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if(document.isObject())
        {
            QJsonObject object = document.object();

            //判断json文件是否完整，如果不完整，直接返回错误
            if(!object.contains("MainVersion")
                    || !object.contains("DescribeSize")
                    || !object.contains("Describe")
                    || !object.contains("FileSize")
                    || !object.contains("UpdateFileInfoList"))
            {
                return false;
            }

            _updateJsonInfo.MainVersion = object.value("MainVersion").toString();
            _updateJsonInfo.DescribeSize = object.value("DescribeSize").toInt();
            _updateJsonInfo.FileSize = object.value("FileSize").toInt();

            QJsonValue DescribeValue = object.value("Describe");
            QJsonValue UpdateFileInfoListValue = object.value("UpdateFileInfoList");

            QList<QString> Describe;
            ParseDescribe(DescribeValue, _updateJsonInfo.DescribeSize, Describe);

            QList<OneUpdateFileInfo> UpdateFileInfoList;
            ParseUpdateFile(UpdateFileInfoListValue, _updateJsonInfo.FileSize, UpdateFileInfoList);

            _updateJsonInfo.Describe = Describe;
            _updateJsonInfo.UpdateFileInfoList = UpdateFileInfoList;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

QJsonArray JsonGenParser::GenDescribeJson(const QList<QString> &_describe)
{
    QJsonArray descArray;
    for(int i=0; i<_describe.size(); i++)
    {
        descArray.append(_describe[i]);
    }
    return descArray;
}

bool JsonGenParser::ParseDescribe(const QJsonValue &_value, const int _size, QList<QString> &_Describe)
{
    if(!_value.isArray())
    {
        return false;
    }
    QJsonArray array = _value.toArray();
    int nSize = array.size();
    if(nSize != _size)
    {
        return false;
    }
    for(int i=0; i<nSize; i++)
    {
        _Describe.push_back(array[i].toString());
    }
    return true;
}

QJsonArray JsonGenParser::GenUpdateFileJson(const QList<OneUpdateFileInfo> &_UpdateFileInfoList)
{
    QJsonArray updateFileArray;
    for(int i=0; i<_UpdateFileInfoList.size(); i++)
    {
        QJsonObject oneObj = GenOneUpdateFileInfo(_UpdateFileInfoList[i]);
        updateFileArray.append(QJsonValue(oneObj));
    }
    return updateFileArray;
}

bool JsonGenParser::ParseUpdateFile(const QJsonValue &_value, const int _size, QList<OneUpdateFileInfo>& _UpdateFileInfoList)
{
    if(!_value.isArray())
    {
        return false;
    }
    QJsonArray array = _value.toArray();
    int nSize = array.size();
    if(nSize != _size)
    {
        return false;
    }
    for(int i=0; i<nSize; i++)
    {
        OneUpdateFileInfo oneInfo;
        ParseOneUpdateFile(array[i], oneInfo);
        _UpdateFileInfoList.push_back(oneInfo);
    }
    return true;
}

QJsonObject JsonGenParser::GenOneUpdateFileInfo(const OneUpdateFileInfo &_oneInfo)
{
    QJsonObject oneObj;
    oneObj.insert("RelativeName", _oneInfo.RelativeName);
    oneObj.insert("LatestVersion", _oneInfo.LatestVersion);
    oneObj.insert("MD5", _oneInfo.MD5);
    oneObj.insert("Url", _oneInfo.Url);
    oneObj.insert("ReleaseNote", _oneInfo.ReleaseNote);

    return oneObj;
}

bool JsonGenParser::ParseOneUpdateFile(const QJsonValue &_value, OneUpdateFileInfo &_oneInfo)
{
    QJsonObject oneObj = _value.toObject();

    //如果数据错误，返回false
    if(!oneObj.contains("RelativeName")
            ||!oneObj.contains("LatestVersion")
            ||!oneObj.contains("MD5")
            ||!oneObj.contains("Url")
            ||!oneObj.contains("ReleaseNote"))
    {
        return false;
    }

    _oneInfo.RelativeName       = oneObj.value("RelativeName").toString();
    _oneInfo.LatestVersion      = oneObj.value("LatestVersion").toString();
    _oneInfo.MD5                = oneObj.value("MD5").toString();
    _oneInfo.Url                = oneObj.value("Url").toString();
    _oneInfo.ReleaseNote        = oneObj.value("ReleaseNote").toString();

    return true;
}
