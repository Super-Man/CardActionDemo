//
//  SelectButton.h
//  GameBall
//
//  Created by zhongtao on 14-4-12.
//
//

#ifndef __GameBall__SelectButton__
#define __GameBall__SelectButton__

#include <iostream>
#include "../CoreFramework/BaseSprite.h"
#include "../Include/IncludeAllHead.h"
#include "../CoreFramework/GameHelper.h"
#include "../CustomCommon/PetHeadSprite.h"
#include "../sqlite3/GuanKaMsgDAO.h"
#include "../CoreFramework/AudioEngine.h"

typedef void (Ref::*SEL_CALL)(Node*);
#define button_selector(_SELECTOR) (SEL_CALL)(&_SELECTOR)
#define bind_function(_SELECTOR_,_Target_,...) std::bind(&_SELECTOR_,_Target_, std::placeholders::_1, ##__VA_ARGS__)
/**带选择状态的按钮**/
enum kSelectButtonState
{
    kButtonNormal,
    kButtonSelected,
};

enum eFuBenButtonState
{
    kNotTongGuan,
    kNewFuBen,
    kTongGuanFuBen,
};

enum eSelectButtonTag/**1100开始**/
{
    kFuBenButtonNameTag,//副本名字
    kFuBenXingLabTag,//当前副本获得的星
    kFuBenXingSpTag,
    kFuBenStateSpTag,//当前副本状态 新的or已通关的
    kFuBenTime,//倒计时
    kGuanKaStateSpTag,
    kGuanKaBossSpTag,
    kGuanKaNameTag,
    kGuanKaTiLiTag,
    kGuanKaZhanLiTag,
    kGuanKaXingTag,
    kGuanKaDiaoLuoTag,
};
class SelectButton:public BaseSpriteDelegate,public Node
{
public:
    SelectButton();
    ~SelectButton();
    
    static SelectButton* createWith(const char* nomal,const char* select,const char* title = nullptr);
    static SelectButton* createWithHightLight(const char* nomal,const char* select,const char* hightLight,const char* title = nullptr);
    bool init(const char* nomal,const char* select,const char* title = nullptr);
    bool initHightLight(const char* nomal,const char* select,const char* hightLight,const char* title = nullptr);
    
    virtual void touchBeginBaseSprite(Ref* sender,Point pos);
    virtual void touchEndBaseSprite(Point pos);
    
    void upDateButton(const char* nomal,const char* select,const char* title = nullptr);
    void setNormal();
    void setSelected();
    
    void addTargetAndCallBack(Ref* target,SEL_CALL selector);
    void addFunction(const std::function<void(Node*)> &function);
    void pressBtn();
    void setButtonPos(Point pos);
    Size getButtonSize();
    
    /**副本按钮(外面的大关卡)**/
    void fuBenInfo(CSVINFO_GuanKa* fuBen);
    void fubenName(const char* name);
    void fubenStatus(eFuBenButtonState state);
    void fubenXing(int haveGot,int total);
    void timeInfo(const char* c);//时间信息
    //
    CC_SYNTHESIZE(eFuBenButtonState, _fuBenState, FuBenState);
    Sprite* _fubenStateSp;
    Sprite* _fubenXingSp;
    LabelBMFont* _fubenXingLab,*_fubenNameLab,*_timeLab;
    /**副本按钮**/
    
    /**关卡按钮（里面的小关卡）**/
    void guankaInfo(CSVINFO_FBMapInfo* guanKaInfo);
    void guankaStatus(eFuBenButtonState state);
    void bossSp(const char* picPath,int bossType);
    void guanKaName(const char* name);
    void tiLi(int needTiLi);
    void zhanLi(int needZhanLi);
    void xingInfo(int curXing);
    void diaoLuo(const char* picPath);
    //
    PetHeadSprite* _bossHeadSp;
    Sprite* _guanKaStateSp;
    LabelBMFont* _guankaNameLab,* _guankaTiLi,* _guankaZhanLi;
    Sprite* _guankaDiaoLuo;
    Sprite* _xing[3];
    /**关卡按钮**/
    
    void setTouchArea(Rect area);
public:
    LabelBMFont* _title;
    bool touch;
    CC_SYNTHESIZE(kSelectButtonState, _state, ButtonState);
    CC_SYNTHESIZE(bool, _stateControl, StateControl);//是否要开启第二次点击取消选择状态
    CC_SYNTHESIZE(bool, _needSwal, Swallow);
    CC_SYNTHESIZE(bool, _endScale, EndScaleChange);
    CC_SYNTHESIZE(bool, _timeControl, ClickTimeControl);
    CC_SYNTHESIZE(int, _buttonID, ButtonID);
    CC_SYNTHESIZE(bool, _enable, Enable);
    CC_SYNTHESIZE(bool, _soundEff, SoundEff);
    BaseSprite* _button;
    Node* parent;
    CC_SYNTHESIZE(BaseSprite*, _container, ButtonContainer);
private:
    char* _selecte;
    char* _normal;
    char* _hightLight;
    Ref* _target;
    SEL_CALL _callBack;
    Node* _sender;
    std::function<void(Node*)> _function;
    ActionInterval* _endEffect;
    Point _beginPoi;
    //控制两次点击按钮的时间间隔
    struct cc_timeval _beginTime;
    struct cc_timeval _endTime;
    Rect _touchArea;
};
#endif /* defined(__GameBall__SelectButton__) */
