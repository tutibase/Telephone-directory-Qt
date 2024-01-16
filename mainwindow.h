#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QRegularExpression>
#include "mytablewidgetitem/mytablewidgetitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QString dateToString(QDate date);


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_deleteButton_clicked();
    void on_addButton_clicked();
    void on_writeButton_clicked();
    void on_readButton_clicked();
    void on_searchButton_clicked();

    void cellChecker(int row, int col);
    void cellSaver(int row, int col);

private:
    Ui::MainWindow *ui;
    QString tmpCellStr;
};
#endif // MAINWINDOW_H
