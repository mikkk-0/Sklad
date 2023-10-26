#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Цена: 1, Номер: 1");
    ui->listWidget->addItem("Цена: 1, Номер: 2");
    ui->listWidget->addItem("Цена: 1, Номер: 3");
    ui->listWidget->addItem("Цена: 1, Номер: 4");
}

void MainWindow::delete_item(QHBoxLayout* layout_h){
    QLayoutItem *child;
    while ((child = layout_h->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_delete_2_clicked()
{
    ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        delete selectedItem;
    }
}


void MainWindow::on_edit_clicked()
{
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        selectedItem->setText("");
    }
}

