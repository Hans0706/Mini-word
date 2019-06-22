#include "form.h"
#include "ui_form.h"
class wordchild;
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    this->find_edit=ui->lineEdit;
    this->to_replace_edit=ui->lineEdit_2;
    this->to_find_pbutton=ui->pushButton;
    this->to_replace_pbutton=ui->pushButton_2;
    connect(to_find_pbutton,SIGNAL(clicked(bool)),this,SLOT(find_function()));
    connect(to_replace_pbutton,SIGNAL(clicked(bool)),this,SLOT(replace_fuction()));
    this->setWindowIcon(QIcon(":/pic/love.ico"));
    this->find_result=ui->tableWidget;
        this->find_result->setColumnCount(2);
        this->find_result->setRowCount(4);
        QStringList header;
        header<<"行"<<"列";
        QStringList vertical_header;
        find_result->setHorizontalHeaderLabels(header);
            find_result->setVerticalHeaderLabels(vertical_header);
            find_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
            find_result->setSelectionBehavior(QAbstractItemView::SelectRows);
}
Form::~Form()
{
    delete ui;
}
void Form::find_function()
{
    emit send_find_data(ui->lineEdit->text());
}
void Form::replace_fuction()
{
    emit send_replace_data(this->find_edit->text(),this->to_replace_edit->text());
}
