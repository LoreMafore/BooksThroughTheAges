//
// Created by momer on 10/30/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_MAINWINDOW_H
#define BOOKSTHROUGHTHEAGES_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "newsearchwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class mainWindow;
}
QT_END_NAMESPACE

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget* parent = nullptr);
    ~mainWindow() override;
    void openNewSearchWindow();

private:
    Ui::mainWindow* ui;
    NewSearchWindow* new_search_window;
};


#endif //BOOKSTHROUGHTHEAGES_MAINWINDOW_H