#pragma once

#include <iostream>
using namespace std;

#define COUT cout<<
#define COUT_LN cout<<endl
#define CIN cin>>
#define LK <<
#define LN <<endl

#define TO_STRING(X) #X
#define TO_SINGLE_CHAR(C) #@C

#define DELETE_OBJ(T) \
	if (T)\
	{\
		delete T;\
		T=nullptr;\
	}

#define NEW_OBJ(TYPE,OBJ) \
	TYPE *OBJ=new TYPE

#define POINTER_INIT(TYPE,OBJ)\
	TYPE *OBJ=nullptr
	
#define POINTER_INS(OBJ,TYPE)\
	OBJ=new TYPE

#define SET_NULL(OBJ)\
	OBJ=nullptr\

#define DEFAULT_IMAGE "D:\\__Codes\\__Visual_Studio\\BezierImageDistortion_Final\\BezierImageDistortion_Final\\Resources\\images\\test3.jpg"

#define FRAME_WIDGET 960
#define FRAME_HEIGHT 720

#define CTL_POINT_ZISE 10
#define CENTER_POINT_STEP (CTL_POINT_ZISE/2)