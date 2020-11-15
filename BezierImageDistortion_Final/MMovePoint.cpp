#include "MMovePoint.h"

#include <QPalette>
#include <QPainter>
#include <QPen>

MMovePoint::MMovePoint(QWidget *parent)
	: QLabel(parent)
{
}

MMovePoint::~MMovePoint()
{
}

void MMovePoint::enterEvent(QEvent * event)
{
	setCursor(Qt::OpenHandCursor);
}

void MMovePoint::leaveEvent(QEvent * event)
{
	setCursor(Qt::ArrowCursor);
}

void MMovePoint::setTextColor(std::string color)
{
	QPalette pe;

	if (color.compare("red")==0)
	{
		pe.setColor(QPalette::WindowText, Qt::red);
		setPalette(pe);
	}else if (color.compare("blue") == 0)
	{
		pe.setColor(QPalette::WindowText, Qt::blue);
		setPalette(pe);
	}
}
