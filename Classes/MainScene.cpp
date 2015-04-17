//
// MainScene.cpp
// 
// Create By ChenJinJun on 15-4-10
//
//


#include "MainScene.h"
#include "BottonLayer.h"
#include "TopLayer.h"
MainScene::MainScene() :oldTouchPoint(0, 0),
						dir(1),
						farSprite(NULL),
						midSprite(NULL),
						hero(NULL),
						isMapMove(false)
{

}

MainScene::~MainScene()
{

}

cocos2d::Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	
	MainScene* MainLayer = MainScene::create();
	
	BottomLayer* bottomLayer = BottomLayer::create();
	
	TopLayer* topLayer = TopLayer::create();
	
	scene->addChild(topLayer,2);
	scene->addChild(MainLayer);
	scene->addChild(bottomLayer,1);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();


	farSprite = Sprite::create("main_bg_sky.jpg");
	farSprite->setAnchorPoint(Vec2(0, 1));
	farSprite->setPosition(Vec2(0, winSize.height));
	this->addChild(farSprite);


	midSprite = Sprite::create("main_bg_mountain.png");
	midSprite->setAnchorPoint(Vec2(0, 0.5));
	midSprite->setPosition(Vec2(0, winSize.height / 2));
	this->addChild(midSprite);

	auto dipatcher = this->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	dipatcher->addEventListenerWithSceneGraphPriority(listener, this);

	hero = Sprite::create("item/hero.png");
	hero->setPosition(Vec2(30, 200));
	this->addChild(hero);

	leftDis = hero->getContentSize().width;
	FarDis = midSprite->getContentSize().width - hero->getContentSize().width;
	mixDis = midSprite->getContentSize().width / 4;
	maxDis = midSprite->getContentSize().width * 3 / 4;
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("skeleton_and_texture1.ExportJson");
	Armature* he = Armature::create("skeleton_and_texture1");
	he->getAnimation()->play("attack");
	he->getAnimation()->setSpeedScale(0.1);

	he->setScale(0.3f);
//	he->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(HelloWorld::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	he->setTag(10010);
	he->setRotation3D(Vec3(0, 180, 0));
	he->setPosition(Point(100, 300));
	this->addChild(he);




	return true;

}

bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	Size winSize = Director::getInstance()->getVisibleSize();

	Point touchLocation = midSprite->convertTouchToNodeSpace(touch);
	
	Point touchToScreen = touch->getLocation();
	CCLOG("tochLoaction x =====  %f" ,touchLocation.x);
	CCLOG("touch  to  screen   x =====  %f", touchToScreen.x);
	
	float mapPointX = midSprite->getPositionX();

	CCLOG("   map  position  x     %f", mapPointX);
	
	CCLOG("                               ");

	
	//限制点击区域
	if (touchToScreen.y < winSize.height/2 )
	{
		//人物方向
		float disTouch = touchLocation.x - oldTouchPoint.x;
		if (disTouch < 0)
		{
			dir = 1;
		}
		else
		{
			dir = 2;
		}
		oldTouchPoint = touchLocation;
		
		heroMove(touchLocation, touchToScreen);
		
		mapMove(touchLocation, touchToScreen);
	}

	
	return true;
}

void MainScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void MainScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void MainScene::heroMove(Point point , Point touchOnScreen)
{
	CCLOG("  heroMove   Piont x    %f    y      %f", point.x, point.y);
	CCLOG("heroMove     touchOnScreen  X  %f      y    %f", touchOnScreen.x, touchOnScreen.y);
 	hero->stopAllActions();
 
 	Size visibelSize = Director::getInstance()->getVisibleSize();
 	Size herContentSize = hero->getContentSize();
 	Vec2 herPosiotion = hero->getPosition();

 	float move_y = 0;
 	float move_x = 0;

 	if (point.x < herContentSize.width/2)
 	{
		CCLOG("click on the heroContentSize width /2 area");
 		move_x = herContentSize.width / 2;
		move_y = touchOnScreen.y;
 	}
 	else if (point.x < visibelSize.width/2)
 	{
		CCLOG("Click on the left area");
 		move_x = touchOnScreen.x;
		move_y = touchOnScreen.y;
 		
 	}
	if ( point.x > visibelSize.width / 2 && point.x < maxDis)
	{
		CCLOG("click on the middle area");
		move_x = visibelSize.width / 2;
		move_y = touchOnScreen.y;
	}
	if (point.x > visibelSize.width / 2 && point.x > maxDis)
	{
		CCLOG("click on the right area");
		move_x = touchOnScreen.x;
		move_y = touchOnScreen.y;
	}
	if (point.x > midSprite->getContentSize().width - herContentSize.width/2)
	{
		move_x = visibelSize.width - herContentSize.width / 2;
		move_y = touchOnScreen.y;
	}
	CCLOG("hero move   move_x   %f     move_y    %f", move_x, move_y);
	hero->runAction(MoveTo::create(2.0f, Vec2(move_x,move_y)));


}

void MainScene::mapMove(Point touchLocation, Point touchToScreen)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	midSprite->stopAllActions();
	farSprite->stopAllActions();
	float mapPointX = midSprite->getPositionX();

	float dis = winSize.width / 2 - touchToScreen.x;
	float move_x = mapPointX + dis;

	if (touchLocation.x < mixDis && mapPointX < 0 || move_x >= 0)
	{
		CCLOG(" touch in left area but the map is - position ");
		isMapMove = false;
		move_x = 0;
	}
	else if (touchLocation.x > maxDis && mapPointX >-(midSprite->getContentSize().width - winSize.width) || move_x <= -(midSprite->getContentSize().width - winSize.width))
	{
		move_x = -(midSprite->getContentSize().width - winSize.width);
		isMapMove = false;
	}
	else
	{
		isMapMove = true;
	}
	
	midSprite->runAction(MoveTo::create(2.0f, Vec2(move_x, midSprite->getPositionY())));
	farSprite->runAction(MoveTo::create(2.5f, Vec2(move_x, farSprite->getPositionY())));
}


