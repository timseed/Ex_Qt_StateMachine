
#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QDebug>
#include <QScxmlCppDataModel>
#include <QScxmlEvent>

class DataModel :public QScxmlCppDataModel
{
    Q_OBJECT
    Q_SCXML_DATAMODEL

public:
    DataModel(QObject *parent);
    void UpdateFields(QString call, int rst, QString exchange);
    bool CallIsValid(QString s);
    bool RstIsValid(int i);
    bool ExchangeIsValid(QString s);

    QString Call;
    int Rst;
    QString Exchange;

    QString m_Descript;
    QVariant m_var;
};


#define DATAMODEL_H
#endif // DATAMODEL_H
