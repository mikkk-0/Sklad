#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Номер: 1");
    ui->listWidget->addItem("Номер: 2");
    ui->listWidget->addItem("Номер: 3");
    ui->listWidget->addItem("Номер: 4");

    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::show_details);
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
        QString newText = QInputDialog::getText(this, "Изменение элемента", "Введите новый текст:", QLineEdit::Normal, selectedItem->text());
        if (!newText.isEmpty()) {
            selectedItem->setText(newText);
        }
    }
}

void MainWindow::on_add_clicked()
{
    QString newText = QInputDialog::getText(this, "Добавление элемента", "Введите новый текст:");
    if (!newText.isEmpty()) {
        ui->listWidget->addItem(newText);
    }
}

void MainWindow::show_details(QListWidgetItem* item)
{
    QString itemText = item->text();

    QDialog* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Характеристики элемента");

    QLabel* detailsLabel = new QLabel(itemText);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(detailsLabel);

    detailsDialog->setLayout(layout);

    detailsDialog->exec();
}

