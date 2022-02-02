#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game = new Game2048();
    game->newGame();
    applyStyles();

    endWindow = new SecondWindow();
    endWindow->setParent(this);
    endWindow->hide();

    QObject::connect(game, &Game2048::endGame, endWindow, &MainWindow::show);
    QObject::connect(endWindow, &SecondWindow::closed, game, &Game2048::newGame);
    QObject::connect(game, &Game2048::newGameStarted, this, &MainWindow::displayGameBoard);
}

void MainWindow::applyStyles(){

    QFile File(":/new/design/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    ui->score->setAlignment(Qt::AlignCenter);
    ui->best_score->setAlignment(Qt::AlignCenter);
    ui->score_name->setAlignment(Qt::AlignCenter);
    ui->best_score_name->setAlignment(Qt::AlignCenter);
    ui->boardUI->setFocusPolicy(Qt::NoFocus);

    setWindowIcon(QIcon(":/new/images/icon.png"));
}

void MainWindow::displayGameBoard()
{
    ui->score->setText(QString::number(game->score_));
    ui->best_score->setText(QString::number(game->bestScore_));

    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            if (!game->board[i][j])
                setBoardItem(i, j, " ");
            else
                setBoardItem(i, j, QString::number(game->board[i][j]));
}

void MainWindow::setBoardItem(int i, int j, QString value)
{
    if(ui->boardUI->cellWidget(i,j)) {
        ui->boardUI->removeCellWidget(i,j);
    }
    QColor color = getItemColor(value.toInt());
    QPushButton * cell = new QPushButton();
    QHBoxLayout * layout = new QHBoxLayout();
    QLabel * cell_value = new QLabel(value);
    cell_value->setAlignment(Qt::AlignCenter);

    layout->addWidget(cell_value);
    cell->setLayout(layout);

    cell->setStyleSheet("background: " + QString(color.name()) + ";"
                        "border-radius: 6px;"
                        "margin: 6px;"
                        "color: #776e65;"
                        "font-weight: bold;"
                        "font-size: 36px;");

    ui->boardUI->setCellWidget(i, j, cell);
}

QColor MainWindow::getItemColor(int itemValue)
{
    if (2 == itemValue)
        return QColor(238,228,218);
    else if (4 == itemValue)
        return QColor(237,224,200);
    else if (8 == itemValue)
        return QColor(242,177,121);
    else if (16 == itemValue)
        return QColor(245,149,99);
    else if (32 == itemValue)
        return QColor(246,124,95);
    else if (64 == itemValue)
        return QColor(246,94,59);
    else if (128 <= itemValue)
        return QColor(237,207,114);
    else
        return QColor(238, 228, 218, 35);
}

void MainWindow::on_pushButton_clicked()
{
   game->newGame();
   displayGameBoard();
}

void MainWindow::keyPressEvent(QKeyEvent * event){
     switch (event->key()){
     case Qt::Key_Up:
         game->moveNumberCell(up);
         break;
     case Qt::Key_Left:
         game->moveNumberCell(left);
         break;
     case Qt::Key_Down:
         game->moveNumberCell(down);
         break;
     case Qt::Key_Right:
         game->moveNumberCell(right);
         break;
     }
    displayGameBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}
