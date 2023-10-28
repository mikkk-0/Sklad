#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <model.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void show_details(QListWidgetItem* item);

private slots:
    void on_delete_2_clicked();
    void on_delete_3_clicked();

    void on_edit_clicked();
    void on_edit_2_clicked();

    void on_add_clicked();
    void on_add_2_clicked();
    void on_start_clicked();

private:
    Ui::MainWindow *ui;
    model model;
};
#endif
