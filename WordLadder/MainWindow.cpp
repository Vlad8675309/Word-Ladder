#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Word Ladder Game");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QPushButton* automaticButton = new QPushButton("Automatic Mode", this);
    QPushButton* playingButton = new QPushButton("Playing Mode", this);
    QPushButton* analyticsButton = new QPushButton("Analytics Mode", this);

    mainLayout->addWidget(new QLabel("Select Game Mode:", this));
    mainLayout->addWidget(automaticButton);
    mainLayout->addWidget(playingButton);
    mainLayout->addWidget(analyticsButton);
    mainLayout->addStretch();

    // Create stacked widget for different modes
    stackedWidget = new QStackedWidget(this);
    automaticMode = new AutomaticMode(this);
    playingMode = new PlayingMode(this);
    analyticsMode = new AnalyticsMode(this);

    stackedWidget->addWidget(centralWidget); // Index 0 - main menu
    stackedWidget->addWidget(automaticMode); // Index 1
    stackedWidget->addWidget(playingMode);   // Index 2
    stackedWidget->addWidget(analyticsMode); // Index 3

    QVBoxLayout* stackedLayout = new QVBoxLayout();
    stackedLayout->addWidget(stackedWidget);
    QWidget* container = new QWidget(this);
    container->setLayout(stackedLayout);
    setCentralWidget(container);

    // Connect buttons to slots
    connect(automaticButton, &QPushButton::clicked, this, &MainWindow::showAutomaticMode);
    connect(playingButton, &QPushButton::clicked, this, &MainWindow::showPlayingMode);
    connect(analyticsButton, &QPushButton::clicked, this, &MainWindow::showAnalyticsMode);

    connect(automaticMode, &AutomaticMode::backToMainMenu, this, [this]() {
        stackedWidget->setCurrentIndex(0); 
        });

    connect(playingMode, &PlayingMode::backToMainMenu, this, [this]() {
       stackedWidget->setCurrentIndex(0); 
        });

    connect(analyticsMode, &AnalyticsMode::backToMainMenu, this, [this]() {
       stackedWidget->setCurrentIndex(0); // Switch to main menu
        });
}

void MainWindow::showAutomaticMode() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPlayingMode() {
    stackedWidget->setCurrentIndex(2);
    //playingMode->startNewGame();
}

void MainWindow::showAnalyticsMode() {
    stackedWidget->setCurrentIndex(3);
}