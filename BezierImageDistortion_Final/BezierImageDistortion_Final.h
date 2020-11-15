#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BezierImageDistortion_Final.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>

#include <cstring>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QEvent>
#include <QPoint>
#include <vector>
#include <stdlib.h>
#include <QPaintEvent>

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>

#include "Good.h"
#include "MMovePoint.h"

using namespace cv;
using namespace std;
using namespace boost;
using namespace boost::assign;

class BezierImageDistortion_Final : public QMainWindow
{
	Q_OBJECT

public:
	BezierImageDistortion_Final(QWidget *parent = Q_NULLPTR);

private:
	Ui::BezierImageDistortion_FinalClass ui;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);

public:
	void initMembers();
	void connectAll();
	void addToLabel(Mat &input,QLabel *output);
	void loadDefaultImg();
	void loadDefaultVideo();
	void drawPoints();
	void paint();

	/*
		代表排列组合
		 __
		/   i
	   |	  
		\__ n
	*/
	int C(int n,int i);

private:
	//image
	Mat mat_image,
		mat_frame;
	QImage qimg;
	string path_img;
	POINTER_INIT(boost::thread, t_show);//图像
	POINTER_INIT(boost::thread, t_show_v);//视频
	POINTER_INIT(boost::thread, t_draw);//绘制

	//vedio
	VideoCapture cap;
	
	POINTER_INIT(QWidget, selected_widget);


	/*
		一行有几个点c_grid个点
		若选择格数为1X1
		则c_grid=2，一行有2个点
		总共c_grid * c_grid个
	*/
	int c_grid=2;

	/*
		每一行相邻两点的步长

		若一行2点，步长为 (1X1)
			step=widget/(c_grid-1) = widget

		若一行3点，步长为 (2X2)
		step=widget/(c_grid-1) =
	*/
	int step_r = 0;
	int step_c = 0;//每一列相邻两点的步长
	
	/*
		保存每一行的网格点
		v_grid_point[i][0]为第i行的第一个点
	*/
	vector< vector<Point> > v_grid_point;

	vector<MMovePoint*> v_move_point;//保存控制点
	POINTER_INIT(MMovePoint,mp);

	QLabel *lab;//在image_show上 再加一层label 用来绘制网格

	/*
		保存每一行的bezier点的坐标
		v_bezier_rows[i][0]为第i行的第一个B(t)点
	*/
	vector< vector<Point> > v_bezier_rows;
};
