#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataStruct.h"

class QLabel;
class QPushButton;
class QProgressBar;
class QLineEdit;
class QWidget;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//    void OnGetJsonBtnClicked();
//    void OnDownLoadFinished(QString fullFileName, QString relativeName);
//    void OnTextChanged();


//private:
//    void Init();
//    void InitLayout();
//    void InitConnector();

//    void InitData();

//private:
//    bool DownloadJsonFile();
//    int GetJsonContent(const QString& _fileName, UpdateJsonInfo& _jsonInfo, ErrorCode& _err);
//    int CompareUpdateJson(const UpdateJsonInfo& _jsonInfo1, const UpdateJsonInfo& _jsonInfo2, QList<OneUpdateFileInfo>& _fileInfoList);

//    int GetFileMapFromList(const QList<OneUpdateFileInfo>& _fileInfoList, QMap<QString, OneUpdateFileInfo>& _fileInfoMap);

//    void StartDownLoad();
//    void StartDownLoadOneFile();

//    void AppendTextStr(QString str);

//    void StartCheckMD5();
//    bool CheckMD5(const QString& _TmpUpdateDir, const QMap<QString, OneUpdateFileInfo>& _oneInfo);
//    bool CheckOneMD5(const QString& _TmpUpdateDir, const OneUpdateFileInfo& _oneInfo);

//    bool copyFileToPath(QString _sourceDir ,QString _toDir, bool _coverFileIfExist);
//    bool copyDirectoryFiles(QString _TmpUpdateDir, QString _UpdateDir, bool _coverFileIfExist);

//    QByteArray getFileMd5(const QString& _fileName);

//private:

//    QWidget* mainWidget_;
//    QLabel* rootUrlLabel_;
//    QLineEdit* rootUrlEdit_;
//    QPushButton* getJsonBtn_;

//    QTextEdit* textEdit_;

//    QProgressBar* processBar_;

//private:
//    QMap<QString, OneUpdateFileInfo> downLoadFileList_;
//    QMap<QString, OneUpdateFileInfo> CheckMD5FileList_;

//    QString curDownLoadFile_;
//    int downLoadFileSize_;

//    ClientBasicInfo clientBasicInfo_;
//private:
//    bool JsonDownLoadStatus_;//一个升级包里只有一个update.json。防止发生冲突。默认为false，下在一次update.json后，值为true
};
#endif // MAINWINDOW_H
