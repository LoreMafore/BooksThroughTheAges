#include "bookListWidget.h"
#include "ui_bookListWidget.h"


bookListWidget::bookListWidget(QWidget* parent) :
    QWidget(parent), ui(new Ui::bookListWidget)
{
    ui->setupUi(this);
    ui->coverLbl->setFixedSize(115, 180);
}

bookListWidget::~bookListWidget()
{
    delete ui;
}

void bookListWidget::configBookList(QMap<QString, QString> bookInfo)
{
    if(bookInfo.contains("author"))
    {
        ui->authLbl->setText(bookInfo["author"]);
    }

    if(bookInfo.contains("title"))
    {
        ui->titleLbl->setText(bookInfo["title"]);
    }

    if(bookInfo.contains("cover_id"))
    {
        //do cover stuff
    }

}
