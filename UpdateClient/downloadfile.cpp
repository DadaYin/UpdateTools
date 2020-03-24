#include "downloadfile.h"
#include "util.h"
#include <QThread>

DownloadFile::DownloadFile(QObject *parent) : QObject(parent)
{
    AppendStatus = false;
}

bool DownloadFile::DownloadFromUrl(const QString &_rootDir, const QString &_url, const QString &_relativeName)
{
//    qDebug() << QThread::currentThreadId() <<__FILE__<<__LINE__ << "---_rootDir = " << _rootDir << ",_url = " << _url << ",_relativeName = " << _relativeName;
    QNetworkAccessManager *myNetworkManager = new QNetworkAccessManager(this);

    myFullFileName = _rootDir + _relativeName;
    relativeName_ = _relativeName;

    myNetworkRequest.setUrl(QUrl(_url));
    myNetworkReply = myNetworkManager->get(myNetworkRequest);
    connect(myNetworkReply,SIGNAL(finished()),this,SLOT(onFinished()));
    connect(myNetworkReply,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(myNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(OnError(QNetworkReply::NetworkError)));

    return true;
}

void DownloadFile::onReadyRead()
{
//    myDebug()
    QFile myDownloadFile(myFullFileName);

    bool OpenStatus = false;
    if(!AppendStatus)
    {
        OpenStatus = myDownloadFile.open(QIODevice::WriteOnly);
        AppendStatus = true;
    }
    else
    {
        OpenStatus = myDownloadFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    if(!OpenStatus)
    {
        qDebug() << "打开失败---" << myFullFileName;
    }
    myDownloadFile.write(myNetworkReply->readAll());

    myDownloadFile.close();
}

void DownloadFile::onFinished()
{
    QNetworkAccessManager *NetworkManager = static_cast<QNetworkAccessManager*>(sender());
    if(NetworkManager != NULL)
    {
        NetworkManager->deleteLater();
    }
    emit DownLoadFinished(myFullFileName, relativeName_);

//    qDebug() << QThread::currentThreadId() << "DownFinished---myFullFileName = " << myFullFileName << ",relativeName_ = " << relativeName_;
    //    myDebug()
}

void DownloadFile::OnError(QNetworkReply::NetworkError err)
{
    emit DownLoadError(myFullFileName, relativeName_, err);
}
