#include "GameManager.h"
#include <random>

Game2048::Game2048(){
    score_ = 0;
    bestScore_ = 0;
}

void Game2048::newGame(){

    score_ = 0;
    //filling board with "empty" values
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            board[i][j] = 0;

//    //generating first "2"
    addNumberCell();
    emit newGameStarted();
}

std::pair<int, int> Game2048::getRandomFreeCell(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);

    bool generated = false;
    int line, column;

    while (!generated){
        line = dist6(rng);
        column = dist6(rng);

        if (0 == board[line][column])
            generated = true;
    }
    return std::make_pair(line, column);
}

void Game2048::addNumberCell(){
    std::pair<int,int> pos = getRandomFreeCell();
    board[pos.first][pos.second] = firstCellValue;
}

bool Game2048::isPossibleToMoveNumberCell(int i, int j, int nextI, int nextJ) {
    if (nextI < 0 || nextI >= 4 || nextJ < 0 || nextJ >= 4
        || (board[i][j] != board[nextI][nextJ] && board[nextI][nextJ] != 0))
        return 0;
    return 1;
}

void Game2048::updateScore(int points){
    score_ += points;
    if (score_ > bestScore_)
        bestScore_ = score_;
}

void Game2048::mergeNumberCells(int i, int j, int nextI, int nextJ){
    if (!( i == nextI && j == nextJ)){
        board[nextI][nextJ] += board[i][j];
        board[i][j] = 0;
    }
}

int rowStepFor(int direction){
    switch (direction){
    case down:
        return 1;
    case right:
        return 0;
    case up:
        return -1;
    case left:
        return 0;
    }
    return 0;
}

int columnStepFor(int direction){
    switch (direction){
    case down:
        return 0;
    case right:
        return 1;
    case up:
        return 0;
    case left:
        return -1;
    }
    return 0;
}

void Game2048::moveNumberCell(int direction){
    int startRow = 0
            , startColumn = 0
            , lineStep = 1
            , columnStep = 1;

    if (down == direction){
        startRow = 3;
        lineStep = -1;
    }

    if (right == direction){
        startColumn = 3;
        columnStep = -1;
    }

    bool movePossible = 0
        ,canAddPiece = 0;

    do {
        movePossible = 0;
        for (int i = startRow; i>= 0 && i < 4; i+= lineStep)
            for (int j = startColumn; j >= 0 && j < 4 ; j+= columnStep){
                 int nextI = i + rowStepFor(direction)
                   , nextJ = j + columnStepFor(direction);

                 if (board[i][j] && isPossibleToMoveNumberCell(i,j, nextI, nextJ)){
                     mergeNumberCells(i, j, nextI, nextJ);
                     updateScore(board[nextI][nextJ]);
                     movePossible = canAddPiece = true;
                 }
                 else if (isBoardFullOfNumberCells()){
                     emit endGame();
                     break;
                 }
            }
      } while (movePossible);

    if (canAddPiece){
       addNumberCell();
    }
}

bool Game2048::isBoardFullOfNumberCells(){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if (0 == board[i][j])
                return false;
    return true;
}
