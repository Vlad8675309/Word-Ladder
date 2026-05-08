#include "AnalyticsMode.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>

AnalyticsMode::AnalyticsMode(QWidget* parent) : QWidget(parent) {
	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	QHBoxLayout* inputLayout = new QHBoxLayout(this);
	inputLayout->addWidget(new QLabel("Username: "));
	usernameEdit = new QLineEdit(this);
	inputLayout->addWidget(usernameEdit);
	mainLayout->addLayout(inputLayout);

	loadButton = new QPushButton("Load data", this);
	mainLayout->addWidget(loadButton);

	resultDisplay = new QTextEdit(this);
	resultDisplay->setReadOnly(true);
	mainLayout->addWidget(resultDisplay);

	backButton = new QPushButton("Back", this);
	mainLayout->addWidget(backButton);

	connect(loadButton, &QPushButton::clicked, this, &AnalyticsMode::loadUserData);
	connect(backButton, &QPushButton::clicked, this, &AnalyticsMode::backToMainMenu);

}


void AnalyticsMode::loadUserData() {
	QString username = usernameEdit->text();
	if (username.isEmpty()) {
		resultDisplay->setText("Please enter a username");
		return;
	}

	QFile file(username + ".csv");
	if (!file.exists()) {
		resultDisplay->setText("File does not exist for this username");
		return;
	}

	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QTextStream in(&file);
	int totalGames = 0;
	int totalHints = 0;
	std::set<QString> uniqueWords;

	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList parts = line.split(',');
		if (parts.size() >= 6) {
			++totalGames;
			totalHints += parts[parts.size()-3].toInt();

			for (size_t i = 1; i < parts.size() - 3; ++i) {
				uniqueWords.insert(parts[i]);
			}

		}
	}

	file.close();

	QString result;
	result += QString("Total games played: " + QString::number(totalGames));
	result += QString("\nTotal hints used: " + QString::number(totalHints));
	result += QString("\nUnique words: ");
	for (auto word : uniqueWords) {
		result += QString(word + " ");
	}
	resultDisplay->setText(result);

}

void AnalyticsMode::goBack() {
	emit backToMainMenu();
}