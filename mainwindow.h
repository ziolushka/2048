#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QObject>
#include <QLayoutItem>

#include "GameManager.h"
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setBoardItem(int, int, QString);
    void keyPressEvent(QKeyEvent *) override;
    void applyStyles();
    QColor getItemColor(int);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void displayGameBoard();

private:
    Ui::MainWindow *ui;
    Game2048 *game;
    SecondWindow *endWindow;
};
#endif // MAINWINDOW_H
