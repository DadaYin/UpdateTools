#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H

#include <QObject>

class ConnectThread : public QObject
{
    Q_OBJECT
public:
    explicit ConnectThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONNECTTHREAD_H
