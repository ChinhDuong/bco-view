#ifndef VBMQUERYINFO_H
#define VBMQUERYINFO_H

#include <QString>
class VbmQueryInfo {
  public:
    VbmQueryInfo(QString description, QString query);
    QString description() const;
    QString query() const;
  private:
    QString m_Description;
    QString m_Query;


};

#endif // VBMQUERYINFO_H
