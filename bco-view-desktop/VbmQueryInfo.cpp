#include "VbmQueryInfo.h"

VbmQueryInfo::VbmQueryInfo(QString description, QString query):
    m_Description(description),
    m_Query(query)
{

}

QString VbmQueryInfo::description() const
{
    return m_Description;
}

QString VbmQueryInfo::query() const
{
    return m_Query;
}
