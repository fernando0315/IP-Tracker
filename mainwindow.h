#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_trackIPButton_clicked();

private:
    Ui::MainWindow *ui;

    QString sendRequest(QString);
};

#endif // MAINWINDOW_H
