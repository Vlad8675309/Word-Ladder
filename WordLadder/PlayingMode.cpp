#include "PlayingMode.h"
#include <QWidget>
#include <QVBoxLayout>
#include <random>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include "Algorithms.h"

PlayingMode::PlayingMode(QWidget* parent) : QWidget(parent), hintsUsed(0) {

	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

    QHBoxLayout* usernameLayout = new QHBoxLayout();
    QLabel* usernameLabel = new QLabel("Enter username: ");
    usernameEdit = new QLineEdit(this);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    mainLayout->addLayout(usernameLayout);


    QHBoxLayout* lengthLayout = new QHBoxLayout();
    wordLengthLabel = new QLabel("Select word length:", this);
    wordLengthCombo = new QComboBox(this);
    for (int i = 3; i <= 16; ++i) {
        wordLengthCombo->addItem(QString::number(i));
    }
    lengthLayout->addWidget(wordLengthLabel);
    lengthLayout->addWidget(wordLengthCombo);
    mainLayout->addLayout(lengthLayout);


    QPushButton* setupButton = new QPushButton("Start New Game", this);
    mainLayout->addWidget(setupButton);


    currentWordLabel = new QLabel("Current word: ", this);
    targetWordLabel = new QLabel("Target word: ", this);
    mainLayout->addWidget(currentWordLabel);
    mainLayout->addWidget(targetWordLabel);

  
    userInput = new QLineEdit(this);
    mainLayout->addWidget(userInput);


    QHBoxLayout* buttonLayout = new QHBoxLayout();
    submitButton = new QPushButton("Submit", this);
    hintButton = new QPushButton("Hint", this);
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(hintButton);
    mainLayout->addLayout(buttonLayout);


    hintLabel = new QLabel(this);
    hintLabel->setWordWrap(true);
    mainLayout->addWidget(hintLabel);


    gameLog = new QTextEdit(this);
    gameLog->setReadOnly(true);
    mainLayout->addWidget(gameLog);

    backButton = new QPushButton("Back", this);
    mainLayout->addWidget(backButton);

    connect(setupButton, &QPushButton::clicked, this, &PlayingMode::setupGame);
    connect(submitButton, &QPushButton::clicked, this, &PlayingMode::processInput);
    connect(hintButton, &QPushButton::clicked, this, &PlayingMode::giveHint);
    connect(backButton, &QPushButton::clicked, this, &PlayingMode::goBack);
}


void PlayingMode::startNewGame() {
    setupGame();
}

void PlayingMode::setupGame() {
    username = usernameEdit->text();

    wordLength = wordLengthCombo->currentText().toInt();
    auto patternMap = Algorithms::buildPatternMap("dictionary.txt", true, wordLength);
    graph = Algorithms::buildWordGraph(patternMap);

    std::vector<std::string> words;
    for (const auto& pair : graph.getAdjacencyList()) {
        words.push_back(pair.first);
    }

    currentWord = words[rand() % words.size()];
    targetWord = words[rand() % words.size()];
    while (targetWord == currentWord) {
         targetWord = words[rand() % words.size()];
    }

    hintsUsed = 0;
    userPath.clear();
    userPath.push_back(currentWord);

    currentWordLabel->setText("Current word: " + QString::fromStdString(currentWord));
    targetWordLabel->setText("Target word: " + QString::fromStdString(targetWord));
    gameLog->clear();
    gameLog->append("Game started! Try to reach from " + QString::fromStdString(currentWord) +
        " to " + QString::fromStdString(targetWord));
    hintLabel->clear();
    userInput->clear();

}

void PlayingMode::processInput() {
    QString input = userInput->text().toLower();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a word");
        return;
    }

    std::string newWord = input.toStdString();
    if (graph.getAdjacencyList().find(newWord) == graph.getAdjacencyList().end()) {
        gameLog->append("Invalid word: " + input + " (not in dictionary)");
        return;
    }

    int diffCount = 0;
    for (size_t i = 0; i < currentWord.size(); ++i) {
        if (i >= newWord.size() || currentWord[i] != newWord[i]) {
            diffCount++;
        }
    }

    if (diffCount != 1) {
        gameLog->append("Invalid move: You must change only 1 letter! Try again!");
    }

    currentWord = newWord;
    userPath.push_back(currentWord);
    currentWordLabel->setText("Current word: " + QString::fromStdString(currentWord));
    gameLog->append("-> " + QString::fromStdString(currentWord));

    if (currentWord == targetWord) {
        auto optimalPath = graph.findPath(userPath.front(), targetWord);

        QString result = "\nCongratulations! You won!\n";
        result += "Your path (" + QString::number(userPath.size() - 1) + " steps):\n";
        for (const auto& word : userPath) {
            result += QString::fromStdString(word) + "\n";
        }

        result += "\nOptimal path (" + QString::number(optimalPath.size() - 1) + " steps):\n";
        for (const auto& word : optimalPath) {
            result += QString::fromStdString(word) + "\n";
        }

        result += "\nHints used: " + QString::number(hintsUsed);
        gameLog->append(result);

        // Save game results
        
        QFile file(username + ".csv");
       
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << ",";
            for (auto word : userPath) {
                out << QString().fromStdString(word) << ",";
            }
            out << hintsUsed << ","
                << (userPath.size() - 1) << ","
                << (optimalPath.size() - 1) << "\n";
            file.close();
        }
    }
}

void PlayingMode::giveHint() {

    ++hintsUsed;

    auto optimalPath = graph.findPath(currentWord, targetWord);
    std::string nextWord = optimalPath[1];

    int position = -1;
    for (size_t i = 0; i < nextWord.size(); ++i) {
        if (nextWord[i] != currentWord[i]) {
            position = i;
            break;
        }
    }

    if (position >= 0) {
        gameLog->undo();
        QString colouredWord;
        QString hiddenWord = "<span style = 'color:white;'>" + QString::fromStdString(nextWord) +"</span>";
        colouredWord += "-> ";
        for (size_t i = 0; i < currentWord.size(); ++i) {
            if (i == position) {
                colouredWord += "<span style='color:red;'>" + QString(currentWord[position]) + "</span>";
            }
            else {
                colouredWord += QString(currentWord[i]);
            }
        }
        gameLog->append(QString(colouredWord));
        //gameLog->append(QString(colouredWord+hiddenWord));
    }

}

void PlayingMode::goBack() {
    emit backToMainMenu();
}