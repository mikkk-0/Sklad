#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <mainwindow.h>

class CustomListWidgetItem: public QListWidgetItem {
public:
    CustomListWidgetItem(QListWidget *listview, QString title, int item1, int item2, int item3, int fl);
};

#endif // CUSTOMWIDGET_H
