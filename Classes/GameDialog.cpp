//
//  GameDialog.cpp
//  ������
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

	//���ﵯ�򱳾�
	Sprite* HeroDialog_bg = Sprite::create("Dialog/hero_dialog/hero_dialogBg.png");
	HeroDialog_bg->setPosition(Point(winSize.width/2, winSize.height / 2));
	_dialog->addChild(HeroDialog_bg,1);

	Size heroDialogSize = HeroDialog_bg->getContentSize();

	//���ﾫ��
	//�������������
	auto heroSprite = Sprite::create("Dialog/hero_dialog/hero.png");
	heroSprite->setPosition(heroDialogSize.width / 2, heroDialogSize.height / 2);
	HeroDialog_bg->addChild(heroSprite);


	//����label
	auto nameLabel = Label::create();
	nameLabel->setString("shabi");//Ӧ�û�ȡ�������
	nameLabel->setContentSize(Size(120, 30));
	nameLabel->setAnchorPoint(Point(0, 1));
	nameLabel->setPosition(Vec2(50, heroDialogSize.height - 65));
	HeroDialog_bg->addChild(nameLabel);

	//����Label
	auto associationLabel = Label::create();
	associationLabel->setAnchorPoint(Point(0, 1));
	associationLabel->setContentSize(Size(140,30));
	associationLabel->setPosition(Vec2(170, heroDialogSize.height - 65));
	// �������й���  �� setstring���������������Ĺ������� ��û����setstring�����޼��빫�ᣩ
	associationLabel->setColor(ccc3(197, 28, 165));
	associationLabel->setString("���� ");
	HeroDialog_bg->addChild(associationLabel);


	//�ȼ�
	auto levelBg = Sprite::create("Dialog/hero_dialog/hero_dialoglevel.png");
	levelBg->setAnchorPoint(Vec2(0, 1));
	levelBg->setPosition(Vec2(30, heroDialogSize.height - 85));
	HeroDialog_bg->addChild(levelBg);

	auto levelLabel = Label::create();
	levelLabel->setPosition(levelBg->getContentSize().width / 2-5, levelBg->getContentSize().height / 2);
	levelLabel->setString("100");
	levelLabel->setSystemFontSize(25);
	levelBg->addChild(levelLabel);

	//������
	//���ݵ�ǰ���� �� ��һ�ȼ������ ��ֵ�����������ĺ�������
	auto valueBarBg = Sprite::create("Dialog/hero_dialog/hero_dialoglevelBg.png");
	valueBarBg->setAnchorPoint(Point(0, 1));
	valueBarBg->setPosition(20 + levelBg->getContentSize().width, heroDialogSize.height - 85);
	HeroDialog_bg->addChild(valueBarBg);

	auto valueBar = Sprite::create("Dialog/hero_dialog/hero_dialoglevelBar.png");
	valueBar->setAnchorPoint(Point(0, 0.5));
	valueBar->setPosition(13, valueBarBg->getContentSize().height / 2);
	valueBarBg->addChild(valueBar);
	valueBar->setScaleX(0.5);

	//ս����ֵ
	//�������������setring��
	auto battelValue = Label::create();
	battelValue->setString("9999999");
	battelValue->setSystemFontSize(35);
	battelValue->setPosition(140, 165);
	HeroDialog_bg->addChild(battelValue);


	//��� ������





	//�Ҳ౳����
	auto rightFrameBg = Sprite::create("Dialog/hero_dialog/hero_dialogRightBg.png");
	rightFrameBg->setAnchorPoint(Point(1, 0.5));
	rightFrameBg->setPosition(heroDialogSize.width - 10, heroDialogSize.height / 2-3);
	HeroDialog_bg->addChild(rightFrameBg);


	// ������ť
	auto advanceBtn = Button::create("Dialog/hero_dialog/hero_dialogAdvance_normal.png", "Dialog/hero_dialog/hero_dialogAdvance_seclet.png");
	


	//��ȡ��ť
	auto receiveBut = Button::create("Dialog/hero_dialog/hero_dialogReceive_normal.png", "Dialog/hero_dialog/hero_dialogReceive_seclet.png");
	receiveBut->setAnchorPoint(Point(0.5, 0));
	receiveBut->setPosition(Point(rightFrameBg->getContentSize().width/2, 10));
	receiveBut->addClickEventListener(receiveCallBack);
	rightFrameBg->addChild(receiveBut);


	//�رհ�ť
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
	
	//�ָ��ݴ������� stoneId ȥ��ȡ��������� ��stoneId ����Ϣ��Ȼ�����id ȥ��ȡstone�ľ�̬����

	


	//��͸�����ֲ�
	CustomLayerColor* maskLayer = CustomLayerColor::create(ccc4(0, 0, 0, 80));
	maskLayer->setAnchorPoint(Point::ZERO);
	maskLayer->setPosition(Point::ZERO);
	_dialog->addChild(maskLayer);


	//��ʯǿ��������
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


	
	//����һ
	//auto mater1 = Sprite::create("");



	//���϶�
//	auto mater2 = Sprite::create("");

	


	//��stoneID��ʯ
	auto stoneSprite = Sprite::create("item/item_i_chashaobao.png");
	stoneSprite->setPosition(200, 250);
	stoneStrengBg->addChild(stoneSprite);


	//��ǰ�ȼ�����������
	//// ��ȡ�������иý�ʯ �õȼ�����Ϣ
	auto nowAttackLabel = Label::create();
	nowAttackLabel->setAnchorPoint(Point(0, 0.5));
	nowAttackLabel->setPosition(160, 110);
	nowAttackLabel->setString("+10");
	nowAttackLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nowAttackLabel);

	//��ǰ�ȼ��������ٶ�
	auto nowSpeedLabel = Label::create();
	nowSpeedLabel->setAnchorPoint(Point(0, 0.5));
	nowSpeedLabel->setPosition(160, 85);
	nowSpeedLabel->setString("+20");
	nowSpeedLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nowSpeedLabel);

	//��һ�ȼ�����������
	auto nextAttackLabel = Label::create();
	nextAttackLabel->setAnchorPoint(Point(0, 0.5));
	nextAttackLabel->setPosition(360, 110);
	nextAttackLabel->setString("+20");
	nextAttackLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nextAttackLabel);

	//��һ�ȼ��������ٶ�
	auto nextSpeedLabel = Label::create();
	nextSpeedLabel->setAnchorPoint(Point(0, 0.5));
	nextSpeedLabel->setPosition(360, 85);
	nextSpeedLabel->setSystemFontSize(15);
	stoneStrengBg->addChild(nextSpeedLabel);

	//ǿ����ť
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