#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
    mod = 2;
    clickX = 1;
    clickY = 1;
    offColor = QColor(255, 255, 255);
    onColor = QColor(0, 0, 0);
    mode = MODE_TOGGLE;
    setBoardSize(5, 5);
    drawLines = true;
//    drawClicks = true;
    xorFilter = false;
    lightChaseGreen = true;
    seed = 0;
    vx1 = 1;
    vy1 = 1;
    vx2 = boardWidth;
    vy2 = boardHeight;
}

void BoardWidget::saveImage() {
    QPixmap pix(boardWidth, boardHeight);
    QPainter p(&pix);
    for(int i = 0; i < boardWidth; i++) {
        for(int j = 0; j < boardHeight; j++) {
            p.fillRect(i, j, 1, 1,
                   getColor(xorFilter ? (grid[i][j] + horz[i] + vert[j] + 1) % mod : grid[i][j]));
        }
    }
    QFile file("file.png");
    file.open(QIODevice::WriteOnly);
    pix.save(&file, "PNG");
}

void BoardWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    int newWidth = vx2 - vx1 + 1;
    int newHeight = vy2 - vy1 + 1;
    double gridSize = std::min((width() - PADDING * 2) / newWidth, (height() - PADDING * 2) / newHeight);
    int w = floor(gridSize * newWidth);
    int h = floor(gridSize * newHeight);
    int x = width() / 2 - w / 2;
//        int x2 = 3 * width() / 4 - w / 2;
    int y = height()/2 - h/2;
    for(double i = 0; i < newWidth; i += (newWidth < w ? 1 : 1.0 * newWidth / w)) {
        for(double j = 0; j < newHeight; j += (newHeight < h ? 1 : 1.0 * newHeight / h)) {
            p.fillRect(x + i * gridSize, y + j * gridSize, ceil(gridSize), ceil(gridSize),
                       getColor(xorFilter ? (grid[vx1 + i - 1][vy1 + j - 1] + horz[vx1 + i - 1] + vert[vy1 + j - 1] + 1) % mod : grid[vx1 + i - 1][vy1 + j - 1]));
//                p.fillRect(x2 + i * gridSize, y + j * gridSize, ceil(gridSize), ceil(gridSize),
//                           colors[1][drawLights ? grid[i][j] : grid[i][j]]);
        }
    }
    p.drawRect(x, y, w, h);
//        p.drawRect(x2, y, w, h);
    if(drawLines && newWidth < w && newHeight < h) {
        for(int i = 0; i < newWidth; i++) {
            int lineX = x + i * gridSize;
            p.drawLine(lineX, y, lineX, y + h);
//                lineX = x2 + i * gridSize;
//                p.drawLine(lineX, y, lineX, y + h);
        }
        for(int i = 0; i < newHeight; i++) {
            int lineY = y + i * gridSize;
            p.drawLine(x, lineY, x + w, lineY);
//                p.drawLine(x2, lineY, x2 + w, lineY);
        }
    }
    p.end();
}

void BoardWidget::mousePressEvent(QMouseEvent *event) {
    int newWidth = vx2 - vx1 + 1;
    int newHeight = vy2 - vy1 + 1;
    double gridSize = std::min((width() - PADDING * 2) / newWidth, (height() - PADDING * 2) / newHeight);
    int w = floor(gridSize * newWidth);
    int h = floor(gridSize * newHeight);
    int x = width() / 2 - w / 2;
//        int x2 = 3 * width() / 4 - w / 2;
    int y = height() / 2 - h / 2;
    int mx = event->x();
    int my = event->y();
    if(mx >= x && mx < x + w && my >= y && my < y + h) {
        int i = vx1 + (mx - x) / gridSize - 1;
        int j = vy1 + (my - y) / gridSize - 1;
        if(mode == MODE_TOGGLE)
            grid[i][j] = (grid[i][j] + 1) % mod;
        else if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
            grid[i][j] = event->button() == Qt::LeftButton;
        repaint();
    }
//        if(mx >= x2 && mx < x2 + w && my >= y && my < y + h) {
//            int i = (mx - x2) / gridSize;
//            int j = (my - y) / gridSize;
//            if(mode == MODE_TOGGLE)
//                grid[i][j] = !grid[i][j];
//            else if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
//                grid[i][j] = event->button() == Qt::LeftButton;
//            repaint();
//        }
}

void BoardWidget::mouseMoveEvent(QMouseEvent *event) {
    if(mode == MODE_DRAW) {
        double gridSize = std::min((width() - PADDING * 2) / boardWidth, (height() - PADDING * 2) / boardHeight);
        int w = floor(gridSize * boardWidth);
        int h = floor(gridSize * boardHeight);
        int x = width() / 2 - w / 2;
//        int x2 = 3 * width() / 4 - w / 2;
        int y = height() / 2 - h / 2;
        int mx = event->x();
        int my = event->y();
        if(mx >= x && mx < x + w && my >= y && my < y + h) {
            int i = (mx - x) / gridSize;
            int j = (my - y) / gridSize;
            if(event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton)
                grid[i][j] = event->buttons() & Qt::LeftButton;
            repaint();
        }
//        if(mx >= x2 && mx < x2 + w && my >= y && my < y + h) {
//            int i = (mx - x2) / gridSize;
//            int j = (my - y) / gridSize;
//            if(event->buttons() & Qt::LeftButton || event->buttons() & Qt::RightButton)
//                grid[i][j] = event->buttons() & Qt::LeftButton;
//            repaint();
//        }
    }
}

void BoardWidget::setBoardSize(int w, int h) {
    boardWidth = w <= 0 ? 1 : w;
    boardHeight = h <= 0 ? 1 : h;
    grid.clear();
    for(int i = 0; i < boardWidth; i++) {
        std::vector<int> vec;
        for(int j = 0; j < boardHeight; j++)
            vec.push_back(0);
        grid.push_back(vec);
    }
    horz = std::vector<int>(boardWidth, 0);
    vert = std::vector<int>(boardHeight, 0);
    for(int i = boardWidth % 3 == 0 ? 1 : 0; i < boardWidth; i += 3)
        horz[i] = 1;
    for(int i = boardHeight % 3 == 0 ? 1 : 0; i < boardHeight; i += 3)
        vert[i] = 1;
    vx1 = 1;
    vx2 = 1;
    vx2 = boardWidth;
    vy2 = boardHeight;
}
void BoardWidget::setView(int x1, int y1, int x2, int y2) {
    if(x1 < 1) x1 = 1;
    if(y1 < 1) y1 = 1;
    if(x2 > boardWidth) x2 = boardWidth;
    if(y2 > boardHeight) y2 = boardHeight;
    if(x2 < x1) x2 = x1;
    if(y2 < y1) y2 = y1;
    vx1 = x1;
    vy1 = y1;
    vx2 = x2;
    vy2 = y2;
    repaint();
}

int BoardWidget::getBoardWidth() {
    return boardWidth;
}
int BoardWidget::getBoardHeight() {
    return boardHeight;
}

int BoardWidget::isOn(int x, int y) {
    int result = grid[x][y];
    if(x > 0) result += grid[x - 1][y];
    if(x < boardWidth - 1) result += grid[x + 1][y];
    if(y > 0) result += grid[x][y - 1];
    if(y < boardHeight-1) result += grid[x][y + 1];
    return result % mod;
}

void BoardWidget::setOffColor(QColor c) {
    offColor = c;
    repaint();
}
void BoardWidget::setOnColor(QColor c) {
    onColor = c;
    repaint();
}
void BoardWidget::setToggle(bool b) {
    mode = MODE_TOGGLE;
}
void BoardWidget::setDraw(bool b) {
    mode = MODE_DRAW;
}
void BoardWidget::setWidth(QString str) {
    setBoardSize(str.toInt(), boardHeight);
    repaint();
}
void BoardWidget::setHeight(QString str) {
    setBoardSize(boardWidth, str.toInt());\
    repaint();
}
void BoardWidget::setMod(QString str) {
    mod = str.toInt();
    if(mod < 2) mod = 2;
    clearBoard();
}
void BoardWidget::setSeed(QString str) {
    seed = str.toInt();
}
void BoardWidget::setClickX(QString str) {
    clickX = str.toInt();
}
void BoardWidget::setClickY(QString str) {
    clickY = str.toInt();
}

void BoardWidget::setXorFilter(int b) {
    xorFilter = b;
    repaint();
}
void BoardWidget::setDrawLines(int b) {
    drawLines = b;
    repaint();
}
//void BoardWidget::setDrawClicks(int b) {
//    drawClicks = b;
//    repaint();
//}
void BoardWidget::setLightChaseOn(int b) {
    lightChaseGreen = b;
}

void BoardWidget::clearBoard() {
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = 0;
    repaint();
}

void BoardWidget::randomBoard() {
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = std::rand() % mod;
    repaint();
}
void BoardWidget::fillBoard() {
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = 1;
    repaint();
}
void BoardWidget::invertBoard() {
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = (mod - grid[i][j]) % mod;
    repaint();
}
void BoardWidget::iterateBoard() {
    int grid2[boardWidth][boardHeight];
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid2[i][j] = isOn(i, j);
    for(int i = 0; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = grid2[i][j];
    repaint();
}
void BoardWidget::click() {
    if(clickX <= 0) clickX = 1;
    if(clickX > boardWidth) clickX = boardWidth;
    if(clickY <= 0) clickY = 1;
    if(clickY > boardHeight) clickY = boardHeight;
    grid[clickX - 1][clickY - 1] = (grid[clickX - 1][clickY - 1] + 1) % mod;
    repaint();
}

void BoardWidget::solveBoard() {
    bool allFilled = true;
    int **goal = (int**) malloc(grid.size() * sizeof(int*));
    for(unsigned int i = 0; i < grid.size(); i++) {
        goal[i] = (int*) malloc(grid[0].size() * sizeof(int));
        for(unsigned int j = 0; j < grid[0].size(); j++) {
            goal[i][j] = grid[i][j];
            if(!goal[i][j])
                allFilled = false;
        }
    }
//         shortcut for 2^n-1 boards
    if(mod == 2 && grid.size() == grid[0].size() && unit(grid.size()) == 0 && allFilled) {
        if(grid.size() % 3 == 0) {
            for(unsigned int i = 0; i < grid.size(); i++) {
                if(i % 3 != 1)
                    grid[i][grid.size()/2] = !grid[i][grid.size()/2];
                grid[i][grid.size()/2+1] = !grid[i][grid.size()/2];
            }
        }else {
            for(unsigned int i = 0; i < grid.size(); i++) {
                if(i % 3 != 0)
                    grid[i][grid.size()/2] = !grid[i][grid.size()/2];
                grid[i][grid.size()/2 + 1] = !grid[i][grid.size()/2];
            }
        }
        lightChaseDown(grid.size()/2 + 1, goal);
        for(unsigned int i = 0; i < grid.size(); i++)
            for(unsigned int j = 0; j < grid.size()/2; j++)
                grid[i][j] = grid[i][grid[0].size()-j-1];
        for(unsigned int i = 0; i < grid.size(); i++)
            free(goal[i]);
        free(goal);
        repaint();
        return;
    }
    for(unsigned int i = 0; i < grid.size(); i++)
        grid[i][0] = false;
    int **matrix = (int**) malloc(grid.size() * sizeof(int*));
    for(unsigned int i = 0; i < grid.size(); i++) {
        matrix[i] = (int*) malloc(grid.size() * sizeof(int));
        grid[i][0] = 1;
        lightChaseDown(0);
        for(unsigned int j = 0; j < grid.size(); j++)
            matrix[i][j] = isOn(j, grid[0].size() - 1);
        grid[i][0] = 0;
    }

    for(unsigned int i = 0; i < grid.size(); i++)
        grid[i][0] = false;
    lightChaseDown(0, goal);
    int *mult = (int*) malloc(grid.size() * sizeof(int));
    for(unsigned int i = 0; i < grid.size(); i++)
        mult[i] = (goal[i][grid[0].size()-1] + mod - isOn(i, grid[0].size()-1)) % mod;
    int *result = GaussianElimination::solve(matrix, mult, grid.size(), seed, mod);
    //clearBoard();
    for(unsigned int i = 0; i < grid.size(); i++)
        grid[i][0] = result[i];
    lightChaseDown(0, goal);
    if(!solved(goal))
        for(unsigned int i = 0; i < grid.size(); i++)
            for(unsigned int j = 0; j < grid[0].size(); j++)
                grid[i][j] = goal[i][j];

    //free allocated memory
    for(unsigned int i = 0; i < grid.size(); i++) {
        free(goal[i]);
        free(matrix[i]);
    }
    free(goal);
    free(matrix);
    free(mult);
    free(result);
    repaint();
}
void BoardWidget::solveBoard2() {
    int *goal = (int*) malloc(boardWidth * boardHeight * sizeof(int));
    int **A = (int**) malloc(boardWidth * boardHeight * sizeof(int*));
    for(int i = 0; i < boardWidth; i++) {
        for(int j = 0; j < boardHeight; j++) {
            goal[boardHeight * i + j] = grid[i][j];
            A[j * boardWidth + i] = (int*) malloc(boardWidth * boardHeight * sizeof(int));
            for(int k = 0; k < boardWidth * boardHeight; k++)
                A[j * boardWidth + i][k] = 0;
            A[j * boardWidth + i][j * boardWidth + i] = 1;
            if(i > 0) A[j * boardWidth + i][j * boardWidth + i - 1] = 1;
            if(i < boardWidth - 1) A[j * boardWidth + i][j * boardWidth + i + 1] = 1;
            if(j > 0) A[j * boardWidth + i][(j - 1) * boardWidth + i] = 1;
            if(j < boardHeight - 1) A[j * boardWidth + i][(j + 1) * boardWidth + i] = 1;
        }
    }
    int *result = GaussianElimination::solve(A, goal, boardWidth * boardHeight, seed, mod);
    for(int i = 0; i < boardWidth * boardHeight; i++) {
        free(A[i]);
        grid[i % boardWidth][i / boardWidth] = result[i];
    }
    free(goal);
    free(A);
    repaint();
}

void BoardWidget::lightChaseRight() {
    for(int i = 1; i < boardWidth; i++)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = (grid[i][j] + lightChaseGreen + mod - isOn(i - 1, j)) % mod;
    repaint();
}
void BoardWidget::lightChaseLeft() {
    for(int i = boardWidth - 2; i >= 0; i--)
        for(int j = 0; j < boardHeight; j++)
            grid[i][j] = (grid[i][j] + lightChaseGreen + mod - isOn(i + 1, j)) % mod;
    repaint();
}
void BoardWidget::lightChaseUp() {
    for(int j = boardHeight - 2; j >= 0; j--)
        for(int i = 0; i < boardWidth; i++)
            grid[i][j] = (grid[i][j] + lightChaseGreen + mod - isOn(i, j + 1)) % mod;
    repaint();
}
void BoardWidget::lightChaseDown() {
    for(int j = 1; j < boardHeight; j++)
        for(int i = 0; i < boardWidth; i++)
            grid[i][j] = (grid[i][j] + lightChaseGreen + mod - isOn(i, j - 1)) % mod;
    repaint();
}

bool BoardWidget::solved(int **goal) {
    for(unsigned int i = 0; i < grid.size(); i++)
        for(unsigned int j = 0; j < grid[0].size(); j++)
            if(isOn(i, j) != goal[i][j])
                return false;
    return true;
}
int BoardWidget::unit(int n) {
    if((n+1)%2 == 0) {
        return unit((n+1)/2-1);
    }else
        return n;
}

void BoardWidget::lightChaseDown(bool lcg) {
    for(unsigned int j = 0; j < grid[0].size() - 1; j++)
        for(unsigned int i = 0; i < grid.size(); i++)
            grid[i][j+1] = (grid[i][j+1] + mod - isOn(i, j) + lcg) % mod;
}
void BoardWidget::lightChaseDown(int row, int **goal) {
    for(unsigned int j = row; j < grid[0].size() - 1; j++)
        for(unsigned int i = 0; i < grid.size(); i++)
            grid[i][j+1] = (grid[i][j+1] + mod - isOn(i, j) + goal[i][j]) % mod;
}
QColor BoardWidget::getColor(int c) {
    int r = (mod - c - 1) * offColor.red() / (mod - 1) + c * onColor.red() / (mod - 1);
    int g = (mod - c - 1) * offColor.green() / (mod - 1) + c * onColor.green() / (mod - 1);
    int b = (mod - c - 1) * offColor.blue() / (mod - 1) + c * onColor.blue() / (mod - 1);
    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;
    return QColor(r, g, b);
}
