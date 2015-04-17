//
// MainScene.h
//
// Create By ChenJinJun on 15-4-10
//
//


#ifndef  __MAIN_SCENE_HEADER__
#define	 __MAIN_SCENE_HEADER__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace cocostudio;


/************************
	主界面
************************/

class MainScene : public Layer
{
public:
	MainScene();
	~MainScene();

	static cocos2d::Scene* createScene();

	virtual bool init();


	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(MainScene);
private:

	int dir; // 1 向左， 2 向右;  todo


	Sprite* farSprite;

	Sprite* midSprite;

	Sprite* hero;


	//最左边
	float leftDis;

	//最右边
	float FarDis;

	//左边界  
	float mixDis;
	//右边界
	float maxDis;

	Point oldTouchPoint;

	bool isMapMove;
private:
	/****************************
		人物移动
		参数说明： 
		point  点击坐标相对于地图
		touchOnScreen  点击坐标相对于屏幕
	*****************************/	
	void heroMove(Point point, Point touchOnScreen);


	/*****************************
		地图移动
		参数说明：
		point  点击坐标相对于地图
		touchOnScreen  点击坐标相对于屏幕
	**********************************/

	void mapMove(Point point,Point touchToScreen);



};



#endif//__MAIN_LAYER_HEADER__