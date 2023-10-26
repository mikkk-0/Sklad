#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Globals.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->listWidget->addItem("Номер: 1");
//    ui->listWidget->addItem("Номер: 2");
//    ui->listWidget->addItem("Номер: 3");
//    ui->listWidget->addItem("Номер: 4");

    ui->listWidget_2->addItem("Торговая точка номер 1");
    ui->listWidget_2->addItem("Торговая точка номер 2");
    ui->listWidget_2->addItem("Торговая точка номер 3");

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::show_details);

    ui->spinBox->setMinimum(10);
    ui->spinBox->setMaximum(30);
    global::products = new std::vector<Product*>;
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
        std::string name = selectedItem->text().toStdString();
        int id = 0;
        for (int i = 0; i < (int)name.size(); ++i) {
            if (name[i] == '.') break;
            id = 10 * id + name[i] - '0';
        }
        delete global::products->at(id - 1);
        global::products->erase(global::products->begin() + id - 1);
        delete selectedItem;
        for (int i = 0; i < global::products->size(); ++i) {
            global::products->at(i)->setId(i);
            auto item = ui->listWidget->item(i);
            QString newText = QString::fromStdString(std::to_string(i + 1)) + ". " + QString::fromStdString(global::products->at(i)->getName());
            item->setText(newText);
        }
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

Product* getProduct(QWidget* parent) {
    Product* p = new Product;
    QString newText;
    while (newText.isEmpty()) {
        newText = QInputDialog::getText(parent, "Добавление продукта", "Введите название продукта:");
    }
    p->setName(newText.toStdString());
    int time_limit = QInputDialog::getInt(parent, "Добавление продукта", "Введите срок годности продукта:", 10, 4, 100);
    p->setTime_limit(time_limit);
    int price = QInputDialog::getInt(parent, "Добавление продукта", "Введите цену за 1 упаковку продукта (руб):", 20, 1);
    p->setPrice(price);
    double weight = QInputDialog::getDouble(parent, "Добавление продукта", "Введите вес 1 упаковку продукта (кг):", .5, .1);
    p->setWeight_per_pack(weight);
    p->setPercent(1);
    p->setCount(20);
    return p;
}

void MainWindow::on_edit_clicked()
{
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        std::string name = selectedItem->text().toStdString();
        int id = 0;
        for (int i = 0; i < (int)name.size(); ++i) {
            if (name[i] == '.') break;
            id = 10 * id + name[i] - '0';
        }
        Product* newProduct = getProduct(this);
        delete global::products->at(id - 1);
        global::products->at(id - 1) = newProduct;
        QString newText = QString::fromStdString(std::to_string(id)) + ". " + QString::fromStdString(newProduct->getName());
        selectedItem->setText(newText);
    }
}

void MainWindow::on_add_clicked()
{
    Product* product = getProduct(this);
    product->setId(global::products->size());
    global::products->emplace_back(product);
    QString newText = QString::fromStdString(std::to_string(global::products->size())) + ". " + QString::fromStdString(product->getName());
    ui->listWidget->addItem(newText);
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
    std::string name = item->text().toStdString();
    int id = 0;
    for (int i = 0; i < (int)name.size(); ++i) {
        if (name[i] == '.') break;
        id = 10 * id + name[i] - '0';
    }
    id--;
    Product* p = global::products->at(id);
    QString itemText =
              "Наименование: " + QString::fromStdString(p->getName())
            + "\nСрок годности (дней): " + QString::fromStdString(std::to_string(p->getTime_limit()))
            + "\nЦена за упаковку (руб): " + QString::fromStdString(std::to_string(p->getPrice()))
            + "\nВес одной упаковки (кг): " + QString::fromStdString(std::to_string(p->getWeight_per_pack()));

    QDialog* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Характеристики элемента");

    QLabel* detailsLabel = new QLabel(itemText);//вместо itemText нужно поля продукта брать, а вообще похуй

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(detailsLabel);

    detailsDialog->setLayout(layout);

    detailsDialog->exec();
}

