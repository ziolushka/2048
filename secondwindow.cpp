#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    applyStyles();

    QWidget *end_window = new QWidget(this);
    setCentralWidget(end_window);
    end_window->setLayout(ui->main_layout);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFixedSize(500, 700);

    QPalette pal = palette();
    //Windows
    //pal.setColor(QPalette::Background, QColor(238, 228, 218, 150));
    //macOS
    pal.setColor(QPalette::Window, QColor(238, 228, 218, 150));
    end_window->setAutoFillBackground(true);
    end_window->setPalette(pal);

}

SecondWindow::~SecondWindow()
{
    delete ui;
}
void SecondWindow::applyStyles()
{
    QFile File(":/new/design/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}
void SecondWindow::on_try_again_button_clicked()
{
    emit closed();
    this->close();
}

void SecondWindow::on_link_button_clicked()
{
    QString autorLinkedIn = "https://www.linkedin.com/in/olena-z-b714a013b/";
    QDesktopServices::openUrl(QUrl(autorLinkedIn));
}
