#ifndef FORM_H
#define FORM_H
#include<QLineEdit>
#include<QPushButton>
#include <QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
class wordchild;
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    QLineEdit * find_edit;
    QLineEdit * to_replace_edit;

    QPushButton * to_find_pbutton;
    QPushButton * to_replace_pbutton;
    QTableWidget * find_result;

private:
    Ui::Form *ui;
private slots:
    void find_function();
    void replace_fuction();
signals:
    void send_find_data(QString);
    void send_replace_data(QString,QString);

};

#endif // FORM_H
