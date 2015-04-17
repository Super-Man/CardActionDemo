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
	������
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

	int dir; // 1 ���� 2 ����;  todo


	Sprite* farSprite;

	Sprite* midSprite;

	Sprite* hero;


	//�����
	float leftDis;

	//���ұ�
	float FarDis;

	//��߽�  
	float mixDis;
	//�ұ߽�
	float maxDis;

	Point oldTouchPoint;

	bool isMapMove;
private:
	/****************************
		�����ƶ�
		����˵���� 
		point  �����������ڵ�ͼ
		touchOnScreen  ��������������Ļ
	*****************************/	
	void heroMove(Point point, Point touchOnScreen);


	/*****************************
		��ͼ�ƶ�
		����˵����
		point  �����������ڵ�ͼ
		touchOnScreen  ��������������Ļ
	**********************************/

	void mapMove(Point point,Point touchToScreen);



};



#endif//__MAIN_LAYER_HEADER__