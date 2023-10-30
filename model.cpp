#include "model.h"
#include "ui_model.h"
#include "customwidget.h"

model::model(QWidget *parent, std::vector<Product*>* prods) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    this->prods = prods;
    st = new Storage(prods);

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

    connect(ui->listWidget_2, &QListWidget::itemClicked, this, &model::updateTextEdit);
}

model::~model()
{
    delete ui;
}


void model::updateTextEdit(QListWidgetItem* item) {
    if (item) {
        QString itemText = item->text();
        ui->textEdit->setPlainText(itemText);
    }
}

void model::perc(QListWidgetItem* item)
{
    if (item) {
        int id = 0;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i) == item) {
                id = i;
                break;
            }
        }
        Product* p = st->getProds().at(id);
        if (p->getPercent() != 0) {
            return;
        }
        int newValue = QInputDialog::getDouble(this, "Ввод процента уценки", "Введите новый процент:", 15, 1, 100);
        p->setPercent(newValue);
        st->orderProducts();
        ui->listWidget->clear();
        for(int i = 0; i < st->getProds().size(); ++i) {
            p = st->getProds().at(i);
            CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, p, false);
            if (p->getTime_limit() == 0) item1->strikeoutText();
            else if (p->getPercent() == 0 && p->getTime_limit() < 3) item1->colorLabelsRed();
        }
    }
}

void model::on_create_shipment_clicked()
{
    std::vector<Product*> need_prods;
    for (int i = 0; i < ui->listWidget_3->count(); ++i) {
        auto item = ui->listWidget_3->item(i);
        auto layout = ui->listWidget_3->itemWidget(item)->layout()->itemAt(1)->layout();
        auto checkbox = qobject_cast<QCheckBox*>(layout->itemAt(6)->widget());
        if (checkbox->isChecked()) {
            need_prods.emplace_back(this->prods->at(i));
            checkbox->setCheckState(Qt::Unchecked);
        }
    }
    int days = rnd() % 4 + 1;
    this->st->addShipment(generateShipment(need_prods, days));
    this->st->orderShipments();
}
