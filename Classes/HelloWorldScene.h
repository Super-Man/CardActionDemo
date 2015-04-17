#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include <vector>

class HelloWorld : public cocos2d::Layer ,public cocos2d::extension::TableViewDataSource,public cocos2d::extension::TableViewDelegate
{
public:
	enum BagBtn
	{
		BTNEQUIP,
		BTNITEM,
		BTNSKILL
	};




	struct ItemInfo
	{
		std::string ItemName;
		int ItemType;
		int ItemNum;
		bool isWear = false;
	};

	std::vector<ItemInfo> ItemVec;
	


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	void ButtentouchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::SpriteBatchNode *ItemBackGround;
};

#endif // __HELLOWORLD_SCENE_H__
