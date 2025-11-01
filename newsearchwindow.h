#ifndef BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H
#define BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>


namespace Ui
{
    class NewSearchWindow;
}


class NewSearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewSearchWindow(QWidget* parent = nullptr);
    ~NewSearchWindow() override;
    void newSearchWindowInit();

private slots:
    void on_searchBtn_clicked();

private:
    Ui::NewSearchWindow* ui;

    QNetworkAccessManager* network_manager{};
    QString search_limit = "10";
    QString bk_id;
    QString bk_title;
    QString bk_author;
    QString bk_pages;
    QPixmap bk_pixmap;

    void searchQuery(QString search);
    void closeEvent(QCloseEvent* event) override;
};


#endif //BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H