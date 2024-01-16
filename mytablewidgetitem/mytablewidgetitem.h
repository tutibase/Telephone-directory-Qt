#ifndef MYTABLEWIDGETITEM_H
#define MYTABLEWIDGETITEM_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QDate>
#include "mainwindow.h"

bool isValidEmail(QString& email);
bool isValidPhone(QString& phone);
bool isValidName(QString& name);

class myTableWidgetItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    myTableWidgetItem();
    myTableWidgetItem(QString);

signals:


public slots:
    void setTextSlot(const QDate& date);


};

#endif // MYTABLEWIDGETITEM_H
