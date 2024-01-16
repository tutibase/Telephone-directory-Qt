#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList{"name", "address", "date of birth"," email", "phone number"});
    ui->tableWidget->setSortingEnabled(true);

    ui->tableWidget->setItemPrototype(new myTableWidgetItem());
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    this->setWindowFlags( this->windowFlags() |  Qt::MSWindowsFixedSizeDialogHint );

    tmpCellStr = "";
    connect(ui->tableWidget, SIGNAL(cellPressed(int,int)), this, SLOT(cellSaver(int,int)));
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(cellChecker(int,int)));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    while (!selectedRows.empty()) {
        ui->tableWidget->removeRow(selectedRows[0].row());
        selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    }
}


void MainWindow::on_addButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int rows = ui->tableWidget->rowCount()-1;

    for (int i = 0; i<ui->tableWidget->columnCount(); i++){
        if (i == 2) continue;
        myTableWidgetItem* tmpItem = new myTableWidgetItem("");
        ui->tableWidget->setItem(rows, i, tmpItem);
    }

    QDateEdit* dateEdit = new QDateEdit();
    dateEdit->setMaximumDate(QDate::currentDate());
    dateEdit->setMinimumDate(QDate(1900, 1, 1));
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setDisplayFormat("yyyy.MM.dd");


    ui->tableWidget->setCellWidget(rows, 2, dateEdit);
    QDate tmp = dateEdit->date();

    myTableWidgetItem* tmpItem = new myTableWidgetItem(dateToString(tmp));
    ui->tableWidget->setItem(rows, 2, tmpItem);

    connect(dateEdit, SIGNAL(dateChanged(QDate)), tmpItem, SLOT(setTextSlot(QDate)));
}

// Необходимо заменить путь к файлу на собственный
void MainWindow::on_writeButton_clicked()
{
    QFile file("C:/Qt/projects/lab8_3sem/datebase1.txt");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not found");
    }

    QTextStream out(&file);
    QString text;
    bool empty;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        text = "";
        empty = 1;
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            if (j != 2){
                QTableWidgetItem *tmp = ui->tableWidget->item(i, j);

                if (nullptr != tmp) {
                    text += tmp->text() + ',';
                    if (tmp->text() != "") empty = 0;
                }
                else text += ',';
            } else {
                QDate tmp = (qobject_cast<QDateEdit*>(ui->tableWidget->cellWidget(i,j)))->date();
                text += QString::number(tmp.year()) + ',' + QString::number(tmp.month())
                        + ',' + QString::number(tmp.day()) + ',';
            }
        }

        text += '\n';
        if (empty) text = "";
        out << text;
    }


    file.flush();
    file.close();
}

// Необходимо заменить путь к файлу на собственный
void MainWindow::on_readButton_clicked()
{
    QFile file("C:/Qt/projects/lab8_3sem/datebase1.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not found");
    }

    QTextStream in(&file);
    int i = 0;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSortingEnabled(false);

    while (!in.atEnd()) {
        on_addButton_clicked();

        int flag = 0;
        QString text = in.readLine();
        QStringList list = text.split(u',');

        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            if (j != 2) {
                myTableWidgetItem *tmp = new myTableWidgetItem(list[j + flag]);
                ui->tableWidget->setItem(i, j, tmp);

            } else {
                QDateEdit *DateEdit = qobject_cast<QDateEdit*>(ui->tableWidget->cellWidget(i,j));
                DateEdit->setDisplayFormat("yyyy.MM.dd");
                DateEdit->setDate(QDate((list[j]).toInt(), (list[j + 1]).toInt(), (list[j + 2]).toInt()));
                flag = 2;
                myTableWidgetItem *tmp = new myTableWidgetItem(dateToString(DateEdit->date()));
                ui->tableWidget->setItem(i, j, tmp);

                connect(DateEdit, SIGNAL(dateChanged(QDate)), tmp, SLOT(setTextSlot(QDate)));
            }
        }

        i++;
    }

    file.close();
    ui->tableWidget->setSortingEnabled(true);
}


void MainWindow::on_searchButton_clicked() {
    ui->tableWidget->clearSelection();

    if (ui->lineEdit->text() == "") return;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            if (ui->tableWidget->item(i, j) == 0) continue;

            if (ui->tableWidget->item(i, j)->text().toLower().indexOf(ui->lineEdit->text().toLower()) != -1) {
                ui->tableWidget->selectionModel()->select(ui->tableWidget->model()->index(i, j),
                                                          QItemSelectionModel::Select | QItemSelectionModel::Rows);
            }
        }
    }

}


void MainWindow::cellChecker(int row, int col) {
    if (col == 2 or col == 1) return;

    QString cellText = ui->tableWidget->item(row, col)->text();
    if (cellText == "") return;
    bool flag = 0;

    if (col == 0) flag = isValidName(cellText);
    if (col == 3) flag = isValidEmail(cellText);
    if (col == 4) flag = isValidPhone(cellText);

    if (!flag) ui->tableWidget->item(row, col)->setText(tmpCellStr);
}

void MainWindow::cellSaver(int row, int col) {
    if (col == 2 or col == 1) return;
    tmpCellStr = ui->tableWidget->item(row, col)->text();
}

QString dateToString(QDate date) {
    QString year =  QString::number(date.year());
    QString month = QString::number(date.month());
    QString day = QString::number(date.day());

    if (month.size() == 1) month = "0" + month;
    if (day.size() == 1) day = "0" + day;

    return year + "." + month + "." + day;
}

