//
// Created by momer on 10/30/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainWindow.h"
#include "ui_mainWindow.h"


mainWindow::mainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    new_search_window = new NewSearchWindow(this);


    connect(ui->newBookBtn, &QPushButton::clicked, this, &mainWindow::openNewSearchWindow);
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::openNewSearchWindow()
{
    new_search_window->open();
}
