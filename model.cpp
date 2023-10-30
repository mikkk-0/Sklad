#include "model.h"
#include "QtWidgets/qlabel.h"
#include "ui_model.h"
#include "customwidget.h"

#include <QMenuBar>

model::model(QWidget *parent, std::vector<Product*>* prods, std::vector<std::string> names) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    this->prods = prods;
    st = new Storage(prods, names);

    ui->tabWidget->setTabText(1, "Список товаров на складе");
    ui->tabWidget->setTabText(2, "Заказы в фирму-поставщик");
    ui->tabWidget->setTabText(3, "Список запросов на поставку");
    ui->tabWidget->setTabText(0, "Список заказов");



    for(int i = 0; i < prods->size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, prods->at(i), false);
    }

    for(int i = 0; i < prods->size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget_3, prods->at(i), true);
    }



    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &model::perc);

    connect(ui->listWidget_2, &QListWidget::itemClicked, this, &model::updateTextEdit);

    connect(ui->listWidget_4, &QListWidget::itemDoubleClicked, this, &model::show_details);


}

void model::next_day() {
    st->newDay();
    for(int i = 0; i < st->getShpmnts().size(); ++i){
        clwi_4* item1 = new clwi_4(ui->listWidget_4, st->getShpmnts()[i]);
    }
}

model::~model()
{
    delete ui;
}

void model::show_details(QListWidgetItem* item)
{
    int id = 0;
    for (int i = 0; i < ui->listWidget_4->count(); ++i) {
        if (ui->listWidget_4->item(i) == item) {
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

void model::on_nextDay_clicked()
{
    next_day();
}

