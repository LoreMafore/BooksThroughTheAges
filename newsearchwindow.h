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

    // uint16_t reg_w = 710; //initial width
    uint16_t reg_w = 605; //initial width
    uint16_t reg_h = 45;  //initial height
    // uint16_t search_w = 710; // after search width
    uint16_t search_w = 605; // after search width
    uint16_t search_h = 500; // after search height

    QNetworkAccessManager* network_manager{};
    QString search_limit = "10";
    QString bk_author;
    QString bk_cover_id;
    QString bk_id;
    QString bk_pages;
    QString bk_title;
    QMap<QString, QString> bk_info;
    // QPixmap bk_pixmap;

    void searchQuery(QString search);
    void closeEvent(QCloseEvent* event) override;
};


#endif //BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H