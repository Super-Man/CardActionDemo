//
//  BaseSprite.h
//  
//	可点，可长按，可拖拽.....
//  Created by ChenJinJun on 15-4-16.
//
//

#ifndef __GameBall__BaseSprite__
#define __GameBall__BaseSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/**
 作为基类，之后如果需要更多的自定义功能，则通过继承这个类去实现
 kSpriteType 设定Sprite类型
 **/
typedef enum
{
    kSpriteTypeForDefault,
    kSpriteTypeForPetHead,
    kSpriteTypeForNew,  
}kSpriteType;


class BaseSpriteDelegate
{
public:
    BaseSpriteDelegate():_selSpritePos(-1),_selSpriteID(-1),_selSpriteType(kSpriteTypeForPetHead){}
public:
    virtual void touchBeginBaseSprite(Ref* sender,Point pos){}
    virtual void touchMoveBaseSprite(Point pos){}
    virtual void touchEndBaseSprite(Point pos){}
    virtual void touchCancelBaseSprite(Point pos){}
    virtual void longTimeTouchBaseSprite(Ref* sender,Point pos){}
public:
    int _selSpritePos;
    int _selSpriteID;
    kSpriteType _selSpriteType;
};


class BaseSprite:public Sprite
{
public:
    BaseSprite();
    virtual ~BaseSprite();
    static BaseSprite* create();
    static BaseSprite* createWith(const char* f);
    static BaseSprite* createWithFrameName(const char* fName);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
	void upDateForLongPress(float dt);
public:

    CC_SYNTHESIZE(BaseSpriteDelegate*, _baseDelegate, BaseDelegate);
    
    //长按操作
	//长按时间
    CC_SYNTHESIZE_READONLY(float, _pressTime, PressTime);
    //是否长按
	CC_SYNTHESIZE_READONLY(bool, _isLongPress,IsLongPress);
    //检测是否长按
	CC_SYNTHESIZE(bool, _isCheckLongPress, IsCheckLongPress);
    
    //是否被点击
    CC_SYNTHESIZE(bool, _isSelected, IsSelected);
    
    //修改触摸优先级
    CC_SYNTHESIZE(int, _customPriority, CustomPriority);
    
    //多点触控的监测
    CC_SYNTHESIZE(bool, _isCheckTouchCount, IsCheckTouchCount);
    
    
    CC_SYNTHESIZE(int, _spriteID, SpriteID);
    CC_SYNTHESIZE(int, _spritePos, SpritePos);
    CC_SYNTHESIZE(kSpriteType, _spriteType, SpriteType);

	//能否选择
    CC_SYNTHESIZE(bool, _canSelect, CanSelect);
	//是否已经被选择
    CC_SYNTHESIZE(bool, _beSelected, BeSelected);
	//是否需要吞噬触摸
    CC_SYNTHESIZE(bool, _needSwallow, NeedSwallow);

    CC_SYNTHESIZE(bool, _touchEndCheck, TouchEndCheck);
	
	//单击响应操作
    CC_SYNTHESIZE(bool, _clickEvent, ClickEvent);
	//长按响应操作
    CC_SYNTHESIZE(bool, _pressEvent, PressEvent);
   
	CC_SYNTHESIZE(bool, _beLocked, Locked);

private:
	int selecCount;
    EventListenerTouchOneByOne* _listener;
    bool _longPress;
};
#endif /* defined(__GameBall__BaseSprite__) */
