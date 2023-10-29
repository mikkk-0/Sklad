#include "model.h"
#include "ui_model.h"
#include "customwidget.h"

model::model(QWidget *parent, std::vector<Product*>* prods) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    this->prods = prods;

    for (int i = 0; i < (int)prods->size(); ++i) {
        auto& p = prods->at(i);
        p->setCount(30);
    }

    ui->tabWidget->setTabText(1, "Список товаров на складе");
    ui->tabWidget->setTabText(2, "Заказы в фирму-поставщик");
    ui->tabWidget->setTabText(3, "МБМБМБМБМБМБМББ");
    ui->tabWidget->setTabText(0, "Список заказов");

    for(int i = 0; i < prods->size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, prods->at(i), false);
    }

    for(int i = 0; i < prods->size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget_3, prods->at(i), true);
    }
    //connect(checkBox, &QCheckBox::stateChanged, this, &CustomListWidgetItem::onCheckBoxStateChanged);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &model::perc);
}

model::~model()
{
    delete ui;
}


void model::perc(QListWidgetItem* item)
{
    if (item) {
        QString itemText = item->text();

        int newValue = QInputDialog::getDouble(this, "Ввод процента уценки", "Введите новый процент:", 15, 1, 100);
        int id = 0;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i) == item) {
                id = i;
                break;
            }
        }
        Product* p = prods->at(id);
        p->setPercent(newValue);
    }
}
