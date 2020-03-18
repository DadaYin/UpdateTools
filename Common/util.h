#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QDebug>

#define myDebug()    qDebug() << QObject::tr("文件名: ") <<  __FILE__ << QObject::tr("行号: ")<<  __LINE__ << QObject::tr("函数名: ") <<  __FUNCTION__;

#include <stdio.h>

#ifdef SHINEDEBUG
        #define SHINE_dputs(str) do{ printf("%s %s %d: %s\n", __FILE__, __func__, __LINE__, str); }while(0);
        #define SHINE_dprintf(fmt, args...) do{ printf("%s, %s, %d: 'fmt'\n", __FILE__, __func__, __LINE__, ##args); }while(0);
#else
        #define SHINE_dputs(str) do{}while(0);
        #define SHINE_dprintf(fmt, args...) do{}while(0);
#endif

#endif // UTIL_H
