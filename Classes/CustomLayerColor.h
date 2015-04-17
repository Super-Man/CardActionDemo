//
//  CustomLayerColor.h
//  屏蔽层
//
//  Created by ChenJinJun on 15-4-15.
//
//

#ifndef __CustomLayerColor__
#define __CustomLayerColor__


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class CustomLayerColor:public LayerColor
{
public:
    CustomLayerColor();
    ~CustomLayerColor();
    
    static CustomLayerColor* create();
    static CustomLayerColor* create(const Color4B& color);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
public:
	
	//设置该MaskLayer 的点击优先级
    CC_SYNTHESIZE(int, m_nDefaultPriority, DefaultPriority);
    
	EventListenerTouchOneByOne *_listener;

private:
	
};

#endif /* defined(__CustomLayerColor__) */
