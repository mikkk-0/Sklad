#ifndef MODEL_H
#define MODEL_H

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
#include "product.h"
#include "storage.h"
#include "shipment.h"

namespace Ui {
class model;
}

class model : public QWidget
{
    Q_OBJECT

public:
    model(QWidget*, std::vector<Product*>*);
    ~model();

public slots:
    void perc(QListWidgetItem* item);

private slots:
    void on_create_shipment_clicked();

private:
    Ui::model *ui;
    std::vector<Product*>* prods;
    Storage* st;
};

#endif // MODEL_H
