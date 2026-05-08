#pragma once
#include "Graph.h"
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class PlayingMode : public QWidget {
    Q_OBJECT

public:
    PlayingMode(QWidget* parent = nullptr);
    void startNewGame();

    QString username;

signals:
    void backToMainMenu();

private:
    Graph<std::string> graph;
    std::string currentWord;
    std::string targetWord;
    int wordLength;
    int hintsUsed;
    std::vector<std::string> userPath;

    QLineEdit* usernameEdit;
    QLabel* wordLengthLabel;
    QComboBox* wordLengthCombo;
    QLabel* currentWordLabel;
    QLabel* targetWordLabel;
    QLineEdit* userInput;
    QPushButton* submitButton;
    QPushButton* hintButton;
    QPushButton* backButton;
    QTextEdit* gameLog;
    QLabel* hintLabel;

private slots:
    void setupGame();
    void processInput();
    void giveHint();
    void goBack();
};