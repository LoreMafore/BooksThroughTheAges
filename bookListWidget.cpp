#include "bookListWidget.h"

#include <QBuffer>
#include <QNetworkReply>

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
        manager = new QNetworkAccessManager(this);
        QUrl cover_url(QString("http://covers.openlibrary.org/b/id/%1-M.jpg").arg(bookInfo["cover_id"]));
        QNetworkRequest request(cover_url);
        cover_reply = manager->get(request);
        connect(cover_reply, &QNetworkReply::finished, this, &bookListWidget::loadCover);
    }
    else
    {
        ui->coverLbl->setText("No\nCover");
        ui->coverLbl->setStyleSheet( "background-color: white; border: 1px solid black;");
    }

}

void bookListWidget::loadCover()
{
   if (cover_reply->error() == QNetworkReply::NoError)
   {
       QByteArray cover_data = cover_reply->readAll();

       QImage coverJpeg;
       if(coverJpeg.loadFromData(cover_data))
       {
           QByteArray coverPng;
           QBuffer buffer(&coverPng);
           buffer.open(QIODevice::WriteOnly);
           coverJpeg.save(&buffer, "PNG");
           buffer.close();

           QPixmap cover_pixmap;
           if(cover_pixmap.loadFromData(coverPng))
           {
               //cover_pixmap
           }
       }
   }
}
