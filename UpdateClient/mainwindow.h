#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QProgressBar;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
