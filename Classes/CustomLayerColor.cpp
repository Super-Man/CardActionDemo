//
//  CustomLayerColor.cpp
//  
//
//  Created by Chen on 15-4-15.
//
//

#include "CustomLayerColor.h"

CustomLayerColor::CustomLayerColor():
m_nDefaultPriority(0)
{
    
}

CustomLayerColor::~CustomLayerColor()
{
    
}

CustomLayerColor* CustomLayerColor::create()
{
    CustomLayerColor* _layerColor = new CustomLayerColor();
    if (_layerColor && _layerColor->init())
    {
        _layerColor->autorelease();
        return _layerColor;
    }
    CC_SAFE_DELETE(_layerColor);
    return nullptr;
}

CustomLayerColor* CustomLayerColor::create(const Color4B& color)
{
    CustomLayerColor* _layerColor = new CustomLayerColor();
    if (_layerColor && _layerColor->initWithColor(color))
    {
        _layerColor->autorelease();
        return _layerColor;
    }
    CC_SAFE_DELETE(_layerColor);
    return nullptr;
}

void CustomLayerColor::onEnter()
{
    LayerColor::onEnter();
    _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(true);
    
    _listener->onTouchBegan = [this](Touch* pTouch,Event* pEvent)
    {
        auto point = convertToNodeSpace(pTouch->getLocation());
        auto size = getContentSize();
        if (Rect(0,0,size.width,size.height).containsPoint(point) && this->isVisible())
        {
            return true;
        }
        return false;
    };
	//没有设置优先级的话，根据z轴来判断吞噬
    if (m_nDefaultPriority != 0)
    {
        _eventDispatcher->addEventListenerWithFixedPriority(_listener, m_nDefaultPriority);
    }
    else
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    }
}

void CustomLayerColor::onExit()
{
    _eventDispatcher->removeEventListener(_listener);
    LayerColor::onExit();
}
