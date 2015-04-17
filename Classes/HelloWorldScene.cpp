#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	/************************************************************************/
	/*  
			bag Test    
	*/
	/************************************************************************/
	
	
	for (int i = 1; i < 11;i++)
	{
		char strNma[20];
		sprintf(strNma, "item/%d.png",i);
		ItemInfo ite;
		ite.ItemName = strNma;
		ite.ItemType = 2;
		ite.ItemNum = 2+i;
		ItemVec.push_back(ite);

	}

	 ItemBackGround = SpriteBatchNode::create("item_background.png");
	this->addChild(ItemBackGround);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	TableView* tabelView = TableView::create(this, CCSizeMake(450, 400));
	tabelView->setDirection(ScrollView::Direction::VERTICAL);
	tabelView->setPosition(Vec2(visibleSize.width / 2, 200));
	tabelView->setDelegate(this);
	tabelView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tabelView);
	tabelView->reloadData();
   
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	CCLOG("cell touch index _%d", cell->getIdx());
}

cocos2d::Size HelloWorld::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return Size(450, 120);
}

cocos2d::extension::TableViewCell* HelloWorld::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	TableViewCell *cell = table->dequeueCell();
	if (!cell)
	{
		cell = new (std::nothrow)TableViewCell();
		cell->autorelease();	
	}
	if (cell)
	{
		cell->removeAllChildrenWithCleanup(true);
	}
	
	for (int i = 0; i < 3; i++)
	{
		if ((3 * idx + i) < ItemVec.size())
		{
			auto ItemBg = Sprite::createWithTexture(ItemBackGround->getTexture());
			ItemBg->setPosition(Vec2(63 * (2 * i + 1), 63));

			auto itemNumLabel = Label::create();
			itemNumLabel->setPosition(Vec2(113 * (2 * i + 1), 10));
			//itemNumLabel->setString(ItemVec[3 * idx + i].ItemNum)
			auto ItemButton = Button::create(ItemVec[3 * idx + i].ItemName);
			ItemButton->setPosition(Vec2(63 * (2 * i + 1), 63));
			ItemButton->setTag(3 * idx + i);
			ItemButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ButtentouchEvent, this));
			cell->addChild(ItemBg);
			cell->addChild(ItemButton);
		}

	}
	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return ItemVec.size()/3+1;
}

void HelloWorld::ButtentouchEvent(Ref *pSender,Widget::TouchEventType type)
{
	Button* pButn = (Button*)pSender;

	switch (type) {
	case Widget::TouchEventType::BEGAN:
		log("TOUCH_EVENT_BEGAN");
		CCLOG("PButton ' s target %d", pButn->getTag());
		break;



	case Widget::TouchEventType::MOVED:
		log("TOUCH_EVENT_MOVED");
		break;

	case Widget::TouchEventType::ENDED:
		log("TOUCH_EVENT_ENDED");
		break;
	case Widget::TouchEventType::CANCELED:
		log("TOUCH_EVENT_CANCELED");
		break;

	default:
		break;
	}

}