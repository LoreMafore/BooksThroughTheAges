//
// Created by Conrad Mercer on 5/7/2025.
//

#include "BookSearchWindow.h"
#include "BookCard.h"
#include <QLine>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QScrollArea>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

Book_Search_Window::Book_Search_Window(QWidget *parent) : QDialog(parent){
    setWindowTitle("New Book");
    setModal(true);
    setFixedSize(600,500);

    main_layout = new QVBoxLayout(this);
    QHBoxLayout *search_layout = new QHBoxLayout();

    search_text_box = new QLineEdit(this);
    search_text_box->setPlaceholderText("Enter book title to search");
    search_layout->addWidget(search_text_box,1);


    QPushButton *search_button = new QPushButton("Search", this);
    connect(search_button, &QPushButton::clicked, this, &Book_Search_Window::on_search_clicked);
    search_layout->addWidget(search_button);

    main_layout->addLayout(search_layout);

    status_label = new QLabel(this);
    status_label->setAlignment(Qt::AlignCenter);
    status_label->setWordWrap(true);
    main_layout->addWidget(status_label);

    //create scroll area for search results
    scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //create widget to hold scroll content
    scroll_content = new QWidget(scroll_area);
    scroll_layout = new QVBoxLayout(scroll_content);
    scroll_layout->setAlignment(Qt::AlignTop);
    scroll_content->setLayout(scroll_layout);

    //set scroll content as the widget for scroll area
    scroll_area->setWidget(scroll_content);

    //add scroll area to main layout
    main_layout->addWidget(scroll_area,1);
    QHBoxLayout *buttons_layout = new QHBoxLayout();
    buttons_layout->addStretch(1);

    select_button = new QPushButton("Select Book", this);
    select_button->setEnabled(false);
    connect(select_button, &QPushButton::clicked, this, &QDialog::accept);
    buttons_layout->addWidget(select_button);

    main_layout->addLayout(buttons_layout);

    QPushButton *new_book = new QPushButton("Add New Book", this);
    main_layout->addWidget(new_book);

    setLayout(main_layout);

    network_manager = new QNetworkAccessManager(this);

}

void Book_Search_Window::on_search_clicked() {

    QString search_text = search_text_box->text().trimmed();

    if(search_text.isEmpty()){
        status_label->setText("Please enter a book title to search");
        status_label->setStyleSheet("color: black;");
        return;
    }

    clear_search_results();

    status_label->setText("Searching for books...");
    status_label->setStyleSheet("color: black;");

    QUrl url("http://openlibrary.org/search.json");
    QUrlQuery query;
    query.addQueryItem("title", search_text);
    query.addQueryItem("limit", "10");
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply *reply = network_manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply](){
        if(reply->error() != QNetworkReply::NoError){
            status_label->setText("Error: " + reply->errorString());
            status_label->setStyleSheet("color: red;");
            reply->deleteLater();
            return;
        }

        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();

        //number of results
        int num_found = json["numFound"].toInt();

        if(num_found == 0){
            status_label->setText("No books found");
            status_label->setStyleSheet("color: black;");
            reply->deleteLater();
            return;
        }

        QJsonArray docs = json["docs"].toArray();

        status_label->setText(QString("Found %1 books. Showing top %2 results:").arg(num_found).arg(docs.size()));
        status_label->setStyleSheet("color: black;");

        for(const QJsonValue &doc : docs){
            QJsonObject book = doc.toObject();

            QString title = book["title"].toString();

            QString author = "Unknown Author";
            if (book.contains("author_name") && book["author_name"].isArray()) {
                QJsonArray authors = book["author_name"].toArray();
                if (!authors.isEmpty()) {
                    author = authors[0].toString();
                    // If multiple authors, add "et al."
                    if (authors.size() > 1) {
                        author += " et al.";
                    }
                }
            }

            QString cover_id;
            if(book.contains("cover_i")){
                cover_id = QString::number(book["cover_i"].toInt());
            }

            QString book_id;
            if (book.contains("key")) {
                book_id = book["key"].toString();
            }

            else if (book.contains("edition_key") && book["edition_key"].isArray()) {
                QJsonArray editions = book["edition_key"].toArray();
                if (!editions.isEmpty()) {
                    book_id = editions[0].toString();
                }
            }

            if (!book_id.isEmpty()) {
                BookCard *card = new BookCard(title, author, cover_id, book_id, scroll_content);
                connect(card, &BookCard::book_selected, this, &Book_Search_Window::on_book_selected);
                scroll_layout->addWidget(card);
            }

        }

        reply->deleteLater();
    });

}

void Book_Search_Window::on_book_selected(const QString &book_id) {
    selected_book_id = book_id;
    select_button->setEnabled(true);

    for (int i = 0; i < scroll_layout->count(); ++i) {
        QWidget *widget = scroll_layout->itemAt(i)->widget();
        BookCard *card = qobject_cast<BookCard*>(widget);

        if (card) {
            if (card->book_id == book_id) {
                card->setStyleSheet("BookCard { background-color: #e6f2ff; border: 2px solid #3399ff; border-radius: 5px; margin: 5px; padding: 10px; }");
            } else {
                card->setStyleSheet("BookCard { background-color: #ffffff; border: 1px solid #dddddd; border-radius: 5px; margin: 5px; padding: 10px; }");
            }
        }
    }
}

void Book_Search_Window::clear_search_results() {
    selected_book_id.clear();
    select_button->setEnabled(false);

    QLayoutItem *item;
    while((item = scroll_layout->takeAt(0)) != nullptr){
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }
}
