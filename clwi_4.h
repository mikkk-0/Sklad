#ifndef CLWI_4_H
#define CLWI_4_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QErrorMessage>
#include <QPalette>
#include "product.h"
#include "shipment.h"

class clwi_4 : public QListWidgetItem
{
public:
    clwi_4(QListWidget *listview, Shipment * shipm);
};

#endif // CLWI_4_H
