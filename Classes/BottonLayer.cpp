//
// BottomLayer.h	
// 
// create by ChenJinJun on 15-4-12
//

#include "CustomLayerColor.h"
#include "BottonLayer.h"

BottomLayer::BottomLayer()
{
}

BottomLayer::~BottomLayer()
{
}

bool BottomLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	SwallowTouch * m_pSwallowTouch = SwallowTouch::create();
	this->addChild(m_pSwallowTouch,1);

	CustomLayerColor* maskLayer = CustomLayerColor::create(ccc4(226, 3, 37, 225));
	maskLayer->setContentSize(Size(visibleSize.width,100));
	maskLayer->setAnchorPoint(Point(0, 0));
	maskLayer->setPosition(Point::ZERO);
	this->addChild(maskLayer);

	return true;
}

