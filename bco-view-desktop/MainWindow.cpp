#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <memory>

#include "PrescriptionOrderWidget.h"
#include "PrescriptionBatchWidget.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent, DbController* dbc, QThread* dbt) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db_controller = dbc;
    db_thread = dbt;
    ui->statusBar->showMessage("Not connect");

    PrescriptionOrderWidget* prescriptionOrderWidget = new PrescriptionOrderWidget();
    PrescriptionBatchWidget* prescriptionBatchWidget = new PrescriptionBatchWidget();

    ui->gridLayout->addWidget(prescriptionOrderWidget,0,1);
    ui->gridLayout->addWidget(prescriptionBatchWidget,0,2);

    connect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    connect(this,SIGNAL(connectToServer(QString)),db_controller, SLOT(connectToServerRequested(QString)));
    connect(db_controller, SIGNAL(serverConnected()),this, SLOT(serverConnected()));
    connect(db_controller, SIGNAL(serverDisconnected()), this, SLOT(serverDisconnected()));
    connect(this, SIGNAL(disconnectFromServer()), db_controller, SLOT(disconnectFromServerRequested()));
    connect(db_controller, SIGNAL(serverErrorWithConnection(QString)), this, SLOT(serverErrorWithConnection(QString)));

    connect(prescriptionOrderWidget,&PrescriptionOrderWidget::selected,prescriptionBatchWidget,&PrescriptionBatchWidget::prescriptionOrderSelected);
}

MainWindow::~MainWindow()
{
    db_thread->exit();
    db_thread->wait();
    delete ui;
}

void MainWindow::connectToServerRequested()
{
    QString connectionString = ui->connection_string_lineEdit->text();
    ui->connect_pushButton->setEnabled(false);
    ui->connection_string_lineEdit->setEnabled(false);
    ui->statusBar->showMessage("Connecting ...");

    emit connectToServer(connectionString);
}

void MainWindow::disconnectFromServerRequested()
{
    emit disconnectFromServer();
}

void MainWindow::serverConnected()
{
    ui->statusBar->showMessage("Connected");
    ui->connect_pushButton->setEnabled(true);
    ui->connect_pushButton->setText("Disconnect");
    ui->connection_string_lineEdit->setEnabled(false);
    disconnect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    connect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(disconnectFromServerRequested()));
}

void MainWindow::serverDisconnected()
{
    disconnect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(disconnectFromServerRequested()));
    connect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    ui->connect_pushButton->setEnabled(true);
    ui->connect_pushButton->setText("Connect");
    ui->statusBar->showMessage("Not connect");
    ui->connection_string_lineEdit->setEnabled(true);
}

void MainWindow::serverErrorWithConnection(QString message)
{
    QMessageBox::critical(this,
                          "Connection failed",
                          message,
                          QMessageBox::Ok);

    ui->connect_pushButton->setEnabled(true);

    ui->statusBar->showMessage("Connection failed", 3000);
}
