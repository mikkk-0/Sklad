#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>>
#include <QPushButton>
#include <QApplication>
#include <QWidget>

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
    void delete_item (QHBoxLayout*);

private slots:
    void on_delete_2_clicked();

    void on_edit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
