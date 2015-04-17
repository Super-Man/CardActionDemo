//
//  GameDialog.cpp
//  弹框类
//  Created by ChenJinJun on 15-4-15.
//
//


#include "GameDialog.h"
#include "CustomLayerColor.h"
#include "CustomSprite.h"

GameDialog* GameDialog::m_dialogInstance = nullptr;


GameDialog::GameDialog()
{
	_dialog = NULL;

}

GameDialog::~GameDialog()
{
	CC_SAFE_RELEASE_NULL(_dialog);
	//CC_SAFE_DELETE_ARRAY(m_dialogInstance);
}

GameDialog* GameDialog::getInstance()
{
	if (m_dialogInstance == nullptr)
	{
		m_dialogInstance = new (std::nothrow) GameDialog();
		m_dialogInstance->init();

	}

	return m_dialogInstance;
}

bool GameDialog::init()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	_dialog = Node::create();
	_dialog->setContentSize(winSize);

	CCASSERT(_dialog != nullptr, "");
	_dialog->retain();
	_dialog->setPosition(Point(winSize.width / 2, 0));


	return true;
}



void GameDialog::HeroDialogShow(Node* parent, int zOrder, const std::function<void(Ref*)>& receiveCallBack, const std::function<void(Ref*)>& advanceCallBack, Point position /*= Point::ZERO*/)
{
	auto winSize = Director::getInstance()->getVisibleSize();
	
	if (_dialog->getChildrenCount())
	{
		_dialog->removeAllChildrenWithCleanup(true);
	}
	
	if (_dialog && _dialog->getParent() != nullptr)
	{
		_dialog->removeFromParentAndCleanup(true);
	}
	if (nullptr != parent && zOrder != 0)
	{
		CCASSERT(_dialog != nullptr, "");
		parent->addChild(_dialog,zOrder + 1);
		_dialog->setPosition(0, 0);
	}
	CustomLayerColor* maskLayer = CustomLayerColor::create(ccc4(0, 0, 0, 50));
	maskLayer->setAnchorPoint(Point::ZERO);
	maskLayer->setPosition(Point::ZERO);
	_dialog->addChild(maskLayer);

	//人物弹框背景
	Sprite* HeroDialog_bg = Sprite::create("Dialog/hero_dialog/hero_dialogBg.png");
	HeroDialog_bg->setPosition(Point(winSize.width/2, winSize.height / 2));
	_dialog->addChild(HeroDialog_bg,1);

	Size heroDialogSize = HeroDialog_bg->getContentSize();

	//人物精灵
	//根据玩家数据来
	auto heroSprite = Sprite::create("Dialog/hero_dialog/hero.png");
	heroSprite->setPosition(heroDialogSize.width / 2, heroDialogSize.height / 2);
	HeroDialog_bg->addChild(heroSprite);


	//名字label
	auto nameLabel = Label::create();
	nameLabel->setString("shabi");//应该获取玩家名字
	nameLabel->setContentSize(Size(120, 30));
	nameLabel->setAnchorPoint(Point(0, 1));
	nameLabel->setPosition(Vec2(50, heroDialogSize.height - 65));
	HeroDialog_bg->addChild(nameLabel);

	//公会Label
	auto associationLabel = Label::create();
	associationLabel->setAnchorPoint(Point(0, 1));
	associationLabel->setContentSize(Size(140,30));
	associationLabel->setPosition(Vec2(170, heroDialogSize.height - 65));
	// 如果玩家有公会  则 setstring（）玩家数据里面的公会名字 ，没有则setstring（暂无加入公会）
	associationLabel->setColor(ccc3(197, 28, 165));
	associationLabel->setString("逗比 ");
	HeroDialog_bg->addChild(associationLabel);


	//等级
	auto levelBg = Sprite::create("Dialog/hero_dialog/hero_dialoglevel.png");
	levelBg->setAnchorPoint(Vec2(0, 1));
	levelBg->setPosition(Vec2(30, heroDialogSize.height - 85));
	HeroDialog_bg->addChild(levelBg);

	auto levelLabel = Label::create();
	levelLabel->setPosition(levelBg->getContentSize().width / 2-5, levelBg->getContentSize().height / 2);
	levelLabel->setString("100");
	levelLabel->setSystemFontSize(25);
	levelBg->addChild(levelLabel);

	//经验条
	//根据当前经验 与 下一等级经验的 比值，来调整条的横向缩放
	auto valueBarBg = Sprite::create("Dialog/hero_dialog/hero_dialoglevelBg.png");
	valueBarBg->setAnchorPoint(Point(0, 1));
	valueBarBg->setPosition(20 + levelBg->getContentSize().width, heroDialogSize.height - 85);
	HeroDialog_bg->addChild(valueBarBg);

	auto valueBar = Sprite::create("Dialog/hero_dialog/hero_dialoglevelBar.png");
	valueBar->setAnchorPoint(Point(0, 0.5));
	valueBar->setPosition(13, valueBarBg->getContentSize().height / 2);
	valueBarBg->addChild(valueBar);
	valueBar->setScaleX(0.5);

	//战斗力值
	//根据玩家数据来setring，
	auto battelValue = Label::create();
	battelValue->setString("9999999");
	battelValue->setSystemFontSize(35);
	battelValue->setPosition(140, 165);
	HeroDialog_bg->addChild(battelValue);


	//玩家 副主将





	//右侧背景框
	auto rightFrameBg = Sprite::create("Dialog/hero_dialog/hero_dialogRightBg.png");
	rightFrameBg->setAnchorPoint(Point(1, 0.5));
	rightFrameBg->setPosition(heroDialogSize.width - 10, heroDialogSize.height / 2-3);
	HeroDialog_bg->addChild(rightFrameBg);


	// 提升按钮
	auto advanceBtn = Button::create("Dialog/hero_dialog/hero_dialogAdvance_normal.png", "Dialog/hero_dialog/hero_dialogAdvance_seclet.png");
	


	//领取按钮
	auto receiveBut = Button::create("Dialog/hero_dialog/hero_dialogReceive_normal.png", "Dialog/hero_dialog/hero_dialogReceive_seclet.png");
	receiveBut->setAnchorPoint(Point(0.5, 0));
	receiveBut->setPosition(Point(rightFrameBg->getContentSize().width/2, 10));
	receiveBut->addClickEventListener(receiveCallBack);
	rightFrameBg->addChild(receiveBut);


	//关闭按钮
	auto closeBtn = Button::create("Dialog/hero_dialog/hero_dialogClose_nomal.png", "Dialog/hero_dialog/hero_dialogClose_seclet.png");
	closeBtn->setAnchorPoint(Point(1, 1));
	closeBtn->setPosition(Vec2(heroDialogSize.width, heroDialogSize.height));
	closeBtn->addClickEventListener(CC_CALLBACK_1(GameDialog::closeBtnCallBack, this));
	HeroDialog_bg->addChild(closeBtn);

}



void GameDialog::StoneStrengShow(int stoneId, int zOrder, Node* parent, Point position)
{
	if (_dialog->getChildrenCount())
	{
		_dialog->removeAllChildrenWithCleanup(true);
	}
	
	if (_dialog && _dialog->getParent() != nullptr)
	{
		_dialog->removeFromParentAndCleanup(true);
	}
	if (nullptr != parent && zOrder != 0)
	{
		CCASSERT(_dialog != nullptr, "");
		parent->addChild(_dialog, zOrder);
		_dialog->setPosition(0, 0);
	}
	
	//现根据传过来的 stoneId 去读取玩家数据中 该stoneId 的信息，然后根据id 去读取stone的静态数据

	


	//半透明遮罩层
	CustomLayerColor* maskLayer = CustomLayerColor::create(ccc4(0, 0, 0, 80));
	maskLayer->setAnchorPoint(Point::ZERO);
	maskLayer->setPosition(Point::ZERO);
	_dialog->addChild(maskLayer);


	//角石强化背景框
	auto stoneStrengBg = CustomSprite::create("Dialog/stone_dialog/dialog_stoneStrength.png");
	if (position.x != 0 || position.y != 0)
	{
		stoneStrengBg->setPosition(position);
	}
	else
	{
		stoneStrengBg->setAnchorPoint(Point::ZERO);
		stoneStrengBg->setPosition(100, 200);
	}
	_dialog->addChild(stoneStrengBg);


	
	//材料一
	//auto mater1 = Sprite::create("");



	//材料二
//	auto mater2 = Sprite::create("");

	


	//该stoneID角石
	auto stoneSprite = Sprite::create("item/item_i_chashaobao.png");
	stoneSprite->setPosition(200, 250);
	stoneStrengBg->addChild(stoneSprite);


	//当前等级的物理攻击力
	//// 获取道具类中该角石 该等级的信息
	auto nowAttackLabel = Label::create();
	nowAttackLabel->setAnchorPoint(Point(0, 0.5));
	nowAttackLabel->setPosition(160, 110);
	nowAttackLabel->setString("+10");
	nowAttackLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nowAttackLabel);

	//当前等级的敏捷速度
	auto nowSpeedLabel = Label::create();
	nowSpeedLabel->setAnchorPoint(Point(0, 0.5));
	nowSpeedLabel->setPosition(160, 85);
	nowSpeedLabel->setString("+20");
	nowSpeedLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nowSpeedLabel);

	//下一等级的物理攻击力
	auto nextAttackLabel = Label::create();
	nextAttackLabel->setAnchorPoint(Point(0, 0.5));
	nextAttackLabel->setPosition(360, 110);
	nextAttackLabel->setString("+20");
	nextAttackLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nextAttackLabel);

	//下一等级的敏捷速度
	auto nextSpeedLabel = Label::create();
	nextSpeedLabel->setAnchorPoint(Point(0, 0.5));
	nextSpeedLabel->setPosition(360, 85);
	nextSpeedLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nextSpeedLabel);

	//强化按钮
	auto strengthBtn = Button::create("common_button/streng_normal.png", "common_button/strength_selceted.png");
	strengthBtn->setAnchorPoint(Point(0.5, 0));
	strengthBtn->setPosition(Point(stoneStrengBg->getContentSize().width / 2, 20));
	strengthBtn->addClickEventListener([stoneSprite](Ref*){
										stoneSprite->setPosition(100, 100);

										});
	stoneStrengBg->addChild(strengthBtn);

	if (!stoneStrengBg->getIsSelected())
	{
		CCLOG("jingling meiyou  xuan zhong");
	}
	
}


void GameDialog::closeBtnCallBack(Ref* pSend)
{
	//Button* m_pButton = (Button*)pSend;
	CCLOG("============hero dialog close button========");
	if (_dialog->getParent())
	{
		_dialog->removeFromParentAndCleanup(true);
	}


}