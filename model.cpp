#include "model.h"
#include "QtWidgets/qlabel.h"
#include "ui_model.h"
#include "customwidget.h"

#include <QMenuBar>

model::model(QWidget *parent, std::vector<Product*>* prods, std::vector<std::string> names, int N) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    this->prods = prods;
    st = new Storage(prods, names);
    this->n  = N;
    n++;

    ui->tabWidget->setTabText(1, "Список товаров на складе");
    ui->tabWidget->setTabText(2, "Список запросов на поставку");
    ui->tabWidget->setTabText(0, "Список заказов");



    for(int i = 0; i < st->getProds().size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, st->getProds()[i], false);
    }

    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &model::perc);

    connect(ui->listWidget_2, &QListWidget::itemClicked, this, &model::updateTextEdit);
}


void model::redraw_products()
{
    ui->listWidget->clear();
    for(int i = 0; i < st->getProds().size(); ++i) {
        CustomListWidgetItem* item1 = new CustomListWidgetItem(ui->listWidget, st->getProds()[i], false);
        if (st->getProds()[i]->getTime_limit() == 0) {
            item1->strikeoutText();
            ui->listWidget->update();
        } else if (st->getProds()[i]->getTime_limit() <= 3) {
            item1->colorLabelsRed();
            ui->listWidget->update();
        }
    }
}

void model::next_day() {
    st->newDay(*this->prods);
    --n;
    if(n == 0){
        QString itemText =
                  QString::fromStdString("Итоговый доход: ") + QString::number(st->getTotal());

        QDialog* detailsDialog = new QDialog(this);
        detailsDialog->setWindowTitle("Характеристики элемента");

        QLabel* detailsLabel = new QLabel(itemText);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(detailsLabel);

        detailsDialog->setLayout(layout);

        detailsDialog->exec();
        this->destroy();
    }
    ui->listWidget_4->clear();
    for(int i = 0; i < st->getShpmnts().size(); ++i){
        clwi_4* item1 = new clwi_4(ui->listWidget_4, st->getShpmnts()[i]);
    }
    ui->listWidget_2->clear();
    for (int i = 0; i < st->getToday_qrs().size(); ++i) {
        QString name = QString::fromStdString(st->getToday_qrs()[i]->getS_pt()->getName());
        ui->listWidget_2->addItem(name);
    }
    ui->textEdit->clear();

    redraw_products();


}

model::~model()
{
    delete ui;
}

void model::updateTextEdit(QListWidgetItem* item) {
    if (item) {
        int id = 0;
        for (int i = 0; i < ui->listWidget_2->count(); ++i) {
            if (ui->listWidget_2->item(i) == item) {
                id = i;
                break;
            }
        }
        Query* query = st->getToday_qrs()[id];
        Query* q_reply = st->getToday_qrs_reply()[id];
        QString itemText = QString::fromStdString("Заказ от " + query->getS_pt()->getName());
        for (int i = 0; i < query->getProds().size(); ++i) {
            itemText += "\n";
            itemText += QString::fromStdString(st->getInfo_products()[id][i].first);
            itemText += ":\nЗапрошено: ";
            itemText += QString::number(query->at(i).second);
            itemText += " кг\nОтгружено: ";
            itemText += QString::number(q_reply->at(i).second);
            itemText += " (";
            itemText += QString::number(q_reply->at(i).second * st->getInfo_products()[id][i].second);
            itemText += " кг)";
        }
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
        redraw_products();
    }
}

void model::on_nextDay_clicked()
{
    next_day();
}

