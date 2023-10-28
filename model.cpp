#include "model.h"
#include "ui_model.h"

model::model(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);

    ui->tabWidget->setTabText(0, "Список заказов");
    ui->tabWidget->setTabText(1, "Список товаров на складе");
    ui->tabWidget->setTabText(2, "Заказы в фирму-поставщик");
    ui->tabWidget->setTabText(3, "МБМБМБМБМБМБМББ");
}

model::~model()
{
    delete ui;
}
