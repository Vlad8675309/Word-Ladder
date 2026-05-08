#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <set>
#include <string>

class AnalyticsMode : public QWidget {
	Q_OBJECT

public:
	AnalyticsMode(QWidget* parent = nullptr);

private:
	QLineEdit* usernameEdit;
	QTextEdit* resultDisplay;
	QPushButton* backButton;
	QPushButton* loadButton;

signals:
	void backToMainMenu();

private slots:
	void loadUserData();
	void goBack();

};