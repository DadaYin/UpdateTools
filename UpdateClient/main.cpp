#include "mainwindow.h"

#include <QApplication>

#include "downloadfile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    DownloadFile downloadfile;
    downloadfile.DownloadFromUrl("/root/UpdateTool/", "http://192.168.1.10:8080/share/License/ZhangTing/License.dat", "License.dat");

    return a.exec();
}
