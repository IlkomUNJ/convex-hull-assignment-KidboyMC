#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create the main widgets
    drawingWidget = new DrawingWidget(this);
    runButton = new QPushButton("Fix Convex Hull", this);
    clearButton = new QPushButton("Clear Canvas", this);

    // Setup the button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(runButton);
    buttonLayout->addWidget(clearButton);

    // Setup the main vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(drawingWidget);
    mainLayout->addLayout(buttonLayout);

    // Create a central widget to hold the main layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect button signals to the drawing widget's slots
    connect(runButton, &QPushButton::clicked, drawingWidget, &DrawingWidget::runAllConvexHull);
    connect(clearButton, &QPushButton::clicked, drawingWidget, &DrawingWidget::clearCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
