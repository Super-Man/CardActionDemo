//
//  GameDialog.h
//  弹框类
//  Created by ChenJinJun on 15-4-15.
//
//


#ifndef __GAME_DIALOG_HEADER__
#define __GAME_DIALOG_HEADER__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace ui;

class GameDialog :public Layer
{
public:
	GameDialog();
	~GameDialog();

	bool init();
	
	static	GameDialog* getInstance();

	
	/****************************************
		玩家信息弹框
		参数说明：
		
		parent		该弹框加载在 parent这个节点上
		zOrder		设置弹框的Z轴层级，因为该弹框有遮罩层，所以zOrder必须要是parent节点上最高的
		position	设置弹框的位置(注：目前函数内已经写好了适配，所以不需要填该参数)
		receiveCallBack		领取按钮回调函数
		advanceCallBack     提升称号按钮回调函数
	****************************************/
	void HeroDialogShow(Node* parent, int zOrder,const std::function<void(Ref*)>& receiveCallBack, const std::function<void(Ref*)>& advanceCallBack ,Point position = Point::ZERO);


	/**********************************
	  角石强化弹框
	  参数说明：
	  stoneId     角石 id
	  zOrder      设置该弹框的 Z轴层级
	  parent      设置弹框的加载节点
	  position    设置弹框中背景图的位置，这样方便
	***********************************/

	void StoneStrengShow(int stoneId, int zOrder, Node* parent, Point position);



private:
	
	static GameDialog* m_dialogInstance;

	//包涵弹框所需要的子节点
	Node* _dialog;


private:

	//关闭按钮回调函数
	void closeBtnCallBack(Ref* pSend);

};












#endif
