//
//  GameDialog.h
//  ������
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
		�����Ϣ����
		����˵����
		
		parent		�õ�������� parent����ڵ���
		zOrder		���õ����Z��㼶����Ϊ�õ��������ֲ㣬����zOrder����Ҫ��parent�ڵ�����ߵ�
		position	���õ����λ��(ע��Ŀǰ�������Ѿ�д�������䣬���Բ���Ҫ��ò���)
		receiveCallBack		��ȡ��ť�ص�����
		advanceCallBack     �����ƺŰ�ť�ص�����
	****************************************/
	void HeroDialogShow(Node* parent, int zOrder,const std::function<void(Ref*)>& receiveCallBack, const std::function<void(Ref*)>& advanceCallBack ,Point position = Point::ZERO);


	/**********************************
	  ��ʯǿ������
	  ����˵����
	  stoneId     ��ʯ id
	  zOrder      ���øõ���� Z��㼶
	  parent      ���õ���ļ��ؽڵ�
	  position    ���õ����б���ͼ��λ�ã���������
	***********************************/

	void StoneStrengShow(int stoneId, int zOrder, Node* parent, Point position);



private:
	
	static GameDialog* m_dialogInstance;

	//������������Ҫ���ӽڵ�
	Node* _dialog;


private:

	//�رհ�ť�ص�����
	void closeBtnCallBack(Ref* pSend);

};












#endif
