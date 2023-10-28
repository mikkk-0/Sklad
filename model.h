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

namespace Ui {
class model;
}

class model : public QWidget
{
    Q_OBJECT

public:
    explicit model(QWidget *parent = nullptr);
    ~model();

private:
    Ui::model *ui;
};

#endif // MODEL_H
