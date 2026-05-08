#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include "AutomaticMode.h"
#include "PlayingMode.h"
#include "AnalyticsMode.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QStackedWidget* stackedWidget;
    AutomaticMode* automaticMode;
    PlayingMode* playingMode;
    AnalyticsMode* analyticsMode;

private slots:
    void showAutomaticMode();
    void showPlayingMode();
    void showAnalyticsMode();
};
