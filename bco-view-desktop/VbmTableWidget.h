#ifndef VBMTABLEWIDGET_H
#define VBMTABLEWIDGET_H

#include <QWidget>
#include "DbController.h"

namespace Ui {
class VbmTableWidget;
}

class VbmTableWidget : public QWidget {
    Q_OBJECT

  public:
    explicit VbmTableWidget(QWidget* parent = 0);
    ~VbmTableWidget();
  public slots:
    void serverConnected();
    void serverDisconnected();
    void gotTablesNames(QStringList tableNames);
    void loadData();
    void tableNameChanged(const QString& name);
  private:
    Ui::VbmTableWidget* ui;
    DbController* m_Db;
    QString mCurrentTableName;
  private:
    void loadColumnName(QSqlQueryModel*);
};

#endif // VBMTABLEWIDGET_H
