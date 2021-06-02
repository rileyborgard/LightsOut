#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardwidget.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QCheckBox>
#include <QDockWidget>
#include <QIcon>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QKeyEvent>
#include <QApplication>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QString>
#include <QToolButton>
#include <QSize>
#include <QSplitter>
#include <QMenuBar>
#include <QActionGroup>
#include <QKeySequence>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void setView();
    void updateView();
    void setOffColor(QColor c);
    void setOnColor(QColor c);
private:
    QLineEdit *widthEdit = new QLineEdit("5");
    QLineEdit *heightEdit = new QLineEdit("5");
    QLineEdit *viewX1Edit = new QLineEdit("1");
    QLineEdit *viewY1Edit = new QLineEdit("1");
    QLineEdit *viewX2Edit = new QLineEdit("5");
    QLineEdit *viewY2Edit = new QLineEdit("5");

    BoardWidget *boardWidget;
    QPushButton *offColorButton;
    QPushButton *onColorButton;
};

#endif // MAINWINDOW_H
