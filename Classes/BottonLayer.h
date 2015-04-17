//
// BottomLayer.h	
//  底部层类： 包含 伸缩菜单，聊天功能
// create by ChenJinJun on 15-4-12
//


#ifndef __BOTTOM_LAYER_HEADER__
#define __BOTTOM_LAYER_HEADER__

#include "cocos2d.h"
#include "SwallowTouch.h"

USING_NS_CC;

/***************************************
  底部层，包含 伸缩菜单，聊天
****************************************/

class BottomLayer :public Layer
{
public:
	BottomLayer();
	~BottomLayer();

	virtual bool init();

	CREATE_FUNC(BottomLayer);

private:


};



#endif