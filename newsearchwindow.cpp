#include "newsearchwindow.h"
#include "bookListWidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include "ui_bookListWidget.h"
// #include "cmake-build-debug/BooksThroughTheAges_autogen/include/ui_NewSearchWindow.h"
#include "ui_NewSearchWindow.h"


NewSearchWindow::NewSearchWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewSearchWindow)
{
    this->setModal(true);
    ui->setupUi(this);
    this->setFixedSize(reg_w, reg_h);
    this->setWindowTitle("Book Search");
    ui->searchBar->setPlaceholderText("Enter book title");
    ui->statusLbl->setVisible(false);

    network_manager = new QNetworkAccessManager(this);
    // ui->scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

NewSearchWindow::~NewSearchWindow()
{
    delete ui;
}

void NewSearchWindow::newSearchWindowInit()
{
    this->open();
}

void NewSearchWindow::on_searchBtn_clicked()
{
    QString search_box = ui->searchBar->text();
    if (search_box.isEmpty())
    {
        return;
    }
    this->setFixedSize(search_w, search_h);
    ui->statusLbl->setVisible(true);
    ui->statusLbl->setText("Searching for books...");
    ui->statusLbl->setStyleSheet("color: black;");

    searchQuery(search_box);

}

void NewSearchWindow::searchQuery(QString search)
{
    QUrl url("http://openlibrary.org/search.json");
    QUrlQuery query;
    query.addQueryItem("title", search);
    query.addQueryItem("limit", search_limit);
    url.setQuery(query);

    QNetworkRequest request(url);
    QNetworkReply *reply = network_manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        int num_found = 0; //number of results

        if(reply->error() != QNetworkReply::NoError)
        {
            ui->statusLbl->setText("Error: " + reply->errorString());
            ui->statusLbl->setStyleSheet("color: red;");
            reply->deleteLater();
            return;
        }

        QByteArray search_data = reply->readAll();
        QJsonDocument search_json_doc = QJsonDocument::fromJson(search_data);
        QJsonObject search_json = search_json_doc.object();

        num_found= search_json["num_found"].toInt();
        if(num_found == 0)
        {
            ui->statusLbl->setText("No books found" );
            ui->statusLbl->setStyleSheet("color: red;");
            reply->deleteLater();
            return;
        }

        QLayoutItem *item;
        while ((item = ui->scrollLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        QJsonArray books = search_json["docs"].toArray();

        ui->statusLbl->setText(QString("Found %1 books. Showing top %2 results:").arg(num_found).arg(books.size()));
        ui->statusLbl->setStyleSheet("color: black;");

        for(const QJsonValue &book : books)
        {
            QJsonObject book_info = book.toObject();

            bk_info.clear();
            bk_title = book_info["title"].toString();
            bk_info.insert("title", bk_title);

            if(book_info.contains("author_name") && book_info["author_name"].isArray())
            {
                QJsonArray authors = book_info["author_name"].toArray();
                if(!authors.isEmpty())
                {
                    bk_author = authors[0].toString();

                    //if more than one author
                    if(authors.size() > 1)
                    {
                        bk_author += "et. all";
                    }
                }
            }
            else
            {
                bk_author = "Author Unknown";
            }
            bk_info.insert("author", bk_author);

            if(book_info.contains("cover_i"))
            {
                bk_cover_id = QString::number(book_info["cover_i"].toInt());
                bk_info.insert("cover_id", bk_cover_id);
            }

            if(book_info.contains("edition_key") && book_info["edition_key"].isArray())
            {
                QJsonArray editions = book_info["edition_key"].toArray();
                if(!editions.isEmpty())
                {
                    bk_id = editions[0].toString();
                    bk_info.insert("id", bk_id);
                }
            }
            else if(book_info.contains("key"))
            {
                bk_id = book_info["key"].toString();
                bk_info.insert("id", bk_id);
            }

            if(!bk_id.isEmpty())
            {
                bookListWidget *card = new bookListWidget(bk_info, this);
                ui->scrollLayout->addWidget(card);
            }
        }
        QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        ui->scrollLayout->addItem(spacer);

        ui->scrollLayout->setAlignment(Qt::AlignTop);
        // ui->scrollLayout->setSpacing(10);
        // ui->scrollLayout->setContentsMargins(5, 5, 5, 5);
        // ui->scrollArea->setWidgetResizable(true);

        reply->deleteLater();
    });
}

void NewSearchWindow::closeEvent(QCloseEvent* event)
{
    QLayoutItem *item;
    while ((item = ui->scrollLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    ui->searchBar->clear();
    ui->statusLbl->setVisible(false);
    this->setFixedSize(reg_w, reg_h);
    QDialog::closeEvent(event);
}
