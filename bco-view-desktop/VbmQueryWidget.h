#ifndef VBMQUERYWIDGET_H
#define VBMQUERYWIDGET_H

#include <QWidget>

namespace Ui {
class VbmQueryWidget;
}

class VbmQueryInfo;
class DbController;
class VbmQueryModel;
class QSqlQueryModel;

class VbmQueryWidget : public QWidget {
    Q_OBJECT

  public:
    explicit VbmQueryWidget(QWidget* parent = 0);
    ~VbmQueryWidget();
  public slots:
    void serverConnected();
    void loadData();
    void serverDisconnected();
    void columnChanged(int index);
    void filterChanged(const QString& text);
  private:
    void loadQueries();
    void loadColumnName(QSqlQueryModel* model);
    QJsonDocument loadQueriesFromJson();
  private:
    Ui::VbmQueryWidget* ui;
    QVector<VbmQueryInfo*> m_QueryList;
    VbmQueryModel* m_QueryModel;
    DbController* m_Db;
    QString m_CurrentQuery;
};

#endif // VBMQUERYWIDGET_H
