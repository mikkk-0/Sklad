#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QErrorMessage>
#include "Includes.h"

namespace Ui {
class model;
}

class model : public QWidget
{
    Q_OBJECT

public:
    model(QWidget*, std::vector<Product*>*);
    ~model();

private:
    Ui::model *ui;
    std::vector<Product*>* prods;
    Storage* st;
};

#endif // MODEL_H
