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
#include <QCheckBox>
#include "clwi_4.h"
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
    model(QWidget*, std::vector<Product*>*, std::vector<std::string>, int);
    ~model();

public slots:
    void perc(QListWidgetItem* item);
    void updateTextEdit(QListWidgetItem* item);
    void show_details(QListWidgetItem* item);

private slots:
    void on_create_shipment_clicked();

    void on_nextDay_clicked();

private:
    Ui::model *ui;
    std::vector<Product*>* prods;
    Storage* st;
    void next_day();
};

#endif // MODEL_H
