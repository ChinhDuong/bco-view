#include "VbmQueryWidget.h"
#include "ui_VbmQueryWidget.h"

#include "DbController.h"
#include "VbmQueryInfo.h"
#include "VbmQueryModel.h"

#include <memory>
#include <vector>

using namespace std;
VbmQueryWidget::VbmQueryWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::VbmQueryWidget),
    m_QueryList(),
    m_QueryModel(new VbmQueryModel()),
    m_Db(&DbController::instance())
{
    ui->setupUi(this);

    connect(m_Db, &DbController::serverConnected, this, &VbmQueryWidget::serverConnected);
    connect(ui->load_pushButton, &QPushButton::clicked, this, &VbmQueryWidget::loadData);
    connect(m_Db, &DbController::serverDisconnected, this, &VbmQueryWidget::serverDisconnected);
    connect(ui->column_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &VbmQueryWidget::columnChanged);
    connect(ui->filter_lineEdit, &QLineEdit::textChanged, this, &VbmQueryWidget::filterChanged);
    loadQueries();

    if (m_Db->checkIfConnected()) {
        ui->query_comboBox->setEnabled(true);
        ui->load_pushButton->setEnabled(true);
        ui->column_comboBox->setEnabled(true);
        ui->filter_lineEdit->setEnabled(true);
    }
}

VbmQueryWidget::~VbmQueryWidget()
{
    delete ui;
}

void VbmQueryWidget::serverConnected()
{
    ui->query_comboBox->setEnabled(true);
    ui->load_pushButton->setEnabled(true);
    ui->column_comboBox->setEnabled(true);
    ui->filter_lineEdit->setEnabled(true);
}

void VbmQueryWidget::loadData()
{
    int rowIndex = ui->query_comboBox->currentIndex();
    QModelIndex queryIndex = m_QueryModel->index(rowIndex, 1, QModelIndex());

    QVariant queryData = m_QueryModel->data(queryIndex, Qt::DisplayRole);
    QString queryText = queryData.toString();

    if (!queryText.isEmpty() && !queryText.isNull()) {

        qDebug() << queryText;
        QSqlQueryModel* model = m_Db->selectTable(queryText);
        QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
        proxy->setSourceModel(model);
        delete ui->tableView->model();
        ui->tableView->setModel(proxy);

        if (m_CurrentQuery != queryText) {
            loadColumnName(model);
        }

        ui->filter_lineEdit->setEnabled(true);
        m_CurrentQuery = queryText;
    }
}

void VbmQueryWidget::serverDisconnected()
{
    ui->query_comboBox->setEnabled(false);
    ui->load_pushButton->setEnabled(false);
    ui->column_comboBox->setEnabled(false);
    ui->filter_lineEdit->setEnabled(false);
}

void VbmQueryWidget::columnChanged(int index)
{
    QSortFilterProxyModel* proxy = qobject_cast<QSortFilterProxyModel*>(ui->tableView->model());
    proxy->setFilterKeyColumn(index);
}

void VbmQueryWidget::filterChanged(const QString& text)
{
    QSortFilterProxyModel* proxy = qobject_cast<QSortFilterProxyModel*>(ui->tableView->model());
    proxy->setFilterFixedString(text);
}

void VbmQueryWidget::loadQueries()
{
    QJsonDocument json = loadQueriesFromJson();
    QJsonArray jsonArr = json.array();
    unique_ptr<vector<unique_ptr<VbmQueryInfo>>> list(new vector<unique_ptr<VbmQueryInfo>>());

    for (int index = 0; index < jsonArr.size(); ++index) {
        QJsonObject jsonObj = jsonArr[index].toObject();
        QString description = jsonObj["Description"].toString();
        QString query = jsonObj["Query"].toString();
        unique_ptr<VbmQueryInfo> querytemp(new VbmQueryInfo(description, query));
        list->push_back(std::move(querytemp));
    }

    m_QueryModel->setModel(std::move(list));
    ui->query_comboBox->setModel(m_QueryModel);
}

void VbmQueryWidget::loadColumnName(QSqlQueryModel* model)
{
    QStringList* columnNames = new QStringList();

    for (int i = 0; i < model->columnCount(); ++i) {
        QString columnName = model->record().fieldName(i);

        //        if (!columnName.contains("Date", Qt::CaseInsensitive)) {
        //            columnNames->append(columnName);
        //        }
        columnNames->append(columnName);
    }

    QStringListModel* model2 = new QStringListModel();
    model2->setStringList(*columnNames);

    ui->column_comboBox->setModel(model2);
    ui->column_comboBox->setEnabled(true);
}

QJsonDocument VbmQueryWidget::loadQueriesFromJson()
{
    QFile jsonFile(QStringLiteral("queries.json"));
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
