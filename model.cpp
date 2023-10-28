#include "model.h"
#include "QtWidgets/qlabel.h"
#include "ui_model.h"
#include "customwidget.h"

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

    for(int i = 0; i < prods->size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, QString::fromStdString(prods->at(i)->getName()),
                                                               prods->at(i)->getCount(),
                                                               prods->at(i)->getPrice(),
                                                               prods->at(i)->getTime_limit());
    }

}

model::~model()
{
    delete ui;
}
void model::show_details(QListWidgetItem* item)
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
