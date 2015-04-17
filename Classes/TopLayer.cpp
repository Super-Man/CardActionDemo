//
// TopLayer.cpp
// 
// Create By ChenJinJun on 15-4-12
//

#include "TopLayer.h"
#include "CustomLayerColor.h"
#include "GameDialog.h"


TopLayer::TopLayer() :
m_pHeadBtn(nullptr),
m_pVipBtn(nullptr),
m_pStaminaBtn(nullptr),
m_pDiamondsBtn(nullptr),
m_pGoldaBtn(nullptr)
{
}

TopLayer::~TopLayer()
{
}

bool TopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	//头像底部背景;
	auto head_background = Sprite::create("Head/head_background.png");
	head_background->setAnchorPoint(Vec2(0, 1));
	head_background->setPosition(Vec2((visibleSize.width/2)*0.1f, (visibleSize.height/2)*(1.98f)));
	head_background->setScale(0.7f, 0.7f);
	this->addChild(head_background);

	//Head Button;
	m_pHeadBtn = Button::create("Head/head.png", "");
	m_pHeadBtn->addClickEventListener(CC_CALLBACK_1(TopLayer::InterfaceCellBack, this));
	getHeadBtn()->setAnchorPoint(ccp(0, 1));
	getHeadBtn()->setPosition(ccp((visibleSize.width/2)*0.1f, (visibleSize.height/2)*1.98f));
	getHeadBtn()->setTag(HEAD);
	getHeadBtn()->setScale(0.7f, 0.7f);
	this->addChild(getHeadBtn());

	//Name;
	auto name_background = Sprite::create("Head/name_background.png");
	name_background->setAnchorPoint(Vec2(0, 1));
	name_background->setPosition(Vec2((visibleSize.width / 2)*0.3f, (visibleSize.height / 2)*(1.98f)));
	name_background->setScale(0.75f, 0.75f);
	this->addChild(name_background);

	//Vip Button;
	m_pVipBtn = Button::create("Head/vip.png", "");
	m_pVipBtn->addClickEventListener(CC_CALLBACK_1(TopLayer::InterfaceCellBack, this));
	getVipBtn()->setAnchorPoint(ccp(0, 1));
	getVipBtn()->setPosition(ccp((visibleSize.width/2)*(0.01f), (visibleSize.height/2)*(1.98f)));
	getVipBtn()->setTag(VIP);
	getVipBtn()->setScale(0.5f, 0.5f);
	this->addChild(getVipBtn());

	//Level;
	auto level_background = Sprite::create("Head/hero_level.png");
	level_background->setAnchorPoint(Vec2(0, 1));
	level_background->setPosition(Vec2((visibleSize.width / 2)*(0.01f), (visibleSize.height / 2)*(1.80f)));
	level_background->setScale(0.6f, 0.6f);
	this->addChild(level_background);


	//体力;
	auto stamina_background = Sprite::create("Head/heronameframe.png");
	stamina_background->setAnchorPoint(Vec2(0, 1));
	stamina_background->setPosition(Vec2((visibleSize.width / 2)*(0.739f), (visibleSize.height / 2)*(1.98f)));
	this->addChild(stamina_background);

	//Stamina Button
	m_pStaminaBtn = Button::create("Head/stamina_menu.png", "");
	m_pStaminaBtn->addClickEventListener(CC_CALLBACK_1(TopLayer::InterfaceCellBack, this));
	getStaminaBtn()->setAnchorPoint(ccp(0, 1));
	getStaminaBtn()->setPosition(ccp(110, 45));
	getStaminaBtn()->setTag(STAMINA);
	getStaminaBtn()->setScale(0.3f, 0.3f);
	stamina_background->addChild(getStaminaBtn());


	//钻石;
	auto diamonds_background = Sprite::create("Head/heronameframe.png");
	diamonds_background->setAnchorPoint(Vec2(0, 1));
	diamonds_background->setPosition(Vec2((visibleSize.width / 2)*(1.139f), (visibleSize.height / 2)*(1.98f)));
	this->addChild(diamonds_background);

	//Diamonds Button
	m_pDiamondsBtn = Button::create("Head/diamonds_background.png", "");
	m_pDiamondsBtn->addClickEventListener(CC_CALLBACK_1(TopLayer::InterfaceCellBack, this));
	getDiamondsBtn()->setAnchorPoint(ccp(0, 1));
	getDiamondsBtn()->setPosition(ccp(110, 42));
	getDiamondsBtn()->setTag(DIAMONDS);
	getDiamondsBtn()->setScale(0.4f, 0.4f);
	diamonds_background->addChild(getDiamondsBtn());

	//金币;
	auto goled_background = Sprite::create("Head/heronameframe.png");
	goled_background->setAnchorPoint(Vec2(0, 1));
	goled_background->setPosition(Vec2((visibleSize.width / 2)*(1.539f), (visibleSize.height / 2)*(1.98f)));
	this->addChild(goled_background);
	
	//Golda Button
	m_pGoldaBtn = Button::create("Head/gold_back.png", "");
	m_pGoldaBtn->addClickEventListener(CC_CALLBACK_1(TopLayer::InterfaceCellBack, this));
	getGoldaBtn()->setAnchorPoint(ccp(0, 1));
	getGoldaBtn()->setPosition(ccp(110, 50));
	getGoldaBtn()->setTag(GOLDA);
	getGoldaBtn()->setScale(0.8f, 0.8f);
	goled_background->addChild(getGoldaBtn());

	return true;
}

void TopLayer::InterfaceCellBack(Ref* obj)
{
	log("Interface Cell Back");
	Size winSize = Director::getInstance()->getVisibleSize();

	Button *pBtn  = (Button *)obj;
	switch (pBtn->getTag())
	{
		case HEAD:
		{
					
					 if (this->getParent() != nullptr)
					 {
						 // 头像弹框
						 GameDialog* m_pDialog = GameDialog::getInstance();
						 m_pDialog->HeroDialogShow(this->getParent(), 3, [](Ref* sender){ log("xxx"); }, [](Ref* sender){ log("111111"); });
					 }
						

			  break;
		}
		case VIP:
		{
					log("VIP");
					break;
		}

		case STAMINA:
		{
						if (this->getParent() != nullptr)
						{
							//test 角石弹框
							GameDialog* m_pDialog = GameDialog::getInstance();
							m_pDialog->StoneStrengShow(10001, 3, this->getParent(), Point(winSize.width / 2, winSize.height / 2));

						}
						   log("STAMINA");
						   break;
		}

		case  DIAMONDS:
		{
					   log("DIAMONDS");
					   break;
		}
		case GOLDA:
		{
							 log("GOLDA");
							 break;
		}

		default:
			break;
	}
}


