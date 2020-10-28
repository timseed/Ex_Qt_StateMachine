#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScxmlStateMachine>
#include <QScxmlCppDataModel>
#include <QDebug>
#include "DataModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // These are the States

    void onCallState(bool isActive);
    void onRstState(bool isActive);
    void onExchangeState(bool isActive);

    // These are the Events
    void ongotCallEvent(const QScxmlEvent &event);
    void ongotRstEvent(const QScxmlEvent &event);
    void ongotExchangeEvent(const QScxmlEvent &event);



public slots:
    void OnReturnPressed();


private:
    Ui::MainWindow *ui;
    QScxmlStateMachine *m_stateMachine;
    DataModel *datamodel;


};
#endif // MAINWINDOW_H
