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
		�����������
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
	POINTER_INIT(boost::thread, t_show);//ͼ��
	POINTER_INIT(boost::thread, t_show_v);//��Ƶ
	POINTER_INIT(boost::thread, t_draw);//����

	//vedio
	VideoCapture cap;
	
	POINTER_INIT(QWidget, selected_widget);


	/*
		һ���м�����c_grid����
		��ѡ�����Ϊ1X1
		��c_grid=2��һ����2����
		�ܹ�c_grid * c_grid��
	*/
	int c_grid=2;

	/*
		ÿһ����������Ĳ���

		��һ��2�㣬����Ϊ (1X1)
			step=widget/(c_grid-1) = widget

		��һ��3�㣬����Ϊ (2X2)
		step=widget/(c_grid-1) =
	*/
	int step_r = 0;
	int step_c = 0;//ÿһ����������Ĳ���
	
	/*
		����ÿһ�е������
		v_grid_point[i][0]Ϊ��i�еĵ�һ����
	*/
	vector< vector<Point> > v_grid_point;

	vector<MMovePoint*> v_move_point;//������Ƶ�
	POINTER_INIT(MMovePoint,mp);

	QLabel *lab;//��image_show�� �ټ�һ��label ������������

	/*
		����ÿһ�е�bezier�������
		v_bezier_rows[i][0]Ϊ��i�еĵ�һ��B(t)��
	*/
	vector< vector<Point> > v_bezier_rows;
};
