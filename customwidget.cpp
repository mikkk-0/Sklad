#include "customwidget.h"
#include "QtWidgets/qlabel.h"
#include <QCheckBox>

CustomListWidgetItem::CustomListWidgetItem(QListWidget * listview, QString title, int item1, int item2, int item3, int fl):QListWidgetItem(listview)
{
QLabel* titleLabel = new QLabel(title);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleLabel->setFont(titleFont);

    QLabel* spaceLabel = new QLabel(" ");

    QLabel* label1 = new QLabel("Остаток: " + QString::number(item1) + "(кг)");
    QLabel* spaceLabel1 = new QLabel(" ");

    QLabel* label2 = new QLabel("Цена: " + QString::number(item2) + "(руб)");
    QLabel* spaceLabel2 = new QLabel(" ");

    QLabel* label3 = new QLabel("Срок годности: " + QString::number(item3) + "(сут)");

    QCheckBox* checkBox = new QCheckBox();
    if(fl == 0) checkBox->hide();

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

    QWidget* widget = new QWidget();
    widget->setLayout(mainLayout);

    setSizeHint(widget->sizeHint());

    listWidget()->setItemWidget(this, widget);
}
