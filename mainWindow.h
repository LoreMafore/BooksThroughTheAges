//
// Created by momer on 10/30/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_MAINWINDOW_H
#define BOOKSTHROUGHTHEAGES_MAINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class mainWindow;
}

QT_END_NAMESPACE

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget* parent = nullptr);
    ~mainWindow() override;

private:
    Ui::mainWindow* ui;
};


#endif //BOOKSTHROUGHTHEAGES_MAINWINDOW_H