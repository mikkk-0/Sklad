#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    prods = new std::vector<Product*>;
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
        int id = 0;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i) == selectedItem) {
                id = i;
                break;
            }
        }
        delete prods->at(id);
        prods->erase(prods->begin() + id);
        delete selectedItem;
        for (int i = 0; i < (int)prods->size(); ++i) {
            prods->at(i)->setId(i);
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
        int id = 0;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i) == selectedItem) {
                id = i;
                break;
            }
        }
        Product* newProduct = getProduct(this);
        newProduct->setId(id);
        delete prods->at(id);
        prods->at(id) = newProduct;
        QString newText = QString::fromStdString(newProduct->getName());
        selectedItem->setText(newText);
    }
}

void MainWindow::on_add_clicked()
{
    Product* product = getProduct(this);
    product->setId(prods->size());
    prods->emplace_back(product);
    QString newText = QString::fromStdString(product->getName());
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
    int id = 0;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i) == item) {
            id = i;
            break;
        }
    }
    Product* p = prods->at(id);
    QString itemText =
              "Наименование: " + QString::fromStdString(p->getName())
            + "\nСрок годности (дней): " + QString::fromStdString(std::to_string(p->getTime_limit()))
            + "\nЦена за упаковку (руб): " + QString::fromStdString(std::to_string(p->getPrice()))
            + "\nВес одной упаковки (кг): " + QString::fromStdString(std::to_string(p->getWeight_per_pack()));

    QDialog* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Характеристики элемента");

    QLabel* detailsLabel = new QLabel(itemText);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(detailsLabel);

    detailsDialog->setLayout(layout);

    detailsDialog->exec();
}


void MainWindow::on_start_clicked() {
    if (ui->listWidget_2->count() < 3 || ui->listWidget_2->count() > 9) {
        QString itemText =
                  "Невозможно начать моделирование:\nКоличество торговых точек должно быть не меньше 3 и не больше 9.\n";
        QErrorMessage* detailsDialog = new QErrorMessage(this);
        detailsDialog->setWindowTitle("Ошибка запуска модели");

        detailsDialog->showMessage(itemText);

        detailsDialog->exec();
        return;
    }
    else {
        model_ = new model(nullptr, this->prods);
        model_->setWindowTitle("Система управления");
        model_->show();
    }
}

