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
    this->setFixedSize(715, 45);
    // this->setMinimumSize(715, 45);
    // this->setMaximumSize(715, 500);
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
    this->setFixedSize(715, 500);
    ui->statusLbl->setVisible(true);
    ui->statusLbl->setText("Searching for books...");

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

}

void NewSearchWindow::closeEvent(QCloseEvent* event)
{
    ui->searchBar->clear();
    ui->statusLbl->setVisible(false);
    this->setFixedSize(715, 45);
    QDialog::closeEvent(event);
}
