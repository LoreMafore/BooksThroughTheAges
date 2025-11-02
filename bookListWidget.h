//
// Created by momer on 11/1/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H
#define BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H

#include <QWidget>


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
    explicit bookListWidget(QWidget* parent = nullptr);
    ~bookListWidget() override;
    void configBookList(QMap<QString, QString> bookInfo);

private:
    Ui::bookListWidget* ui;
};


#endif //BOOKSTHROUGHTHEAGES_BOOKLISTWIDGET_H