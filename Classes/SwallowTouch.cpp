//
// SwallowTouch.h 
//
// 伸缩菜单类
//
// Create By PenKeJie on 15-4-10
//


#include "swallowTouch.h"


SwallowTouch::SwallowTouch() :_isScale(true),
 m_pHeroBtn(nullptr),
 m_pFooter_soulBtn(nullptr),
 m_pSettingsBtn(nullptr),
 m_pStrongthenBtn(nullptr),
 m_pTeamBtn(nullptr)
{
}


SwallowTouch::~SwallowTouch()
{
}

bool SwallowTouch::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pSwallBg = Sprite::create("SwallowTouch/Swallow_bg.png");
	m_pSwallBg->setAnchorPoint(Vec2(1, 0.5));
	m_pSwallBg->setPosition(Vec2(size.width -90 ,50));
	this->addChild(m_pSwallBg);

	auto arrowLeft = MenuItemImage::create("SwallowTouch/arrow_right.png", "SwallowTouch/arrow_left.png");
	auto arrowRight = MenuItemImage::create("SwallowTouch/arrow_left.png", "SwallowTouch/arrow_right.png");
	MenuItemToggle* tog = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SwallowTouch::MoveMenu, this), arrowLeft, arrowRight, nullptr);
	
	auto menu = Menu::create(tog, NULL);
	menu->setAnchorPoint(Vec2(1, 0));
	menu->setPosition(size.width-50,50);
	this->addChild(menu, 1);

	//Hore Button;
	m_pHeroBtn = Button::create("SwallowTouch/footer_menu_hero.png", "SwallowTouch/slowleaf.png");
	m_pHeroBtn->addClickEventListener(CC_CALLBACK_1(SwallowTouch::MenuAllButton, this));
	getHeroBtn()->setAnchorPoint(ccp(0, 0));
	getHeroBtn()->setPosition(ccp(0, 0));
	getHeroBtn()->setTag(HOERBUTTON);
	getHeroBtn()->setScale(0.35f);
	m_pSwallBg->addChild(getHeroBtn());
	

	//footer_soul Button;
	m_pFooter_soulBtn = Button::create("SwallowTouch/footer_menu_soul.png", "SwallowTouch/slowleaf.png");
	m_pFooter_soulBtn->addClickEventListener(CC_CALLBACK_1(SwallowTouch::MenuAllButton, this));
	getFooter_soulBtn()->setAnchorPoint(ccp(0, 0));
	getFooter_soulBtn()->setPosition(ccp(35, 0));
	getFooter_soulBtn()->setTag(SOUL);
	getFooter_soulBtn()->setScale(0.35f);
	m_pSwallBg->addChild(getFooter_soulBtn());
	

	//strongthen Button;
	m_pStrongthenBtn = Button::create("SwallowTouch/footer_menu_strongthen.png", "SwallowTouch/slowleaf.png");
	m_pStrongthenBtn->addClickEventListener(CC_CALLBACK_1(SwallowTouch::MenuAllButton, this));
	getStrongthenBtn()->setAnchorPoint(ccp(0, 0));
	getStrongthenBtn()->setPosition(ccp(70, 0));
	getStrongthenBtn()->setTag(STRONGTHEN);
	getStrongthenBtn()->setScale(0.35f);
	m_pSwallBg->addChild(getStrongthenBtn());
	

	//team Button;
	m_pTeamBtn = Button::create("SwallowTouch/footer_menu_team.png", "SwallowTouch/slowleaf.png");
	m_pTeamBtn->addClickEventListener(CC_CALLBACK_1(SwallowTouch::MenuAllButton, this));
	getTeamBtn()->setAnchorPoint(ccp(0, 0));
	getTeamBtn()->setPosition(ccp(105, 0));
	getTeamBtn()->setTag(TEAMC);
	getTeamBtn()->setScale(0.35f);
	m_pSwallBg->addChild(getTeamBtn());
	
	
	//settings_icon Button;
	m_pSettingsBtn = Button::create("SwallowTouch/settings_icon.png", "SwallowTouch/slowleaf.png");
	m_pSettingsBtn->addClickEventListener(CC_CALLBACK_1(SwallowTouch::MenuAllButton, this));
	getSettingsBtn()->setAnchorPoint(ccp(0, 0));
	getSettingsBtn()->setPosition(ccp(142, 0));
	getSettingsBtn()->setTag(SETTINGSICON);
	getSettingsBtn()->setScale(0.6f);
	m_pSwallBg->addChild(getSettingsBtn());
	m_pSwallBg->setScale(2.0f);

	return true;
}


void SwallowTouch::MoveMenu(Ref *obj)
{
	m_pSwallBg->stopAllActions();
	MenuItemToggle * toggleMenu = (MenuItemToggle *)obj;

	 int  index = toggleMenu->getSelectedIndex();
	Size size = Director::getInstance()->getVisibleSize();
	
	float swallPositionX = m_pSwallBg->getPositionX();

	if (index == 1)
	{
		// 移出
		MoveTo*	moveAction = MoveTo::create(1.5f, Vec2(swallPositionX, -50));
		FadeOut* outAction = FadeOut::create(0.2f);

		m_pSwallBg->runAction(Spawn::create(moveAction, outAction, NULL));


	}
	if (index ==0)
	{
		//移入
		MoveTo*	moveAction = MoveTo::create(1.5f, Vec2(swallPositionX, 50));
		FadeIn* inAction = FadeIn::create(0.3f);
		m_pSwallBg->runAction(Spawn::create(moveAction, inAction, NULL));
	}
	
}

void SwallowTouch::MenuAllButton(Ref* obj)
{
	Button * m_pButton = (Button*)obj;	
	switch (m_pButton->getTag())
	{
		case HOERBUTTON:
		{
			 log("HOERBUTTON");
			 break;
		}
		case SOUL:
		{
			log("SOUL");
			break;
		}

		case STRONGTHEN:
		{
			log("STRONGTHEN");
			break;
		}

		case  TEAMC:
		{
			log("TEAMC");
			break;
		}
		case SETTINGSICON:
		{
			log("SETTINGSICON");
			break;
		}

		default:
			break;
	}
}