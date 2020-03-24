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
    void DownLoadFinished(QString fullFileName, QString relativeFileName);
    void DownLoadError(QString fullFileName, QString relativeFileName, QNetworkReply::NetworkError);

public slots:
    void onReadyRead();
    void onFinished();
    void OnError(QNetworkReply::NetworkError);

private:
    QNetworkAccessManager *myNetworkManager;
    QNetworkRequest myNetworkRequest;
    QNetworkReply *myNetworkReply;

    QString myFullFileName;
    QString relativeName_;

    bool AppendStatus;
};

#endif // DOWNLOADFILE_H
