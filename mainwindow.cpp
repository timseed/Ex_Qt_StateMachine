#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->f1,SIGNAL(returnPressed()),this,SLOT(OnReturnPressed()));
    connect(ui->f2,SIGNAL(returnPressed()),this,SLOT(OnReturnPressed()));
    connect(ui->f3,SIGNAL(returnPressed()),this,SLOT(OnReturnPressed()));

    m_stateMachine = QScxmlStateMachine::fromFile(":/QsoEx.scxml");
    for(QScxmlError& error:m_stateMachine->parseErrors())
    {
        qDebug()<<error.description();
    }


    // Connect up the States
    // We have 3 States... Call Rst Exchange
    m_stateMachine->connectToState("Call", this, &MainWindow::onCallState);
    m_stateMachine->connectToState("Rst", this, &MainWindow::onRstState);
    m_stateMachine->connectToState("Exchange", this, &MainWindow::onExchangeState);
    // We have 3 Events which move us between each State
    m_stateMachine->connectToEvent("gotCall", this, &MainWindow::ongotCallEvent);
    m_stateMachine->connectToEvent("gotRst", this, &MainWindow::ongotRstEvent);
    m_stateMachine->connectToEvent("gotExchange", this, &MainWindow::ongotExchangeEvent);

    datamodel = new DataModel(this);

    m_stateMachine->setDataModel(datamodel);
    m_stateMachine->init();
    m_stateMachine->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCallState(bool isActive)
{

    qDebug() << "Call Active";

}

void MainWindow::onRstState(bool isActive)
{

    qDebug() << "Rst Active";

}

void MainWindow::onExchangeState(bool isActive)
{
    qDebug() << "Exchange Active";

}

void MainWindow::ongotCallEvent(const QScxmlEvent &event)
{
    qDebug() << "Call Event called";

}

void MainWindow::ongotRstEvent(const QScxmlEvent &event)
{
    qDebug() << "Rst Event called";
}

void MainWindow::ongotExchangeEvent(const QScxmlEvent &event)
{
    qDebug() << "Ex Event Called";
}

void MainWindow::OnReturnPressed()
{
    QString curState = m_stateMachine->activeStateNames()[0];
    qDebug() << "On Return Pressed Triggered";
    qDebug() << "Current State is " + curState;
    if (curState == "Call")
    {
        qDebug() << "We are in Call State. Checking Call";
        // We can move from call to rst is we have a valid call
        if (datamodel->CallIsValid(ui->f1->text()))
        {
            qDebug() << "Data Is Valid";
            QVariant var = QVariant(ui->f1->text());
            m_stateMachine->submitEvent("gotCall", var);
            ui->f2->setFocus();
        }
        else
        {
            ui->f1->setFocus();
        }
    }
    if (curState == "RST")
    {
        if (datamodel->RstIsValid(QString(ui->f2->text()).toInt()))
        {
            QVariant var = QVariant(ui->f1->text());
            m_stateMachine->submitEvent("gotRst", QVariant("Rst"));
            ui->f3->setFocus();
        }
        else
        {
            ui->f2->setFocus();
        }
    }
    if (curState == "Exchange")
    {
        if (datamodel->ExchangeIsValid(ui->f3->text()))
        {
            QVariant var = QVariant(ui->f1->text());
            m_stateMachine->submitEvent("gotExchange", QVariant("Rst"));
            ui->f1->setFocus();
        }
        else
        {
            ui->f3->setFocus();
        }
    }


    ui->label->setText("State "+m_stateMachine->activeStateNames()[0]);
}

