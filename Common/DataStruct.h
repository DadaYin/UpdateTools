#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <QString>
#include <QList>

typedef enum ErrorCodeTag{
    Err_NoErr,
    Err_NoFile
}ErrorCode;

typedef struct BasicInfoTag{
    QString HttpRootUrl;
    QString MainVersion;
    QString UpdateDir;
}BasicInfo;

typedef struct ClientBasicInfoTag{
    QString HttpRootUrl;
    QString UpdateDir;
    QString TmpUpdateDir;
}ClientBasicInfo;

typedef struct OneUpdateFileInfoTag{
    QString RelativeName;
    QString LatestVersion;
    QString MD5;
    QString Url;
    QString ReleaseNote;
}OneUpdateFileInfo;

typedef struct UpdateJsonInfoTag{
    QString MainVersion;

    int DescribeSize;
    QList<QString> Describe;

    int FileSize;
    QList<OneUpdateFileInfo> UpdateFileInfoList;
}UpdateJsonInfo;
#endif // DATASTRUCT_H
