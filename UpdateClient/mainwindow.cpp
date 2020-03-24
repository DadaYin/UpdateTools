#include "mainwindow.h"
#include "updatewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    UpdateWidget* updateWidget = new UpdateWidget;
    this->setCentralWidget(updateWidget);
}

MainWindow::~MainWindow()
{
}

//void MainWindow::OnGetJsonBtnClicked()
//{
//    DownloadJsonFile();
//}

//void MainWindow::OnDownLoadFinished(QString fullFileName, QString relativeName)
//{
//    AppendTextStr("下载\t" + relativeName + "\t结束");
//    if(relativeName == "update.json")
//    {
//        if(!JsonDownLoadStatus_)
//        {
//            JsonDownLoadStatus_ = true;
//            StartDownLoad();
//        }
//        else
//        {
//            if(curDownLoadFile_ == relativeName)
//            {
//                downLoadFileList_.remove(relativeName);
//            }
//            myDebug()
//                    qDebug() << "downLoadFileList_.size(); = " << downLoadFileList_.size();
//            if(downLoadFileSize_ == 0)
//            {
//                StartCheckMD5();
//            }
//            else
//            {
//                StartDownLoadOneFile();
//            }
//        }
//    }
//    else
//    {
//        if(downLoadFileSize_ != 0)
//        {
//            processBar_->setRange(0, downLoadFileSize_);

//            processBar_->setValue(downLoadFileSize_ - downLoadFileList_.size());
//            double processData = (processBar_->value() - processBar_->minimum());
//            qDebug() << "processData = " << processData;
//            processBar_->setFormat(QString::fromUtf8("升级进度:%1%").arg(QString::number(processData, 'f', 2)));

//        }

//        if(curDownLoadFile_ == relativeName)
//        {
//            downLoadFileList_.remove(relativeName);
//        }
//        if(downLoadFileList_.size() != 0)
//        {
//            StartDownLoadOneFile();
//        }
//        else
//        {
//            StartCheckMD5();
//        }
//    }
//}

//void MainWindow::OnTextChanged()
//{
//    textEdit_->moveCursor(QTextCursor::End);
//}

//void MainWindow::Init()
//{
//    mainWidget_ = new QWidget;

//    rootUrlLabel_ = new QLabel("升级根目录地址");
//    rootUrlEdit_ = new QLineEdit;
//    getJsonBtn_ = new QPushButton("开始获取jso文件");

//    textEdit_ = new QTextEdit;

//    processBar_ = new QProgressBar;
//}

//void MainWindow::InitLayout()
//{
//    QHBoxLayout* rootUrlLayout = new QHBoxLayout;
//    rootUrlLayout->addWidget(rootUrlLabel_);
//    rootUrlLayout->addWidget(rootUrlEdit_);
//    rootUrlLayout->addWidget(getJsonBtn_);

//    QVBoxLayout* mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(rootUrlLayout);
//    mainLayout->addWidget(textEdit_);
//    mainLayout->addWidget(processBar_);

//    mainWidget_->setLayout(mainLayout);

//    this->setCentralWidget(mainWidget_);
//}

//void MainWindow::InitConnector()
//{
//    connect(getJsonBtn_, SIGNAL(clicked()), this, SLOT(OnGetJsonBtnClicked()));
//    connect(textEdit_, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));
//}

//void MainWindow::InitData()
//{
//    IniGenParser iniGenParser;
//    clientBasicInfo_ = iniGenParser.GetBasicInfo();

//    rootUrlEdit_->setText(clientBasicInfo_.HttpRootUrl);

//    QDir dir(clientBasicInfo_.TmpUpdateDir);
//    if(!dir.exists())
//    {
//        dir.mkpath(clientBasicInfo_.TmpUpdateDir);
//    }
//    curDownLoadFile_ = "";
//    downLoadFileSize_ = 0;
//    downLoadFileList_.clear();
//    CheckMD5FileList_.clear();
//    JsonDownLoadStatus_ = false;
//}

//bool MainWindow::DownloadJsonFile()
//{
//    AppendTextStr("开始下载update.json");

//    QString rootUrl = rootUrlEdit_->text();

//    QString jsonFileUrl = rootUrl + "update.json";

//    DownloadFile* down = new DownloadFile;
//    down->DownloadFromUrl(clientBasicInfo_.TmpUpdateDir, jsonFileUrl, "update.json");
//    connect(down, SIGNAL(DownLoadFinished(QString, QString)), this, SLOT(OnDownLoadFinished(QString, QString)));

//    return true;
//}

//int MainWindow::GetJsonContent(const QString &_fileName, UpdateJsonInfo &_jsonInfo, ErrorCode &_err)
//{
//    JsonGenParser jsonGenParse;
//    bool result = jsonGenParse.ParseUpdateJson(_fileName, _jsonInfo);
//    if(!result)
//    {
//        _err = Err_NoFile;
//        return -1;
//    }
//    return 1;
//}

//int MainWindow::CompareUpdateJson(const UpdateJsonInfo &_jsonInfo1, const UpdateJsonInfo &_jsonInfo2, QList<OneUpdateFileInfo> &_fileInfoList)
//{
//    //    _jsonInfo1 url里的json文件
//    //    _jsonInfo2 本地保存的json文件
//    //    理论上url里的json数据是正确的，本地的json数据可能没有

//    if(_jsonInfo1.MainVersion == _jsonInfo2.MainVersion)
//    {
//        return -1;
//    }

//    QMap<QString, OneUpdateFileInfo> info1FileMap;
//    QMap<QString, OneUpdateFileInfo> info2FileMap;

//    GetFileMapFromList(_jsonInfo1.UpdateFileInfoList, info1FileMap);
//    GetFileMapFromList(_jsonInfo2.UpdateFileInfoList, info2FileMap);

//    QMapIterator<QString, OneUpdateFileInfo> iter(info1FileMap);
//    while (iter.hasNext())
//    {
//        iter.next();
//        QString key = iter.key();
//        OneUpdateFileInfo oneUrlInfo = iter.value();

//        if(!info2FileMap.contains(key))
//        {
//            _fileInfoList.push_back(oneUrlInfo);
//        }
//        else
//        {
//            OneUpdateFileInfo oneCurInfo = info2FileMap.value(key);
//            if(oneUrlInfo.MD5 != oneCurInfo.MD5)
//            {
//                _fileInfoList.push_back(oneUrlInfo);
//            }
//        }
//    }
//    return 1;
//}

//int MainWindow::GetFileMapFromList(const QList<OneUpdateFileInfo> &_fileInfoList, QMap<QString, OneUpdateFileInfo> &_fileInfoMap)
//{
//    for(int i=0; i<_fileInfoList.size(); i++)
//    {
//        OneUpdateFileInfo oneInfo = _fileInfoList[i];
//        _fileInfoMap[oneInfo.RelativeName] = oneInfo;
//    }
//    return 1;
//}

//void MainWindow::StartDownLoad()
//{
//    UpdateJsonInfo urlJsonInfo;
//    UpdateJsonInfo curJsonInfo;
//    ErrorCode err;
//    GetJsonContent(clientBasicInfo_.TmpUpdateDir + "update.json", urlJsonInfo, err);
//    GetJsonContent(clientBasicInfo_.UpdateDir + "update.json", curJsonInfo, err);

//    QList<OneUpdateFileInfo> updateileist;
//    CompareUpdateJson(urlJsonInfo, curJsonInfo, updateileist);

//    for(int i=0;i<updateileist.size(); i++)
//    {
//        OneUpdateFileInfo oneInfo = updateileist[i];
//        downLoadFileList_[oneInfo.RelativeName] = oneInfo;
//        CheckMD5FileList_[oneInfo.RelativeName] = oneInfo;
//    }
//    //    downLoadFileList_ = jsonInfo.UpdateFileInfoList;
//    downLoadFileSize_ = downLoadFileList_.size();

//    qDebug() << "downLoadFileList_Size = " << downLoadFileList_.size();

//    StartDownLoadOneFile();
//}

//void MainWindow::StartDownLoadOneFile()
//{
//    if(downLoadFileList_.size() <=0)
//    {
//        return;
//    }
//    OneUpdateFileInfo oneInfo = downLoadFileList_.first();

//    DownloadFile* down = new DownloadFile;

//    QFileInfo oneFileInfo(clientBasicInfo_.TmpUpdateDir + oneInfo.RelativeName);
//    qDebug() << clientBasicInfo_.TmpUpdateDir + oneInfo.RelativeName;
//    QString DirStr = oneFileInfo.absolutePath();
//    QDir dir(DirStr);
//    if(!dir.exists())
//    {
//        dir.mkpath(DirStr);
//    }

//    down->DownloadFromUrl(clientBasicInfo_.TmpUpdateDir, oneInfo.Url, oneInfo.RelativeName);
//    connect(down, SIGNAL(DownLoadFinished(QString, QString)), this, SLOT(OnDownLoadFinished(QString, QString)));
//    curDownLoadFile_ = oneInfo.RelativeName;

//    AppendTextStr("开始下载" + curDownLoadFile_);

//}

//void MainWindow::AppendTextStr(QString str)
//{
//    QString originStr = textEdit_->toPlainText();
//    originStr += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") + "---" + str + "\n";
//    textEdit_->setText(originStr);
//}

//void MainWindow::StartCheckMD5()
//{
//    AppendTextStr("***************************");
//    AppendTextStr("下载完成");
//    AppendTextStr("***************************");
//    AppendTextStr("开始校验---");

//    bool CheckMD5Result = CheckMD5(clientBasicInfo_.TmpUpdateDir, CheckMD5FileList_);
//    if(!CheckMD5Result)
//    {
//        AppendTextStr("---------------------------");
//        AppendTextStr("校验失败");
//        AppendTextStr("---------------------------");
//    }
//    else
//    {
//        AppendTextStr("***************************");
//        AppendTextStr("校验成功");
//        AppendTextStr("***************************");

//        bool copyStatus = copyDirectoryFiles(clientBasicInfo_.TmpUpdateDir, clientBasicInfo_.UpdateDir, true);

//        if(!copyStatus)
//        {
//            AppendTextStr("***************************");
//            AppendTextStr("覆盖文件失败");
//            AppendTextStr("***************************");
//        }
//        else
//        {
//            AppendTextStr("***************************");
//            AppendTextStr("覆盖文件成功");
//            AppendTextStr("***************************");
//        }
//    }
//}

//bool MainWindow::CheckMD5(const QString &_TmpUpdateDir, const QMap<QString, OneUpdateFileInfo> &_oneInfo)
//{
//    QMapIterator<QString, OneUpdateFileInfo> iter(_oneInfo);
//    while (iter.hasNext()) {
//        iter.next();
//        OneUpdateFileInfo oneInfo = iter.value();
//        bool CheckStatus = CheckOneMD5(_TmpUpdateDir, oneInfo);
//        if(!CheckStatus)
//        {
//            return false;
//        }
//    }
//    return true;
//}

//bool MainWindow::CheckOneMD5(const QString &_TmpUpdateDir, const OneUpdateFileInfo &_oneInfo)
//{
//    if(_oneInfo.RelativeName == "update.json")
//    {
//        return true;
//    }
//    AppendTextStr("正在校验" + _oneInfo.RelativeName);
//    QByteArray curMd5 = getFileMd5(_TmpUpdateDir + _oneInfo.RelativeName);
//    if(QString::fromUtf8(curMd5) != _oneInfo.MD5)
//    {
//        AppendTextStr(_oneInfo.RelativeName + "校验失败");
//        return false;
//    }
//    AppendTextStr(_oneInfo.RelativeName + "校验成功");
//    return true;
//}

//bool MainWindow::copyFileToPath(QString _sourceDir, QString _toDir, bool _coverFileIfExist)
//{
//    _toDir.replace("\\","/");

//    if (_sourceDir == _toDir){

//        return true;

//    }

//    if (!QFile::exists(_sourceDir)){

//        return false;

//    }

//    QDir *createfile     = new QDir;

//    bool exist = createfile->exists(_toDir);

//    if (exist){

//        if(_coverFileIfExist){

//            createfile->remove(_toDir);

//        }

//    }//end if

//    if(!QFile::copy(_sourceDir, _toDir))

//    {

//        return false;

//    }

//    return true;
//}

//bool MainWindow::copyDirectoryFiles(QString fromDir, QString toDir, bool _coverFileIfExist)
//{
//    QDir sourceDir(fromDir);

//    QDir targetDir(toDir);

//    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */

//        if(!targetDir.mkdir(targetDir.absolutePath()))

//            return false;

//    }

//    QFileInfoList fileInfoList = sourceDir.entryInfoList();

//    foreach(QFileInfo fileInfo, fileInfoList){

//        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")

//            continue;

//        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */

//            if(!copyDirectoryFiles(fileInfo.filePath(),

//                                   targetDir.filePath(fileInfo.fileName()),

//                                   _coverFileIfExist))

//                return false;

//        }

//        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */

//            if(_coverFileIfExist && targetDir.exists(fileInfo.fileName())){

//                targetDir.remove(fileInfo.fileName());

//            }

//            /// 进行文件copy

//            if(!QFile::copy(fileInfo.filePath(),

//                            targetDir.filePath(fileInfo.fileName()))){

//                return false;

//            }

//        }

//    }

//    return true;
//}

//QByteArray MainWindow::getFileMd5(const QString &_fileName)
//{
//    QFile theFile(_fileName);
//    theFile.open(QIODevice::ReadOnly);
//    QByteArray md5 = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
//    theFile.close();

//    return md5.toHex();
//}


