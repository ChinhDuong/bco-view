#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <memory>
#include "VbmTableWidget.h"
#include "VbmQueryWidget.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent, DbController* dbc, QThread* dbt) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mTables(), mQueries(), mColumnCount(3)
{
    ui->setupUi(this);

    db_controller = dbc;
    db_thread = dbt;
    ui->statusBar->showMessage("Not connect");

    connect(ui->connect_pushButton, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    connect(this, SIGNAL(connectToServer(QString)), db_controller,
            SLOT(connectToServerRequested(QString)));
    connect(db_controller, SIGNAL(serverConnected()), this, SLOT(serverConnected()));
    connect(db_controller, SIGNAL(serverDisconnected()), this, SLOT(serverDisconnected()));
    connect(this, SIGNAL(disconnectFromServer()), db_controller, SLOT(disconnectFromServerRequested()));
    connect(db_controller, SIGNAL(serverErrorWithConnection(QString)), this,
            SLOT(serverErrorWithConnection(QString)));

    connect(ui->add_pushButton, &QPushButton::clicked, this, &MainWindow::addView);

    QJsonDocument connections =  loadConnections();
    QJsonArray connectionArr = connections.array();


    for (int i = 0; i < connectionArr.size(); ++i) {
        QString connection = connectionArr[i].toString();
        ui->connections_comboBox->addItem(connection);
    }

}

MainWindow::~MainWindow()
{
    db_thread->exit();
    db_thread->wait();
    delete ui;
}

void MainWindow::connectToServerRequested()
{
    QString connectionString = ui->connections_comboBox->currentText();
    ui->connect_pushButton->setEnabled(false);
    ui->connections_comboBox->setEnabled(false);
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
    ui->connections_comboBox->setEnabled(false);
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
    ui->connections_comboBox->setEnabled(true);
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

void MainWindow::addView()
{
    int tabIndex = ui->tabWidget->currentIndex();

    if (tabIndex == 0) {
        int count = mTables.count();
        float num = (float)count / mColumnCount;
        int row = (int)floorf(num);
        int col = ((num - row) / mColumnCount) * 10;

        VbmTableWidget* widget = new VbmTableWidget(this);
        mTables.append(widget);
        ui->table_gridLayout->addWidget(widget, row, col);
    } else if (tabIndex == 1) {
        int count = mQueries.count();
        float num = (float)count / mColumnCount;
        int row = (int)floorf(num);
        int col = ((num - row) / mColumnCount) * 10;

        VbmQueryWidget* widget = new VbmQueryWidget(this);
        mQueries.append(widget);
        ui->query_gridLayout->addWidget(widget, row, col);
    }

}

QJsonDocument MainWindow::loadConnections()
{
    QFile jsonFile(QStringLiteral("connections.json"));
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
