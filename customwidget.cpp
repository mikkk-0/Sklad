#include "customwidget.h"
#include "QtWidgets/qlabel.h"
#include "mainwindow.h"

CustomListWidgetItem::CustomListWidgetItem(QString title, int item1, int item2, int item3)
{
    setText(title);

    QString item1Str = QString::number(item1);
    QString item2Str = QString::number(item2);
    QString item3Str = QString::number(item3);

    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* label1 = new QLabel(item1Str);
    QLabel* label2 = new QLabel(item2Str);
    QLabel* label3 = new QLabel(item3Str);
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    widget->setLayout(layout);

    setSizeHint(widget->sizeHint());
    listWidget()->setItemWidget(this, widget);
}
