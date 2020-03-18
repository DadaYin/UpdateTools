#ifndef JSONGENPARSER_H
#define JSONGENPARSER_H

#include <QObject>
#include "DataStruct.h"


class QJsonObject;
class QJsonArray;
class QJsonValue;

class JsonGenParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonGenParser(QObject *parent = nullptr);

    bool GenUpdateJson(const UpdateJsonInfo& _updateJsonInfo, const QString & _fileName);
    bool ParseUpdateJson(const QString & _fileName, UpdateJsonInfo& _updateJsonInfo);

    QJsonArray GenDescribeJson(const QList<QString>& _describe);
    bool ParseDescribe(const QJsonValue& _value, const int _size, QList<QString>& _Describe);

    QJsonArray GenUpdateFileJson(const QList<OneUpdateFileInfo>& _UpdateFileInfoList);
    bool ParseUpdateFile(const QJsonValue& _value, const int _size, QList<OneUpdateFileInfo>& _UpdateFileInfoList);

    QJsonObject GenOneUpdateFileInfo(const OneUpdateFileInfo& _oneInfo);
    bool ParseOneUpdateFile(const QJsonValue& _value, OneUpdateFileInfo& _oneInfo);
signals:

public slots:
};

#endif // JSONGENPARSER_H
