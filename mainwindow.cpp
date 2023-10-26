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

    ui->listWidget_2->addItem("Торговая точка номер 1");
    ui->listWidget_2->addItem("Торговая точка номер 2");
    ui->listWidget_2->addItem("Торговая точка номер 3");

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::show_details);

    ui->spinBox->setMinimum(10);
    ui->spinBox->setMaximum(30);
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

void MainWindow::on_delete_3_clicked()
{
    ui->listWidget_2->removeItemWidget(ui->listWidget_2->currentItem());
    QListWidgetItem* selectedItem = ui->listWidget_2->currentItem();
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

void MainWindow::on_edit_2_clicked()
{
    QListWidgetItem* selectedItem = ui->listWidget_2->currentItem();
    if (selectedItem) {
        QString newText = QInputDialog::getText(this, "Изменение элемента", "Введите новый текст:", QLineEdit::Normal, selectedItem->text());
        if (!newText.isEmpty()) {
            selectedItem->setText(newText);
        }
    }
}

void MainWindow::on_add_2_clicked()
{
    QString newText = QInputDialog::getText(this, "Добавление элемента", "Введите новый текст:");
    if (!newText.isEmpty()) {
        ui->listWidget_2->addItem(newText);
    }
}

void MainWindow::show_details(QListWidgetItem* item)
{
    QString itemText = item->text();

    QDialog* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Характеристики элемента");

    QLabel* detailsLabel = new QLabel(itemText);//вместо itemText нужно поля продукта брать, а вообще похуй

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(detailsLabel);

    detailsDialog->setLayout(layout);

    detailsDialog->exec();
}

