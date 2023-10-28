#include "model.h"
#include "QtWidgets/qlabel.h"
#include "ui_model.h"

model::model(QWidget *parent, std::vector<Product*>* prods) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    this->prods = prods;


    ui->tabWidget->setTabText(1, "Список товаров на складе");
    ui->tabWidget->setTabText(2, "Заказы в фирму-поставщик");
    ui->tabWidget->setTabText(3, "МБМБМБМБМБМБМББ");
    ui->tabWidget->setTabText(0, "Список заказов");

    ui->listWidget->addItem("что-то что потом поменяем");
    ui->listWidget->addItem("что-то что потом поменяем");
    ui->listWidget->addItem("что-то что потом поменяем");
    ui->listWidget->addItem("что-то что потом поменяем");

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &model::show_details);
}

model::~model()
{
    delete ui;
}

int index(QListWidgetItem* item) {
    std::string name = item->text().toStdString();
    int id = 0;
    for (int i = 0; i < (int)name.size(); ++i) {
        if (name[i] == '.') break;
        id = 10 * id + name[i] - '0';
    }
    return --id;
}

void model::show_details(QListWidgetItem* item)
{
    int id = index(item);
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
