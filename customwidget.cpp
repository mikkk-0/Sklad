#include "customwidget.h"
#include "QtWidgets/qlabel.h"
#include <QCheckBox>

CustomListWidgetItem::CustomListWidgetItem(QListWidget * listview, Product* product, bool showCheckBox):QListWidgetItem(listview)
{
    QString title = QString::fromStdString(product->getName());
    QLabel* titleLabel = new QLabel(title);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleLabel->setFont(titleFont);

    QLabel* spaceLabel = new QLabel(" ");

    QLabel* label1 = new QLabel("Остаток: " + QString::number(product->getCount()) + " шт. (" + QString::number(product->getCount() * product->getWeight_per_pack()) + " кг)");
    QLabel* spaceLabel1 = new QLabel(" ");

    QLabel* label2 = new QLabel("Цена: " + QString::number(product->getPrice()) + " руб.");
    QLabel* spaceLabel2 = new QLabel(" ");

    QLabel* label3 = new QLabel("Срок годности: " + QString::number(product->getTime_limit()) + " суток");

    QCheckBox* checkBox = new QCheckBox();
    if(!showCheckBox) checkBox->hide();

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label1);
    layout->addWidget(spaceLabel);
    layout->addWidget(label2);
    layout->addWidget(spaceLabel1);
    layout->addWidget(label3);
    layout->addWidget(spaceLabel2);
    layout->addWidget(checkBox);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(layout);
    colorLabelsRed(mainLayout);

    QWidget* widget = new QWidget();
    widget->setLayout(mainLayout);

    setSizeHint(widget->sizeHint());

    listWidget()->setItemWidget(this, widget);
};

void CustomListWidgetItem::colorLabelsRed(QLayout* mainLayout)
{
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);

    for (int i = 0; i < mainLayout->count(); ++i) {
        QLayoutItem* item = mainLayout->itemAt(i);
        if (item) {
            QWidget* widget = item->widget();
            if (widget) {
                QLabel* label = qobject_cast<QLabel*>(widget);
                if (label) {
                    label->setPalette(palette);
                }
            } else {
                QLayout* layout = item->layout();
                if (layout) {
                    colorLabelsRed(layout);
                }
            }
        }
    }
}

void CustomListWidgetItem::onCheckBoxStateChanged(int state)
{
    if (state == Qt::Checked)
    {
        //действия, когда флажок зелёный
    }
    else
    {
        //действия, когда флажок снят
    }
}
