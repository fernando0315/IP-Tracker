#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->countryRespLabel->setText("-");
    ui->IPRespLabel->setText("-");
    ui->emailRespLabel->setText("-");
    ui->hostRespLabel->setText("-");
    ui->ISPRespLabel->setText("-");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_trackIPButton_clicked()
{
    QString ipAddress = ui->IPInput->text();

    QString response = sendRequest(ipAddress);
    QRegExp rx("\\,");
    QStringList respQuery = response.split(rx);

    ui->countryRespLabel->setText(respQuery[8]);
    ui->IPRespLabel->setText(respQuery[0]);
    ui->emailRespLabel->setText(respQuery[9]);
    ui->hostRespLabel->setText(respQuery[2]);
    ui->ISPRespLabel->setText(respQuery[5]);
}

QString MainWindow::sendRequest(QString ipAddress){

    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://freegeoip.net/csv/") + ipAddress ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    QString response;
    if (reply->error() == QNetworkReply::NoError) {
        //success
        response = reply->readAll();
        qDebug() <<  response;
        delete reply;
    }
    else {
        //failure
        response = reply->errorString();
        delete reply;
    }

    return response;
}
