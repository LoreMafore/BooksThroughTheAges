#include "newsearchwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include "cmake-build-debug/BooksThroughTheAges_autogen/include/ui_NewSearchWindow.h"


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

        QJsonArray books = search_json["docs"].toArray();
    });
}

void NewSearchWindow::closeEvent(QCloseEvent* event)
{
    ui->searchBar->clear();
    ui->statusLbl->setVisible(false);
    this->setFixedSize(reg_w, reg_h);
    QDialog::closeEvent(event);
}
