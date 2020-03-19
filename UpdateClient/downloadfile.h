#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QFileInfo>

class DownloadFile : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFile(QObject *parent = nullptr);
    bool DownloadFromUrl(const QString& _rootDir, const QString& _url, const QString& _relativeName);
signals:

public slots:
    void onReadyRead();
    void onFinished();

private:
    QNetworkAccessManager *myNetworkManager;
    QNetworkRequest myNetworkRequest;
    QNetworkReply *myNetworkReply;

    QString myFullFileName;
};

#endif // DOWNLOADFILE_H
