//
// Created by momer on 10/30/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H
#define BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H

#include <QDialog>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class NewSearchWindow;
}

QT_END_NAMESPACE

class NewSearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewSearchWindow(QWidget* parent = nullptr);
    ~NewSearchWindow() override;

private:
    Ui::NewSearchWindow* ui;
};


#endif //BOOKSTHROUGHTHEAGES_NEWSEARCHWINDOW_H