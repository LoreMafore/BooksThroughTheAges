//
// Created by momer on 10/30/2025.
//
#include "newsearchwindow.h"
#include "ui_NewSearchWindow.h"


NewSearchWindow::NewSearchWindow(QWidget* parent) :
    QDialog(parent), ui(new Ui::NewSearchWindow)
{
    ui->setupUi(this);
}

NewSearchWindow::~NewSearchWindow()
{
    delete ui;
}