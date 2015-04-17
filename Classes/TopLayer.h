//
//  TopLayer.h
//
//  顶部层： 包含 玩家头像，信息， 钻石，金币，体力等
//
//  Create By ChenJinJun on 15-4-12
//


#ifndef __TOP_LAYER_HEADER__
#define __TOP_LAYER_HEADER__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;
using namespace ui;


enum InterfaceBtn
{
	HEAD,				//头像枚举;
	VIP,				//会员VIP;
	STAMINA,			//体力;
	DIAMONDS,			//钻石;
	GOLDA				//金币;

};


class TopLayer : public Layer
{
public:
	TopLayer();
	
	~TopLayer();

	virtual bool init();

	//Head
	CC_SYNTHESIZE(ui::Button*, m_pHeadBtn, HeadBtn);

	//Vip;
	CC_SYNTHESIZE(ui::Button*, m_pVipBtn, VipBtn);

	//Stamina
	CC_SYNTHESIZE(ui::Button*, m_pStaminaBtn, StaminaBtn);

	//Diamonds
	CC_SYNTHESIZE(ui::Button*, m_pDiamondsBtn, DiamondsBtn);

	//Golda
	CC_SYNTHESIZE(ui::Button*, m_pGoldaBtn, GoldaBtn);

	//界面功能按钮;
	void InterfaceCellBack(Ref* obj);

	CREATE_FUNC(TopLayer);

private:







};





#endif