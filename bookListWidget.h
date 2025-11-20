//
// Created by momer on 11/1/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H
#define BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class bookListWidget;
}

QT_END_NAMESPACE

class bookListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit bookListWidget(const QMap<QString, QString> &map, QWidget* parent = nullptr);
    ~bookListWidget() override;
    void configBookList(QMap<QString, QString> bookInfo);

private:
    Ui::bookListWidget* ui;

    QNetworkAccessManager* manager;
    QNetworkReply *cover_reply;

    void loadCover();
};


#endif //BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H