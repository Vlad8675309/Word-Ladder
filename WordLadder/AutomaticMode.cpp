#include "AutomaticMode.h"
#include "Algorithms.h"
#include <unordered_map>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include "Graph.h"


AutomaticMode::AutomaticMode(QWidget* parent) : QWidget(parent) {

	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	QLabel* startWordLabel = new QLabel("Enter starting word: ", this);
	QLabel* targetWordLabel = new QLabel("Enter target word: ", this);

	QHBoxLayout* inputLayout = new QHBoxLayout();

	inputLayout->addWidget(startWordLabel);
	startWordEdit = new QLineEdit(this);
	inputLayout->addWidget(startWordEdit);

	inputLayout->addWidget(targetWordLabel);
	targetWordEdit = new QLineEdit(this);
	inputLayout->addWidget(targetWordEdit);

	mainLayout->addLayout(inputLayout);

	findPathButton = new QPushButton("Find Path", this);
	mainLayout->addWidget(findPathButton);

	resultDisplay = new QTextEdit(this);
	resultDisplay->setText("Result");
	resultDisplay->setReadOnly(true);
	mainLayout->addWidget(resultDisplay);

	backButton = new QPushButton("Back", this);
	mainLayout->addWidget(backButton);

	connect(findPathButton, &QPushButton::clicked, this, &AutomaticMode::findWordPath);
	connect(backButton, &QPushButton::clicked, this, &AutomaticMode::goBack);
}

void AutomaticMode::findWordPath() {
	QString start = startWordEdit->text().toUpper();
	QString target = targetWordEdit->text().toUpper();

	if (start.isEmpty() || target.isEmpty()) {
		QMessageBox::warning(this, "Error", "Please enter both start and target words!");
		return;
	}

	if (start.length() != target.length()) {
		QMessageBox::warning(this, "Error", "Please enter same length words!");
		return;
	}

	std::string stdStart = start.toLower().toStdString();
	std::string stdTarget = target.toLower().toStdString();

	std::unordered_map<std::string, std::vector<std::string>> patternMap = Algorithms::buildPatternMap("dictionary.txt");
	graph = Algorithms::buildWordGraph(patternMap);

	if (graph.getAdjacencyList().find(stdStart) == graph.getAdjacencyList().end() || graph.getAdjacencyList().find(stdTarget) == graph.getAdjacencyList().end()) {
		QMessageBox::warning(this, "Error", "One or both words not found in the dictionary!");
		return;
	}

	std::vector<std::string> path = graph.findPath(stdStart, stdTarget);

	if (path.empty()) {
		resultDisplay->setText("No path exists between these words.");
	}
	else {
		QString result;
		for (const auto& word : path) {
			result += QString::fromStdString(word) + "\n";
		}
		resultDisplay->setText(result);
	}

}

void AutomaticMode::goBack() {
	emit backToMainMenu();
}