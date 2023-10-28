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
    void show_details(QListWidgetItem* item);

private:
    Ui::model *ui;
    std::vector<Product*>* prods;
    Storage* st;
};

#endif // MODEL_H
