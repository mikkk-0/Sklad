#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <mainwindow.h>
#include "product.h"

class CustomListWidgetItem: public QListWidgetItem {
public:
    CustomListWidgetItem(QListWidget *listview, Product* product, bool showCheckBox);
    void onCheckBoxStateChanged(int state);
    void colorLabelsRed(QLayout* layout);
    void strikeoutText(QLayout* layout);
};

#endif // CUSTOMWIDGET_H
