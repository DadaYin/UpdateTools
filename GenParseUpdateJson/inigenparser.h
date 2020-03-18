#ifndef INIGENPARSER_H
#define INIGENPARSER_H

#include <QObject>
#include <QList>

class IniGenParser : public QObject
{
    Q_OBJECT
public:
    explicit IniGenParser(QObject *parent = nullptr);
    int FindFile(const QString& _filePath, const QString& _relativefilePath, QList<QString>& _fileList);

    QByteArray getFileMd5(const QString& _fileName);

signals:

public slots:
};

#endif // INIGENPARSER_H
