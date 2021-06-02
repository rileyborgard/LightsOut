#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#define PADDING 20.0
#define MODE_TOGGLE 0
#define MODE_DRAW 1

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QColor>
#include <math.h>
#include <QPixmap>
#include <QFile>
#include "gaussianelimination.h"

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void update(int x, int y, int w, int h);
    void setBoardSize(int w, int h);
    void setView(int x1, int y1, int x2, int y2);
    int getBoardWidth();
    int getBoardHeight();
    int isOn(int x, int y);
public slots:
    void setOffColor(QColor c);
    void setOnColor(QColor c);

    void setToggle(bool b);
    void setDraw(bool b);

    void setWidth(QString str);
    void setHeight(QString str);
    void setMod(QString str);
    void setSeed(QString str);
    void setClickX(QString str);
    void setClickY(QString str);

    void setXorFilter(int b);
    void setDrawLines(int b);
    void setLightChaseOn(int b);

    void clearBoard();
    void randomBoard();
    void solveBoard();
    void solveBoard2();
    void fillBoard();
    void invertBoard();
    void iterateBoard();
    void click();
    void saveImage();

    void lightChaseLeft();
    void lightChaseRight();
    void lightChaseUp();
    void lightChaseDown();
private:
    bool solved(int **goal);
    void lightChaseDown(bool lcg);
    void lightChaseDown(int row, int **goal);
    int unit(int n);
    QColor getColor(int c);
    QColor offColor;
    QColor onColor;
    std::vector<std::vector<int> > grid;
    std::vector<int> vert;
    std::vector<int> horz;
    int vx1;
    int vy1;
    int vx2;
    int vy2;

    int mod;
    int boardWidth;
    int boardHeight;
    int seed;
    int clickX;
    int clickY;
    int mode;
    bool lightChaseGreen;
    bool xorFilter;
    bool drawLines;
};

#endif // BOARDWIDGET_H
