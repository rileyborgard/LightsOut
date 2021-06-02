#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    //menubar
    QMenuBar *menuBar = new QMenuBar(this);

    //toolbar
    QToolBar *toolBar = new QToolBar("toolbar", this);
    toolBar->setIconSize(QSize(32, 32));

    QActionGroup *clickActionGroup = new QActionGroup(this);

    //toggle action
    QIcon toggleIcon("toggle.png");
    QAction *toggleAction = new QAction("Toggle", clickActionGroup);
    toggleAction->setCheckable(true);
    toggleAction->setChecked(true);
    toggleAction->setIcon(toggleIcon);
    toggleAction->setShortcut(QKeySequence(Qt::Key_T));
    clickActionGroup->addAction(toggleAction);

    QToolButton *toggleToolButton = new QToolButton;
    toggleToolButton->addAction(toggleAction);
    toggleToolButton->setIcon(toggleIcon);
    toggleToolButton->setCheckable(true);
    toggleToolButton->setChecked(true);
    toggleToolButton->setAutoExclusive(true);
    toolBar->addWidget(toggleToolButton);

    //draw action
    QIcon drawIcon("draw.png");
    QAction *drawAction = new QAction("Draw", clickActionGroup);
    drawAction->setCheckable(true);
    drawAction->setIcon(drawIcon);
    drawAction->setShortcut(QKeySequence(Qt::Key_B));
    clickActionGroup->addAction(drawAction);

    QToolButton *drawToolButton = new QToolButton;
    drawToolButton->addAction(drawAction);
    drawToolButton->setIcon(drawIcon);
    drawToolButton->setCheckable(true);
    drawToolButton->setAutoExclusive(true);
    toolBar->addWidget(drawToolButton);

    //clear action
    QIcon clearIcon("clear.png");
    QAction *clearAction = new QAction("Clear", this);
    clearAction->setShortcut(QKeySequence(Qt::Key_C));
    clearAction->setIcon(clearIcon);
    QToolButton *clearToolButton = new QToolButton;
    clearToolButton->addAction(clearAction);
    clearToolButton->setIcon(clearIcon);
    clearToolButton->setToolTip("Clear");
    toolBar->addWidget(clearToolButton);

    QIcon fillIcon("fill.png");
    QAction *fillAction = new QAction("Fill", this);
    fillAction->setShortcut(QKeySequence(Qt::Key_F));
    fillAction->setIcon(fillIcon);
    QToolButton *fillToolButton = new QToolButton;
    fillToolButton->addAction(fillAction);
    fillToolButton->setIcon(fillIcon);
    fillToolButton->setToolTip("Fill");
    toolBar->addWidget(fillToolButton);

    QIcon randomIcon("random.png");
    QAction *randomAction = new QAction("Random", this);
    randomAction->setShortcut(QKeySequence(Qt::Key_R));
    randomAction->setIcon(randomIcon);
    QToolButton *randomToolButton = new QToolButton;
    randomToolButton->addAction(randomAction);
    randomToolButton->setIcon(randomIcon);
    randomToolButton->setToolTip("Random");
    toolBar->addWidget(randomToolButton);

    QIcon invertIcon("invert.png");
    QAction *invertAction = new QAction("Invert", this);
    invertAction->setShortcut(QKeySequence(Qt::Key_I));
    invertAction->setIcon(invertIcon);
    QToolButton *invertToolButton = new QToolButton;
    invertToolButton->addAction(invertAction);
    invertToolButton->setIcon(invertIcon);
    invertToolButton->setToolTip("Invert");
    toolBar->addWidget(invertToolButton);

    QIcon solveIcon("solve.png");
    QAction *solveAction = new QAction("Solve", this);
    solveAction->setShortcut(QKeySequence(Qt::Key_Left));
    solveAction->setIcon(solveIcon);
    QToolButton *solveToolButton = new QToolButton;
    solveToolButton->addAction(solveAction);
    solveToolButton->setIcon(solveIcon);
    solveToolButton->setToolTip("Solve");
    toolBar->addWidget(solveToolButton);

    QIcon iterateIcon("iterate.png");
    QAction *iterateAction = new QAction("Iterate", this);
    iterateAction->setShortcut(QKeySequence(Qt::Key_Right));
    iterateAction->setIcon(iterateIcon);
    QToolButton *iterateToolButton = new QToolButton;
    iterateToolButton->addAction(iterateAction);
    iterateToolButton->setIcon(iterateIcon);
    iterateToolButton->setToolTip("Iterate");
    toolBar->addWidget(iterateToolButton);

    QIcon saveIcon("save.png");
    QAction *saveAction = new QAction("Save", this);
    saveAction->setShortcut(QKeySequence(Qt::Key_Enter));
    saveAction->setIcon(saveIcon);
    QToolButton *saveToolButton = new QToolButton;
    saveToolButton->addAction(saveAction);
    saveToolButton->setIcon(saveIcon);
    saveToolButton->setToolTip("Save");
    toolBar->addWidget(saveToolButton);

    //menus
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction(saveAction);
    QMenu *editMenu = menuBar->addMenu("Edit");
    editMenu->addActions(clickActionGroup->actions());
    editMenu->addAction(clearAction);
    editMenu->addAction(fillAction);
    editMenu->addAction(randomAction);
    editMenu->addAction(invertAction);
    editMenu->addAction(solveAction);

    addToolBar(Qt::TopToolBarArea, toolBar);
    setMenuBar(menuBar);

    //icon
    setWindowIcon(QIcon("icon.ico"));

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    QFormLayout *formLayout = new QFormLayout;
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollAreaContents = new QWidget(scrollArea);
    QCheckBox *drawLinesCheckBox = new QCheckBox("Draw Lines");
    QCheckBox *lightChaseOnCheckBox = new QCheckBox("Light Chase On");
    QCheckBox *xorFilterCheckBox = new QCheckBox("XOR Filter");
    QLineEdit *modEdit = new QLineEdit("2");
    QLineEdit *solveSeedEdit = new QLineEdit("0");
    QLineEdit *clickXEdit = new QLineEdit("1");
    QLineEdit *clickYEdit = new QLineEdit("1");
    QPushButton *clickButton = new QPushButton("Click");
    QHBoxLayout *buttons[6];
    QColorDialog *offColorDialog = new QColorDialog(QColor(255, 255, 255));
    QColorDialog *onColorDialog = new QColorDialog(QColor(0, 0, 0));
    offColorButton = new QPushButton();
    onColorButton = new QPushButton();
    QGroupBox *lightChaseBox = new QGroupBox("Light Chase");
    QGroupBox *solveBox = new QGroupBox("Solve");
    QGroupBox *viewBox = new QGroupBox("View");
    QFormLayout *lightChaseLayout = new QFormLayout;
    QFormLayout *solveLayout = new QFormLayout;
    QFormLayout *viewLayout = new QFormLayout;
    QPushButton *clearButton = new QPushButton("Clear");
    QPushButton *randomButton = new QPushButton("Random");
    QPushButton *fillButton = new QPushButton("Fill");
    QPushButton *invertButton = new QPushButton("Invert");
    QPushButton *iterateButton = new QPushButton("Iterate");
    QPushButton *solveButton = new QPushButton("Solve");
    QPushButton *solveButton2 = new QPushButton("Solve 2");
    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *lightChaseLeftButton = new QPushButton("Left");
    QPushButton *lightChaseRightButton = new QPushButton("Right");
    QPushButton *lightChaseUpButton = new QPushButton("Up");
    QPushButton *lightChaseDownButton = new QPushButton("Down");

    //color selection
    offColorButton->setMaximumSize(20, 40);
    offColorButton->setStyleSheet("background-color:white;");
    onColorButton->setMaximumSize(20, 40);
    onColorButton->setStyleSheet("background-color:black;");

    //checkbox default states
    xorFilterCheckBox->setChecked(false);
    drawLinesCheckBox->setChecked(true);
    lightChaseOnCheckBox->setChecked(true);

    //buttons layout
    for(int i = 0; i < 6; i++)
        buttons[i] = new QHBoxLayout;
    buttons[0]->addWidget(clearButton);
    buttons[0]->addWidget(randomButton);
    buttons[1]->addWidget(fillButton);
    buttons[1]->addWidget(invertButton);
    buttons[2]->addWidget(iterateButton);
    buttons[3]->addWidget(lightChaseLeftButton);
    buttons[3]->addWidget(lightChaseRightButton);
    buttons[4]->addWidget(lightChaseUpButton);
    buttons[4]->addWidget(lightChaseDownButton);
    buttons[5]->addWidget(solveButton);
    buttons[5]->addWidget(solveButton2);

    //group boxes
    lightChaseLayout->addRow(lightChaseOnCheckBox);
    lightChaseLayout->addRow(buttons[3]);
    lightChaseLayout->addRow(buttons[4]);
    lightChaseBox->setLayout(lightChaseLayout);
    solveLayout->addRow(new QLabel("Seed"), solveSeedEdit);
    solveLayout->addRow(buttons[5]);
    solveBox->setLayout(solveLayout);
    viewLayout->addRow(new QLabel("X1"), viewX1Edit);
    viewLayout->addRow(new QLabel("Y1"), viewY1Edit);
    viewLayout->addRow(new QLabel("X2"), viewX2Edit);
    viewLayout->addRow(new QLabel("Y2"), viewY2Edit);
    viewBox->setLayout(viewLayout);

    //main form layout
    formLayout->addRow(new QLabel("Off Color"), offColorButton);
    formLayout->addRow(new QLabel("On Color"), onColorButton);
    formLayout->addRow(drawLinesCheckBox);
    formLayout->addRow(xorFilterCheckBox);
    formLayout->addRow(new QLabel("Width"), widthEdit);
    formLayout->addRow(new QLabel("Height"), heightEdit);
    formLayout->addRow(new QLabel("Mod"), modEdit);
    for(int i = 0; i < 3; i++)
        formLayout->addRow(buttons[i]);
    formLayout->addRow(saveButton);
    formLayout->addRow(new QLabel("Click x"), clickXEdit);
    formLayout->addRow(new QLabel("Click y"), clickYEdit);
    formLayout->addRow(clickButton);
    formLayout->addRow(lightChaseBox);
    formLayout->addRow(solveBox);
    formLayout->addRow(viewBox);

    scrollAreaContents->setLayout(formLayout);
    scrollArea->setWidget(scrollAreaContents);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumSize(200, 200);
    splitter->addWidget(scrollArea);

    //board dock
    boardWidget = new BoardWidget(splitter);
    boardWidget->setMinimumSize(400, 400);
    splitter->addWidget(boardWidget);
    setCentralWidget(splitter);

    //signals and slots
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));

    connect(toggleAction, SIGNAL(triggered(bool)), boardWidget, SLOT(setToggle(bool)));
    connect(drawAction, SIGNAL(triggered(bool)), boardWidget, SLOT(setDraw(bool)));
    connect(toggleAction, SIGNAL(triggered(bool)), toggleToolButton, SLOT(setChecked(bool)));
    connect(drawAction, SIGNAL(triggered(bool)), drawToolButton, SLOT(setChecked(bool)));
    connect(clearAction, SIGNAL(triggered(bool)), boardWidget, SLOT(clearBoard()));
    connect(fillAction, SIGNAL(triggered(bool)), boardWidget, SLOT(fillBoard()));
    connect(randomAction, SIGNAL(triggered(bool)), boardWidget, SLOT(randomBoard()));
    connect(invertAction, SIGNAL(triggered(bool)), boardWidget, SLOT(invertBoard()));
    connect(solveAction, SIGNAL(triggered(bool)), boardWidget, SLOT(solveBoard()));
    connect(iterateAction, SIGNAL(triggered(bool)), boardWidget, SLOT(iterateBoard()));
    connect(saveAction, SIGNAL(triggered(bool)), boardWidget, SLOT(saveImage()));

    connect(toggleToolButton, SIGNAL(pressed()), toggleAction, SLOT(trigger()));
    connect(drawToolButton, SIGNAL(pressed()), drawAction, SLOT(trigger()));
    connect(clearToolButton, SIGNAL(pressed()), boardWidget, SLOT(clearBoard()));
    connect(fillToolButton, SIGNAL(pressed()), boardWidget, SLOT(fillBoard()));
    connect(randomToolButton, SIGNAL(pressed()), boardWidget, SLOT(randomBoard()));
    connect(invertToolButton, SIGNAL(pressed()), boardWidget, SLOT(invertBoard()));
    connect(solveToolButton, SIGNAL(pressed()), boardWidget, SLOT(solveBoard()));
    connect(iterateToolButton, SIGNAL(pressed()), boardWidget, SLOT(iterateBoard()));
    connect(saveToolButton, SIGNAL(pressed()), boardWidget, SLOT(saveImage()));

    connect(offColorButton, SIGNAL(pressed()), offColorDialog, SLOT(show()));
    connect(onColorButton, SIGNAL(pressed()), onColorDialog, SLOT(show()));
    connect(offColorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(setOffColor(QColor)));
    connect(onColorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(setOnColor(QColor)));

    connect(widthEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setWidth(QString)));
    connect(heightEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setHeight(QString)));
    connect(widthEdit, SIGNAL(textChanged(QString)), this, SLOT(updateView()));
    connect(heightEdit, SIGNAL(textChanged(QString)), this, SLOT(updateView()));

    connect(viewX1Edit, SIGNAL(textChanged(QString)), this, SLOT(setView()));
    connect(viewY1Edit, SIGNAL(textChanged(QString)), this, SLOT(setView()));
    connect(viewX2Edit, SIGNAL(textChanged(QString)), this, SLOT(setView()));
    connect(viewY2Edit, SIGNAL(textChanged(QString)), this, SLOT(setView()));

    connect(modEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setMod(QString)));
    connect(clickXEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setClickX(QString)));
    connect(clickYEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setClickY(QString)));
    connect(solveSeedEdit, SIGNAL(textChanged(QString)), boardWidget, SLOT(setSeed(QString)));

    connect(xorFilterCheckBox, SIGNAL(stateChanged(int)), boardWidget, SLOT(setXorFilter(int)));
    connect(drawLinesCheckBox, SIGNAL(stateChanged(int)), boardWidget, SLOT(setDrawLines(int)));
    connect(lightChaseOnCheckBox, SIGNAL(stateChanged(int)), boardWidget, SLOT(setLightChaseOn(int)));

    connect(clearButton, SIGNAL(pressed()), clearAction, SLOT(trigger()));
    connect(randomButton, SIGNAL(pressed()), randomAction, SLOT(trigger()));
    connect(fillButton, SIGNAL(pressed()), fillAction, SLOT(trigger()));
    connect(invertButton, SIGNAL(pressed()), invertAction, SLOT(trigger()));
    connect(solveButton, SIGNAL(pressed()), solveAction, SLOT(trigger()));
    connect(solveButton2, SIGNAL(pressed()), solveAction, SLOT(trigger()));
    connect(iterateButton, SIGNAL(pressed()), iterateAction, SLOT(trigger()));
    connect(saveButton, SIGNAL(pressed()), saveAction, SLOT(trigger()));

    connect(clickButton, SIGNAL(pressed()), boardWidget, SLOT(click()));

    connect(lightChaseLeftButton, SIGNAL(pressed()), boardWidget, SLOT(lightChaseLeft()));
    connect(lightChaseRightButton, SIGNAL(pressed()), boardWidget, SLOT(lightChaseRight()));
    connect(lightChaseUpButton, SIGNAL(pressed()), boardWidget, SLOT(lightChaseUp()));
    connect(lightChaseDownButton, SIGNAL(pressed()), boardWidget, SLOT(lightChaseDown()));

    //start timer
//    timer->start(50);
}

MainWindow::~MainWindow() {

}

void MainWindow::setView() {
    boardWidget->setView(viewX1Edit->text().toInt(), viewY1Edit->text().toInt(),
                         viewX2Edit->text().toInt(), viewY2Edit->text().toInt());
}
void MainWindow::updateView() {
    viewX1Edit->setText("1");
    viewY1Edit->setText("1");
    viewX2Edit->setText(widthEdit->text());
    viewY2Edit->setText(heightEdit->text());
}
void MainWindow::setOffColor(QColor c) {
    offColorButton->setStyleSheet("background-color: #"
          + QString(c.red() < 16? "0" : "") + QString::number(c.red(),16)
          + QString(c.green() < 16? "0" : "") + QString::number(c.green(),16)
          + QString(c.blue() < 16? "0" : "") + QString::number(c.blue(),16) + ";");
    boardWidget->setOffColor(c);
}
void MainWindow::setOnColor(QColor c) {
    onColorButton->setStyleSheet("background-color: #"
          + QString(c.red() < 16? "0" : "") + QString::number(c.red(),16)
          + QString(c.green() < 16? "0" : "") + QString::number(c.green(),16)
          + QString(c.blue() < 16? "0" : "") + QString::number(c.blue(),16) + ";");
    boardWidget->setOnColor(c);
}
