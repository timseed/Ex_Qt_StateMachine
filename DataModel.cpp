#include "DataModel.h"



DataModel::DataModel(QObject *parent):
       QScxmlCppDataModel(parent)
{
    qDebug() << "Data Model Initalized";
}

void DataModel::UpdateFields(QString call, int rst, QString exchange)
{
    Call=call;
    Rst=rst;
    Exchange=exchange;
}

bool DataModel::CallIsValid(QString s)
{
    if (s.length()>4)
    {
        Call=s;
        return true;
    }
    else
        return false;
}


bool DataModel::RstIsValid(int s)
{
    if (s==599)
    {
        return true;
        Rst=s;
    }
    else
        return false;
}

bool DataModel::ExchangeIsValid(QString s)
{
    if (Call.length()>0)
    {
        Exchange=s;
        return true;
    }
    else
        return false;
}
