#include "BezierImageDistortion_Final.h"

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QPalette>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include <algorithm>

BezierImageDistortion_Final::BezierImageDistortion_Final(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initMembers();
	connectAll();
}

void BezierImageDistortion_Final::mousePressEvent(QMouseEvent * event)
{
	QWidget *w = this->childAt(event->pos());
	if (w == nullptr) return;
	if (w->inherits("MMovePoint"))
	{
		selected_widget = w;
	}
}

void BezierImageDistortion_Final::mouseReleaseEvent(QMouseEvent * event)
{
	if (selected_widget)
	{
		SET_NULL(selected_widget);
	}
	
}

void BezierImageDistortion_Final::mouseMoveEvent(QMouseEvent * event)
{
	if (selected_widget != Q_NULLPTR)
	{
		selected_widget->move(event->pos());
		lab->update();
	}
}


bool BezierImageDistortion_Final::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == lab)
	{
		if (event->type() == QEvent::Paint)
		{
			DELETE_OBJ(t_draw);
			t_draw = new boost::thread(&BezierImageDistortion_Final::paint,this);
			t_draw->join();
			//paint();
			return true;
		}

	}


	return QMainWindow::eventFilter(watched, event);
}

void BezierImageDistortion_Final::initMembers()
{
	setWindowTitle("960x720");
	
	for (int i=1;i<11;++i)
	{
		ui.comboBox_count->addItem(
			QString(lexical_cast<string>(i).c_str())
		);
	}

	lab = new QLabel(this);
	lab->setGeometry(ui.label_show->geometry().x(), ui.label_show->geometry().y()+CTL_POINT_ZISE*3, ui.label_show->width(), ui.label_show->height());

	lab->installEventFilter(this);
	
	drawPoints();


	loadDefaultImg();
	//loadDefaultVideo();
}

void BezierImageDistortion_Final::connectAll()
{
	/*************************QAction****************************/
	connect(ui.action_open_test_img, &QAction::triggered,
		[=]()mutable
	{
		if (t_show_v)
		{
			DELETE_OBJ(t_show_v);
			cap.release();
		}

		path_img = DEFAULT_IMAGE;
		DELETE_OBJ(t_show);
		t_show = new boost::thread(
			[=]()mutable
		{
			mat_image = imread(path_img);
			cvtColor(mat_image, mat_image, COLOR_BGR2RGB);
			addToLabel(mat_image, ui.label_show);
		}
		);
	}

	);
	connect(ui.action_open_image,&QAction::triggered,
		[=]()mutable
	{
		if (t_show_v)
		{
			DELETE_OBJ(t_show_v);
			cap.release();
		}
		path_img = QFileDialog::getOpenFileName(this,
			QString::fromLocal8Bit("打开图片"),
			"./",
			"image(*.png *.jpeg *.jpg *.bmp)").toLocal8Bit().toStdString();

		if (!path_img.empty())
		{
			DELETE_OBJ(t_show);
			t_show = new boost::thread(
				[=]()mutable
			{
				mat_image = imread(path_img);
				cvtColor(mat_image, mat_image, COLOR_BGR2RGB);
				addToLabel(mat_image, ui.label_show);
			}
			);
		}

	}
		);
	connect(ui.action_open_video, &QAction::triggered,
		[=]()mutable
	{
		setWindowTitle(QString::fromLocal8Bit("960x720 正在打开......."));
		loadDefaultVideo();
		setWindowTitle("960x720");
	}
		
	);

	/*******************************QComboBox************************************/
	connect(ui.comboBox_count,&QComboBox::currentTextChanged,
		[=]()mutable
	{
		drawPoints();
	}
		);

	/********************************QSpinBox*********************************************/
	void (QSpinBox::*p_valueChanged)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox_grid_x, p_valueChanged,
		[=]()mutable
	{
		lab->setGeometry(ui.label_show->geometry().x()+ui.spinBox_grid_x->value(), ui.label_show->geometry().y() + CTL_POINT_ZISE * 3 + ui.spinBox_grid_y->value(), ui.label_show->width(), ui.label_show->height());
		
	}
		);
	connect(ui.spinBox_grid_y, p_valueChanged,
		[=]()mutable
	{
		lab->setGeometry(ui.label_show->geometry().x() + ui.spinBox_grid_x->value(), ui.label_show->geometry().y() + CTL_POINT_ZISE * 3 +ui.spinBox_grid_y->value(), ui.label_show->width(), ui.label_show->height());
	}
	);
	
}

void BezierImageDistortion_Final::addToLabel(Mat &input, QLabel * output)
{
	qimg = QImage(input.data,
		input.cols,
		input.rows,
		input.cols*input.channels(),
		QImage::Format::Format_RGB888
	);
	output->setPixmap(QPixmap::fromImage(qimg));
	output->update();
}

void BezierImageDistortion_Final::loadDefaultImg()
{
	t_show = new boost::thread(
		[=]()mutable
	{
		mat_image = imread(DEFAULT_IMAGE);
		cvtColor(mat_image, mat_image, COLOR_BGR2RGB);
		addToLabel(mat_image, ui.label_show);

	}
	);
}

void BezierImageDistortion_Final::loadDefaultVideo()
{
	if (!t_show_v)
	{
		cap.open(0);
		if (!cap.isOpened())
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未检测到摄像头."));
			return;
		} else
		{
			cap.set(CAP_PROP_FRAME_WIDTH, FRAME_WIDGET);
			cap.set(CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
			t_show_v = new boost::thread(
				[=]()mutable
			{
				while (1)
				{
					cap >> mat_frame;
					if (mat_frame.empty())
					{
						break;
					}
					cvtColor(mat_frame, mat_frame, COLOR_BGR2RGB);
					addToLabel(mat_frame, ui.label_show);

					waitKey(10);
				}

			}
			);
		}

	}
}

void BezierImageDistortion_Final::drawPoints()
{
	v_grid_point.clear();
	if (!v_move_point.empty())
	{
		for (int i = 0; i < v_move_point.size(); ++i)
		{
			DELETE_OBJ(v_move_point[i]);
		}
	}
	v_move_point.clear();
	::system("cls");
	c_grid = lexical_cast<int>(ui.comboBox_count->currentText().toLocal8Bit().toStdString()) + 1;
	step_r = ui.label_show->width() / (c_grid-1);
	step_c = ui.label_show->height() / (c_grid - 1);

	for (int row=0; row <= ui.label_show->height();row+=step_c)
	{
		vector<Point> v_p;
		for (int col = 0; col <= ui.label_show->width(); col+= step_r)
		{
			push_back(v_p)
				(Point(
					col,	//x
					row	//y
				));

			MMovePoint *mp=new MMovePoint(lab);
			/*if (
				(row == 0 && col == 0)||
				(row == 0 && col == ui.label_show->width())||
				(row == ui.label_show->height() && col == 0) ||
				(row == ui.label_show->height() && col == ui.label_show->width())
				)
			{
				mp->setStyleSheet("QLabel{background-color:red;}");
			} else
			{
				mp->setStyleSheet("QLabel{background-color:blue;}");
			}*/
			mp->setStyleSheet("QLabel{background-color:red;}");
			if (col >= ui.label_show->width())//最后一列
			{
				if (row==0)//处理右上角的那个点
				{
					mp->setGeometry(ui.label_show->width() - CTL_POINT_ZISE, row + CTL_POINT_ZISE, CTL_POINT_ZISE, CTL_POINT_ZISE);
				} else if (row >= ui.label_show->height())//右下角
				{
					mp->setGeometry(ui.label_show->width() - CTL_POINT_ZISE, ui.label_show->height() - CTL_POINT_ZISE, CTL_POINT_ZISE, CTL_POINT_ZISE);
				} else
				{
					mp->setGeometry(ui.label_show->width() - CTL_POINT_ZISE, row, CTL_POINT_ZISE, CTL_POINT_ZISE);
				}
				
			}else if (row == 0)//处理第一行
			{
				mp->setGeometry(col, row + CTL_POINT_ZISE, CTL_POINT_ZISE, CTL_POINT_ZISE);
			}else if (row >= ui.label_show->height())//最后一行
			{

				mp->setGeometry(col, ui.label_show->height() - CTL_POINT_ZISE, CTL_POINT_ZISE, CTL_POINT_ZISE);
			}
			else
			{
				mp->setGeometry(col, row, CTL_POINT_ZISE, CTL_POINT_ZISE);
				
			}
			push_back(v_move_point)(mp);
		}
		push_back(v_grid_point)
			(v_p);
	}
	lab->update();

	//Debug
	/*for (int i=0;i<v_grid_point.size();++i)
	{
		for (int j=0;j<v_grid_point[i].size();++j)
		{
			COUT "( " LK v_grid_point[i][j].x LK " , " LK v_grid_point[i][j].y LK " )" LN;
		}
		COUT_LN;
	}*/


	for (int i = 0; i < v_move_point.size(); ++i)
	{
		v_move_point[i]->show();
	}
}

void BezierImageDistortion_Final::paint()
{
	QPainter painter(lab);
	QPen pen;
	pen.setWidth(3);
	pen.setColor(QColor(0, 0, 255));

	painter.setPen(pen);

	//int ind = 0;
	//for (double t = 0; t <= 1.0; t += 0.001)
	//{
	//	double t1 = 1 - t;
	//	int x=0, y=0;

	//	for (ind=0;ind < v_grid_point[0].size();++ind)
	//	{
	//		/*x += C((v_grid_point[ind].size() - 1), ind)*v_move_point[ind]->geometry().x()*pow(t1, (v_grid_point[ind].size() - 1 - ind))*pow(t, ind);
	//		y += C((v_grid_point[ind].size() - 1), ind)*v_move_point[ind]->geometry().y()*pow(t1, (v_grid_point[ind].size() - 1 - ind))*pow(t, ind);

	//		if (ind == v_grid_point[ind].size())
	//		{
	//			break;
	//		}*/
	//	}
	//	painter.drawPoint(x, y);
	//	
	//}

	v_bezier_rows.clear();
	/***********************************行*****************************************/
	int x;
	int y;
	int start = 0;
	for (int i_ = 0; i_ < v_grid_point.size(); ++i_)
	{
		vector<Point> vp;
		for (double t = 0; t <= 1.0; t += ui.doubleSpinBox_bzRow->value())
		{
			double t1 = 1 - t;
			x = 0;
			y = 0;
			for (int i = start; i < v_grid_point[i_].size()+start; ++i)
			{
				/*
					带入 bezier 通项公式  若曲线(包括两个端点)有 N+1 个控制点，则为N阶

                    n
					Σ  [ C(N,i)Pi*pow(1-t,n-i)*pow(t,i) ]
				   i=0	

				   其中：
						N 为阶数  
						t ∈ [0,1]
						i [0,n]
				*/
				
				if (i==0)
				{
					x += C((v_grid_point[i_].size() - 1), i)*
						v_move_point[i]->geometry().x()*
						pow(t1, ((v_grid_point[i_].size() - 1) - i))*
						pow(t, i);

					y += C((v_grid_point[i_].size() - 1), i)*
						v_move_point[i]->geometry().y()*
						pow(t1, ((v_grid_point[i_].size() - 1) - i))*
						pow(t, i);
				} else
				{
					x += C((v_grid_point[i_].size() - 1), (i - (v_grid_point[i_].size()*i_)))*
						v_move_point[i]->geometry().x()*
						pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
						pow(t, (i - (v_grid_point[i_].size()*i_)));

					y += C((v_grid_point[i_].size() - 1), (i - (v_grid_point[i_].size()*i_)))*
						v_move_point[i]->geometry().y()*
						pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
						pow(t, (i - (v_grid_point[i_].size()*i_)));
				}
				
				if (i< v_grid_point[i_].size() + start-1)
				{
					pen.setWidth(2);
					pen.setColor(QColor(0, 0, 0));
					painter.setPen(pen);
					painter.drawLine(v_move_point[i]->geometry().x(), v_move_point[i]->geometry().y(),
						v_move_point[i + 1]->geometry().x(), v_move_point[i + 1]->geometry().y()
					);
				}
				pen.setWidth(3);
				pen.setColor(QColor(0, 0, 255));
				painter.setPen(pen);

			}
			painter.drawPoint(x, y);
			push_back(vp)(Point(x,y));
		}
		start += v_grid_point[i_].size();
		push_back(v_bezier_rows)(vp);
	}
	//连线构成bezier曲线
	for (int i = 0; i < v_bezier_rows.size(); ++i)
	{
		for (int j = 0; j < v_bezier_rows[i].size() - 1; ++j)
		{
			painter.drawLine(v_bezier_rows[i][j].x, v_bezier_rows[i][j].y, v_bezier_rows[i][j + 1].x, v_bezier_rows[i][j + 1].y);
		}
	}

	/***********************************行*****************************************/


	/***********************************列*****************************************/

	int x2;
	int y2;
	int start2 = 0;
	for (int i_ = 0; i_ < v_grid_point.size(); ++i_)
	{
		for (double t = 0; t <= 1.0; t += 0.001)
		{
			double t1 = 1 - t;
			x2 = 0;
			y2 = 0;
			for (int i = start2; i < v_grid_point[i_].size() + start2; ++i)
			{
				/*
					带入 bezier 通项公式

					n
					Σ  [ C(N,i)Pi*pow(1-t,n-i)*pow(t,i) ]
				   i=0

				   其中：
						N 为阶数  若曲线(包括两个端点)有 N+1 个控制点，则为N阶
						t ∈ [0,1]
						i ∈ [0,n]

						Pi为第i个点的坐标
				*/
				if (start2==0)
				{
					x2 += C((v_grid_point[i_].size() - 1), (i - (v_grid_point[i_].size()*i_)))*
						v_move_point[((i - (v_grid_point[i_].size()*i_)) + ((v_grid_point[i_].size() - 1)* (i - (v_grid_point[i_].size()*i_))))]->geometry().x()*pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
						pow(t, (i - (v_grid_point[i_].size()*i_)));
					y2 += C((v_grid_point[i_].size() - 1), (i - (v_grid_point[i_].size()*i_)))*
						v_move_point[((i - (v_grid_point[i_].size()*i_)) + ((v_grid_point[i_].size() - 1)* (i - (v_grid_point[i_].size()*i_))))]->geometry().y()*pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
						pow(t, (i - (v_grid_point[i_].size()*i_)));
				} else
				{
					//x2 += C((v_grid_point[i_].size() - 1), (i-i_))*/*这里有问题  i-i_为 0 1 2*/
					//	v_move_point[((i - (v_grid_point[i_].size()*i_)) + ((v_grid_point[i_].size() - 1)* (i - (v_grid_point[i_].size()*i_))))]->geometry().x()*pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
					//	pow(t, (i - (v_grid_point[i_].size()*i_)));
					//y2 += C((v_grid_point[i_].size() - 1), (i - (v_grid_point[i_].size()*i_)))*
					//	v_move_point[((i - (v_grid_point[i_].size()*i_)) + ((v_grid_point[i_].size() - 1)* (i - (v_grid_point[i_].size()*i_))))]->geometry().y()*pow(t1, ((v_grid_point[i_].size() - 1) - (i - (v_grid_point[i_].size()*i_))))*
					//	pow(t, (i - (v_grid_point[i_].size()*i_)));
				}
				

			}
			painter.drawPoint(x2, y2);
		}
		++start2;
	}

	/***********************************列*****************************************/



	

	//debug
	/*QPoint p0 = QPoint(330, 140);
	QPoint p1 = QPoint(463, 140);
	QPoint p2 = QPoint(468, 308);
	QPoint p3 = QPoint(614, 314);
	for (double t = 0; t <= 1.0; t += 0.001)
	{
		double t1 = 1 - t;
		int x = v_move_point[0]->x()*pow(t1, 3) + 3 * v_move_point[1]->x()*t*pow(t1, 2) + 3 * v_move_point[2]->x()*pow(t, 2)*t1 + v_move_point[3]->x()*pow(t, 3);
		int y = v_move_point[0]->y()*pow(t1, 3) + 3 * v_move_point[1]->y()*t*pow(t1, 2) + 3 * v_move_point[2]->y()*pow(t, 2)*t1 + v_move_point[3]->y()*pow(t, 3);
		painter.drawPoint(x, y);
	}*/

	//for (i = 0; i < v_grid_point[0].size() - 1; ++i)
	//{
	//	painter.drawLine(v_move_point[i]->geometry().x(), v_move_point[i]->geometry().y(),
	//		v_move_point[i + 1]->geometry().x(), v_move_point[i + 1]->geometry().y()
	//	);
	//}

	/*::system("cls");
	for (int i = 0; i < v_move_point.size(); ++i)
	{
		COUT "( " LK v_move_point[i]->geometry().x() LK " , " LK v_move_point[i]->geometry().y() LK " )" LN;
	}*/

}

int BezierImageDistortion_Final::C(int n, int i)
{
	/*
						N!				α
		如果C(N,I)=	------------  =  -------
					  I!(N-I)!		    μ
	*/
	int molecule = 1;	//α
	int denominator = 1;	// μ

	for (int _n = n ,_i=i; _n > n - i,_i>0; --_n,--_i)
	{
		molecule *= _n;
		denominator *= _i;
	}

	return molecule / denominator;

}
