#pragma once

#include <QLabel>
#include <string>
#include <QMouseEvent>
#include <QEvent>

class MMovePoint : public QLabel
{
	Q_OBJECT

public:
	MMovePoint(QWidget *parent=Q_NULLPTR);
	~MMovePoint();
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

public:
	void setTextColor(std::string color);
};
