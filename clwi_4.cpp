#include "clwi_4.h"
#include "QtWidgets/qlabel.h"

clwi_4::clwi_4(QListWidget *listview, Shipment * shipm):QListWidgetItem(listview)
{
    QString title = QString::fromStdString("Заказ № " + std::to_string(shipm->getId()));
    QLabel* titleLabel = new QLabel(title);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleLabel->setFont(titleFont);
    QVBoxLayout* lt = new QVBoxLayout();

    for(int i = 0; i < shipm->getProducts().size(); ++i){
        QString srtg = QString::fromStdString(shipm->getProducts()[i]->getName() + ": " + std::to_string(shipm->getProducts()[i]->getCount()) + " пачек");
        QLabel* labl = new QLabel(srtg);
        lt->addWidget(labl);
    }
    QString str = QString::fromStdString("Осталось ждать: " + std::to_string(shipm->getLeft_days()) + " дней");
    QLabel* label = new QLabel(str);
    lt->addWidget(label);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addItem(lt);
    QWidget* widget = new QWidget();
    widget->setLayout(mainLayout);
    setSizeHint(widget->sizeHint());

    listWidget()->setItemWidget(this, widget);
}
