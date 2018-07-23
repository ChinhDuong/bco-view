#include "VbmTableWidget.h"
#include "ui_VbmTableWidget.h"

#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

VbmTableWidget::VbmTableWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::VbmTableWidget),
    m_Db(&DbController::instance()),
    mCurrentTableName()
{
    ui->setupUi(this);

    connect(m_Db, &DbController::gotTablesNames, this, &VbmTableWidget::gotTablesNames);
    connect(ui->load_pushButton, &QPushButton::clicked, this, &VbmTableWidget::loadData);
    connect(m_Db, &DbController::serverDisconnected, this, &VbmTableWidget::serverDisconnected);
    connect(ui->table_comboBox, &QComboBox::currentTextChanged, this,
            &VbmTableWidget::tableNameChanged );
    ui->to_dateEdit->setDate(QDate::currentDate());
    ui->from_dateEdit->setDate(QDate(1900, 1, 1));

    if (m_Db->checkIfConnected()) {
        gotTablesNames(m_Db->getTableNames());
    }
}

VbmTableWidget::~VbmTableWidget()
{
    delete ui;
}

void VbmTableWidget::serverConnected()
{

}

void VbmTableWidget::serverDisconnected()
{
    delete ui->table_comboBox->model();
    delete ui->tableView->model();
    delete ui->column_comboBox->model();

    ui->table_comboBox->setEnabled(false);
    ui->load_pushButton->setEnabled(false);
    ui->column_comboBox->setEnabled(false);

    ui->row_count_lineEdit->setEnabled(false);
    ui->from_dateEdit->setEnabled(false);
    ui->to_dateEdit->setEnabled(false);
    ui->filter_lineEdit->setEnabled(false);
}

void VbmTableWidget::gotTablesNames(QStringList tableNames)
{
    if (tableNames.count() > 0) {
        ui->load_pushButton->setEnabled(true);
        ui->table_comboBox->setEnabled(true);

        QStringListModel* model = new QStringListModel();
        model->setStringList(tableNames);;
        ui->table_comboBox->setModel(model);
    }

}

void VbmTableWidget::loadData()
{
    QString tableName = ui->table_comboBox->currentText();

    if (!tableName.isEmpty() && !tableName.isNull()) {
        QString rowCount = ui->row_count_lineEdit->text();

        QString selectTable = QString("SELECT TOP %1 * FROM %2 WHERE 1=1 ").arg(rowCount).arg(tableName);
        QDateTime from(ui->from_dateEdit->date(), QTime(0, 0, 0, 0));

        QDateTime to(ui->to_dateEdit->date(), QTime(23, 59, 59, 999));
        QString dateFormat = "yyyy-MM-dd hh:mm:ss.zzz";
        QString fromText = from.toString(dateFormat);
        QString toText = to.toString(dateFormat);
        QString filterDate = QString(" AND DATECREATED BETWEEN \'%1\' AND \'%2\' ")
                             .arg(fromText)
                             .arg(toText);

        QString filterOther = "";

        if (ui->column_comboBox->count() > 0) {
            QString fieldName = ui->column_comboBox->currentText();
            QString fieldValue = ui->filter_lineEdit->text();

            if (!fieldValue.isEmpty()) {
                filterOther = QString(" AND %1 like '%2'").arg(fieldName).arg(fieldValue);
            }

        }

        QString query = QString("%1 %2 %3")
                        .arg(selectTable).arg(filterDate).arg(filterOther);
        qDebug() << query;
        QSqlQueryModel* model = m_Db->selectTable(query);

        delete ui->tableView->model();
        ui->tableView->setModel(model);

        if (mCurrentTableName != tableName) {
            loadColumnName(model);
        }

        ui->row_count_lineEdit->setEnabled(true);
        ui->from_dateEdit->setEnabled(true);
        ui->to_dateEdit->setEnabled(true);
        ui->filter_lineEdit->setEnabled(true);
        mCurrentTableName = tableName;
    }

}

void VbmTableWidget::tableNameChanged(const QString& name)
{
    Q_UNUSED(name);
    //    ui->load_pushButton->setEnabled(true);
}

void VbmTableWidget::loadColumnName(QSqlQueryModel* model)
{
    QStringList* columnNames = new QStringList();

    for (int i = 0; i < model->columnCount(); ++i) {
        QString columnName = model->record().fieldName(i);

        if (!columnName.contains("Date", Qt::CaseInsensitive)) {
            columnNames->append(columnName);
        }

    }

    QStringListModel* model2 = new QStringListModel();
    model2->setStringList(*columnNames);

    ui->column_comboBox->setModel(model2);
    ui->column_comboBox->setEnabled(true);
}

