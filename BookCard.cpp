//
// Created by Conrad Mercer on 5/7/2025.
//
#include "BookCard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QBuffer>

BookCard::BookCard(const QString &Title, const QString &Author, const QString &Cover, const QString &Book_id, QWidget *parent) :
        QWidget(parent), title(Title), author(Author), cover_id(Cover), book_id(Book_id){

    QHBoxLayout *main_layout = new QHBoxLayout(this);

    cover_label = new QLabel(this);
    cover_label->setFixedSize(70,100);
    cover_label->setAlignment(Qt::AlignCenter);
    cover_label->setStyleSheet("border: 1px solid black;");

    QVBoxLayout *details_layout = new QVBoxLayout();

    title_label = new QLabel(title, this);
    title_label->setStyleSheet("font-size: 14px;");
    title_label->setWordWrap(true);

    author_label = new QLabel(author, this);

    details_layout->addWidget(title_label);
    details_layout->addWidget(author_label);

    select_button = new QPushButton("Select", this);
    select_button->setFixedWidth(70);
    connect(select_button, &QPushButton::clicked, this, &BookCard::on_select_clicked);

    main_layout->addWidget(cover_label);
    main_layout->addLayout(details_layout, 1);
    main_layout->addWidget(select_button);

    setLayout(main_layout);

    //height of card
    setFixedHeight(120);
    setStyleSheet("BookCard { background-color: white; border: 1px solid black; border-radius: 5px; margin: 5px; padding: 10px; }");

    if(!cover_id.isEmpty()){
        manager = new QNetworkAccessManager(this);
        QUrl cover_url(QString("http://covers.openlibrary.org/b/id/%1-M.jpg").arg(cover_id));
        QNetworkRequest request(cover_url);
        cover_reply = manager->get(request);
        connect(cover_reply, &QNetworkReply::finished, this, &BookCard::on_cover_image_downloaded);
    }

    else{
        cover_label->setText("No\nCover");
        cover_label->setStyleSheet( "background-color: white; border: 1px solid black;");
    }
}

void BookCard::on_select_clicked() {
    emit book_selected(book_id);
}

void BookCard::on_cover_image_downloaded() {
    if(cover_reply->error() == QNetworkReply::NoError) {
        QByteArray image_data = cover_reply->readAll();
        qDebug() << "Cover data received, size:" << image_data.size() << "bytes";

        // Load the image data using QImage (which might have better JPEG support)
        QImage image;
        if(image.loadFromData(image_data)) {
            // Convert to PNG in memory
            QByteArray png_data;
            QBuffer buffer(&png_data);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PNG");
            buffer.close();

            // Now load the PNG data into a QPixmap
            QPixmap cover_pixmap;
            if(cover_pixmap.loadFromData(png_data)) {
                cover_pixmap = cover_pixmap.scaled(cover_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                cover_label->setPixmap(cover_pixmap);
                qDebug() << "Cover loaded and converted to PNG successfully";
            } else {
                qDebug() << "Failed to load PNG after conversion";
                cover_label->setText("Error\nLoading\nCover");
            }
        } else {
            qDebug() << "Failed to load image from JPEG data";
            cover_label->setText("Error\nLoading\nCover");
        }
    } else {
        qDebug() << "Cover download error:" << cover_reply->errorString();
        cover_label->setText("Error\nLoading\nCover");
    }

    cover_reply->deleteLater();
}

