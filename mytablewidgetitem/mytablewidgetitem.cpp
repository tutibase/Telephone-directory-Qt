#include "mytablewidgetitem.h"

myTableWidgetItem::myTableWidgetItem() : QTableWidgetItem() {}

myTableWidgetItem::myTableWidgetItem(QString str) : QTableWidgetItem (str){}

void myTableWidgetItem::setTextSlot(const QDate& date){
    this->setText(dateToString(date));
}

bool isValidName(QString& name) {
    name = name.trimmed();
    QRegularExpression namePattern("^[A-Za-zА-Яа-яЁё]+[- ]?[A-Za-zА-Яа-яЁё]*$");
    return namePattern.match(name).hasMatch();
}

bool isValidPhone(QString& phone) {
    phone = phone.trimmed();
    QRegularExpression phonePattern("^(\\+\\d{1,3}\\(\\d{1,4}\\)\\d{1,4}-\\d{1,9};)+$");
    return phonePattern.match(phone).hasMatch();
}

bool isValidEmail(QString& email) {
    email = email.trimmed();
    QRegularExpression emailPattern(R"(^[A-Za-z0-9._]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return emailPattern.match(email).hasMatch();
}
