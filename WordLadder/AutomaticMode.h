#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "Graph.h"
#include <string>

class AutomaticMode : public QWidget {
	Q_OBJECT
public:

	AutomaticMode(QWidget* parent = nullptr);

private:
	Graph<std::string> graph;

	QPushButton* findPathButton;
	QPushButton* backButton;

	QLineEdit* startWordEdit;
	QLineEdit* targetWordEdit;

	QTextEdit* resultDisplay;

signals:
	void backToMainMenu();

private slots:
	void goBack();
	void findWordPath();
};