//
// SwallowTouch.h 
//
// 伸缩菜单类
//
// Create By PenKeJie on 15-4-10
//


#pragma once
#ifndef __SWALLOWTOUCH_H__
#define __SWALLOWTOUCH_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <ui/UIWidget.h>


USING_NS_CC;
using namespace cocostudio::timeline;
using namespace ui;


enum ButtonTag
{
	HOERBUTTON,
	SOUL,
	STRONGTHEN,
	TEAMC,
	SETTINGSICON

};

class SwallowTouch : public Layer
{
public:
	SwallowTouch();
	~SwallowTouch();

	virtual bool init();

	void MoveMenu(Ref *obj);

	Sprite* m_pSwallBg;

	bool _isScale;

	void Hore_Menu(Ref *obj);

	void Hore_Menu2(Ref *obj);


	//Hoer Button
	CC_SYNTHESIZE(ui::Button*, m_pHeroBtn, HeroBtn);

	//footer_soul 
	CC_SYNTHESIZE(ui::Button*, m_pFooter_soulBtn, Footer_soulBtn);

	//Strongthen;
	CC_SYNTHESIZE(ui::Button*, m_pStrongthenBtn, StrongthenBtn);

	//Team 
	CC_SYNTHESIZE(ui::Button*, m_pTeamBtn, TeamBtn);

	//Settings_icon
	CC_SYNTHESIZE(ui::Button*, m_pSettingsBtn, SettingsBtn);

	//选项弹框;
	void MenuAllButton(Ref* obj);
	
	CREATE_FUNC(SwallowTouch);
};

#endif // !__SWALLOWTOUCH_H__