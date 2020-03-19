#include "downloadfile.h"
#include <QThread>

DownloadFile::DownloadFile(QObject *parent) : QObject(parent)
{

}

bool DownloadFile::DownloadFromUrl(const QString &_rootDir, const QString &_url, const QString &_relativeName)
{
    qDebug() << QThread::currentThreadId() <<__FILE__<<__LINE__;
    QNetworkAccessManager *myNetworkManager = new QNetworkAccessManager(this);

    myFullFileName = _rootDir + _relativeName;

    myNetworkRequest.setUrl(QUrl(_url));
    myNetworkReply = myNetworkManager->get(myNetworkRequest);
    connect(myNetworkReply,SIGNAL(finished()),this,SLOT(onFinished()));
    connect(myNetworkReply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    qDebug()<<__FILE__<<__LINE__;

    return true;
}

void DownloadFile::onReadyRead()
{
    QFile myDownloadFile(myFullFileName);

    if(!myDownloadFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "打开失败";
    }
    myDownloadFile.write(myNetworkReply->readAll());

    myDownloadFile.close();
}

void DownloadFile::onFinished()
{

}
