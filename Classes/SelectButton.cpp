//
//  SelectButton.cpp
//  GameBall
//
//  Created by zhongtao on 14-4-12.
//
//

#include "SelectButton.h"
#include "../sqlite3/FuBenMsgDAO.h"

SelectButton::SelectButton()
{
    _title = nullptr;
    _selecte = nullptr;
    _normal = nullptr;
    touch = false;
    _target = nullptr;
    _callBack = nullptr;
    _container = nullptr;
    _hightLight = nullptr;
    _stateControl = false;
    _needSwal = true;
    _endScale = false;
    _timeControl = false;
    _buttonID = -1;
    
    auto call = CallFuncN::create([this](Node* sender)
                                  {
                                      sender->setScale(1.0f);
                                  });
    
    auto scaleBy = ScaleBy::create(0.2f, 1.2f);
    _endEffect = Sequence::create(call,scaleBy,scaleBy->reverse(), NULL);
    _endEffect->retain();
    
    _touchArea =  Rect(0, 0, Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    
    /**副本**/
    _fubenStateSp = nullptr;
    _fubenXingSp = nullptr;
    _fubenXingLab = nullptr;
    _fubenNameLab = nullptr;
    _timeLab = nullptr;
    /**关卡**/
    _bossHeadSp = nullptr;
    _guanKaStateSp = nullptr;
    _guankaNameLab = nullptr;
    _guankaTiLi = nullptr;
    _guankaZhanLi = nullptr;
    _guankaDiaoLuo = nullptr;
    for (int i = 0; i<3; ++i)
    {
        _xing[i] = nullptr;
    }
    
    _enable = true;
    _soundEff = true;
}

SelectButton::~SelectButton()
{
    _endEffect->release();
    this->removeAllChildrenWithCleanup(true);
}

SelectButton* SelectButton::createWith(const char *nomal, const char *select,const char* title /*= nullptr*/)
{
    SelectButton* _new = new SelectButton();
    if (_new && _new->init(nomal, select,title))
    {
        _new -> autorelease();
        return _new;
    }
    CC_SAFE_DELETE(_new);
    return nullptr;
}

SelectButton* SelectButton::createWithHightLight(const char *nomal, const char *select, const char *hightLight,const char* title /*= nullptr*/)
{
    SelectButton* _new = new SelectButton();
    if (_new && _new->initHightLight(nomal, select, hightLight,title))
    {
        _new->autorelease();
        return _new;
    }
    CC_SAFE_DELETE(_new);
    return nullptr;
}

bool SelectButton::init(const char *nomal, const char *select,const char* title /*= nullptr*/)
{
    _normal = const_cast<char*>(nomal);
    _selecte = const_cast<char*>(select);
    _container = BaseSprite::createWithFrameName(_normal);
    this->addChild(_container,1);
    _container->setNeedSwallow(false);
    _container->setBaseDelegate(this);
    _container->setCustomPriority(kMaxTouchPriority);
    
    if (title != nullptr)
    {
        _title = LabelBMFont::create(title, FONT_TEXT);
        _title->setScale(0.9);
//        _title->setColor(Color3B::BLACK);
//        _title->enableStroke(Color3B::WHITE, 2);
        _title->setPosition(_container->getContentSize().width/2,_container->getContentSize().height/2);
        _container->addChild(_title,2);
    }
    
    if (_normal)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normal);
        _container->setDisplayFrame(frame);
    }

    return true;
}

bool SelectButton::initHightLight(const char *nomal, const char *select, const char *hightLight,const char* title /*= nullptr*/)
{
    _normal = const_cast<char*>(nomal);
    _selecte = const_cast<char*>(select);
    _hightLight = const_cast<char*>(hightLight);
    _container = BaseSprite::createWithFrameName("blank.png");
    this->addChild(_container,1);
    _container->setNeedSwallow(true);
    _container->setBaseDelegate(this);
    _container->setCustomPriority(kMaxTouchPriority);
    
    if (title != nullptr)
    {
        _title = LabelBMFont::create(title, FONT_TEXT);
        _title->setScale(0.9);
//        _title->setColor(Color3B::BLACK);
        //        _title->enableStroke(Color3B::WHITE, 2);
        _title->setPosition(_container->getContentSize().width/2,_container->getContentSize().height/2);
        _container->addChild(_title,2);
    }
    
    if (_normal)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normal);
        _container->setDisplayFrame(frame);
    }
    
    return true;
}

void SelectButton::upDateButton(const char *nomal, const char *select,const char* title /*= nullptr*/)
{
    _normal = const_cast<char*>(nomal);
    _selecte = const_cast<char*>(select);
    
    if (_title)
    {
        if (title)
        {
            _title->setString(title);
        }
    }
    else
    {
        _title = LabelBMFont::create(title, FONT_TEXT);
        _title->setScale(0.9);
        _title->setAnchorPoint(Point(0.5, 0.5));
//        _title->setColor(Color3B::BLACK);
//        _title->enableStroke(Color3B::WHITE, 2);
        _title->setPosition(_container->getContentSize().width/2,_container->getContentSize().height/2);
        _container->addChild(_title,2);
    }
    
    if (_normal)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normal);
        _button->setDisplayFrame(frame);
    }
}

void SelectButton::setNormal()
{
    if (_container)
    {
        /*auto frame = SpriteFrame::createWithTexture(icon->getTexture(), rect);*/
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normal);
        _container->setDisplayFrame(frame);
        _state = kButtonNormal;
    }
}

void SelectButton::setSelected()
{
    if (_container)
    {
        /*
        auto frame = SpriteFrame::createWithTexture(icon->getTexture(), rect);
        */
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_selecte);
        _container->setDisplayFrame(frame);
        _state = kButtonSelected;
    } 
}

void SelectButton::addTargetAndCallBack(cocos2d::Ref *target, SEL_CALL selector)
{
//    if (target)
//    {
//        target->retain();
//    }
//    if (_target)
//    {
//        _target->release();
//    }
    _target = target;
    _callBack = selector;
}

void SelectButton::addFunction(const std::function<void(Node*)> &function)
{
    _function = function;
}

void SelectButton::touchBeginBaseSprite(cocos2d::Ref *sender, cocos2d::Point pos)
{
    if (!_touchArea.containsPoint(pos) || !_enable)
    {
        return;
    }
    _beginPoi = pos;
    _button = static_cast<BaseSprite*>(sender);
    if (_button)
    {
        if (_hightLight)
        {
            auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_hightLight);
            _container->setDisplayFrame(frame);
        }
        touch = true;
        if (!_endScale)
        {
            _button->setScale(1.2f);
//            if (_title)
//            {
//                _title->setScale(1.2f);
//            }
        }
    }
    else
    {
        touch = false;
        _state = kButtonNormal;
    }
    if (_timeControl)
    {
        CCTime::gettimeofdayCocos2d(&_beginTime, nullptr);
    }
}

void SelectButton::touchEndBaseSprite(cocos2d::Point pos)
{
    if (!_touchArea.containsPoint(pos) || !_enable)
    {
        return;
    }
    auto end = pos - _beginPoi;
    if (fabs(end.x)>30 || fabs(end.y)>30)
    {
        return;
    }
    
    if (_timeControl)
    {
        CCTime::gettimeofdayCocos2d(&_endTime, nullptr);
        long timeDiff = _endTime.tv_usec - _beginTime.tv_usec;
//        timeDiff = timeDiff * 1000 + (_endTime.tv_usec - _beginTime.tv_usec)/1000;
//        log("%ld",timeDiff);
        if (timeDiff < 50)
        {
            return;
        }
    }
    
    if (_button == nullptr)
    {
        return;
    }
    if (touch)
    {
        if (_state != kButtonSelected)
        {
            this->setSelected();
            this->pressBtn();
        }
        else
        {
            if (!_stateControl)
            {
                this->setNormal();
                this->pressBtn();
            }  
        }
    }
    if (_endScale)
    {
        _button->stopAllActions();
        _button->runAction(_endEffect);
//        if (_title && _title->getParent() != nullptr)
//        {
//            _title->stopAllActions();
//            _title->runAction(_endEffect->clone());
//        }
    }
    else
    {
        _button->setScale(1.0f);
//        if (_title && _title->getParent() != nullptr)
//        {
//            _title->setScale(1.0f);
//        }
    }
    _button = nullptr;
}

void SelectButton::pressBtn()
{
    if (_callBack)
    {
        (_target->*_callBack)(this);
    }
    else if (_function)
    {
        _function(this);
    }
    if (_soundEff)
    {
        AudioEngine::sharedAudioEngine()->playEffSound(kSub_Menu_Click);
    }    
}

void SelectButton::setButtonPos(cocos2d::Point pos)
{
    _container->setPosition(pos);
//    if (_title)
//    {
//        _title->setPosition(pos);
//    }
}

Size SelectButton::getButtonSize()
{
    return _container->getContentSize();
}

void SelectButton::setTouchArea(Rect area)
{
    _touchArea = area;
}

#pragma mark 定制内容---副本按钮和关卡按钮用到

#pragma mark /**副本按钮**/
void SelectButton::fuBenInfo(CSVINFO_GuanKa *fuBen)
{
    CCASSERT(_container != nullptr, "_container can't be nullptr");
    //名字
    fubenName(fuBen->sName.c_str());
    
    auto isTongGuan = false;
    //星
    auto total = 0;
    auto haveGot = 0;
    auto str = __String::create(fuBen->sXiaoGuanKa.c_str());
    auto ar = str->componentsSeparatedByString("~");
    for (int j = 0; j<ar->count(); ++j)
    {
        auto fubenId = ((__String*)ar->getObjectAtIndex(j))->intValue();
        auto guankaData = (CSVINFO_FBMapInfo*)CsvFileManage::csvfbmapInfoInstance()->FindCsvPropertyWith(fubenId);/*里面的小关卡*/
        CCASSERT(guankaData != nullptr, "");
        total += guankaData->_allPingFen;
        auto guankaInfo = GuanKaMsgDAO::getInstance()->getGuanKaInfoWith(fubenId);
        if (guankaInfo.nGuanKaID != 0)
        {
            haveGot += guankaInfo.nGotXing;
            if (guankaInfo.nTongGuan == 1)
            {
                isTongGuan = true;
            }
            else
            {
                isTongGuan = false;
            }
        }
    }
    fubenXing(haveGot, total);
    
    auto info = FuBenMsgDAO::getInstance()->getFuBenInfoWith(fuBen->nID);
    if (info.nIsNew)
    {
        fubenStatus(kNewFuBen);
    }
    else if (info.nTongGuan)
    {
        fubenStatus(kTongGuanFuBen);
    }
    else
    {
        fubenStatus(kNotTongGuan);
    }
}

void SelectButton::fubenStatus(eFuBenButtonState state)
{
    _fuBenState = state;
    string path = "UI_10019_3.png";//通关的sp
    if (state == kNewFuBen)
    {
        path = "UI_10019_4.png";
    }
    else if (state == kNotTongGuan)
    {
        path = "blank.png";
    }
    if (_fubenStateSp && _fubenStateSp->getParent() != nullptr)
    {
        _fubenStateSp->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(path.c_str()));
    }
    else
    {
        _fubenStateSp = Sprite::createWithSpriteFrameName(path.c_str());
        CCASSERT(_fubenStateSp != nullptr, "");
        _fubenStateSp->setPosition(_container->getContentSize().width*0.256,_container->getContentSize().height*0.828);
        _fubenStateSp->setTag(kFuBenStateSpTag);
        _container->addChild(_fubenStateSp);
    }
}

void SelectButton::fubenName(const char *name)
{
    if (_fubenNameLab && _fubenNameLab->getParent() != nullptr)
    {
        _fubenNameLab->setString(name);
    }
    else
    {
        _fubenNameLab = LabelBMFont::create(name, FONT_GUANKA);
        CCASSERT(_fubenNameLab != nullptr, "");
        _fubenNameLab->setScale(0.9);
//        _fubenNameLab->enableStroke(Color3B::BLACK, 1);
        _fubenNameLab->setPosition(_container->getContentSize().width*0.19,_container->getContentSize().height*0.39);
        _fubenNameLab->setAnchorPoint(Point(0, 0.5));
        _fubenNameLab->setTag(kFuBenButtonNameTag);
        _container->addChild(_fubenNameLab);
    }
}

void SelectButton::fubenXing(int haveGot,int total)
{
    string picPath = "UI_10019_1.png";
    if (haveGot == total)
    {
        picPath = "UI_10019_2.png";
    }
    
    if (_fubenXingSp && _fubenXingSp->getParent() != nullptr)
    {
        _fubenXingSp->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picPath.c_str()));
    }
    else
    {
        _fubenXingSp = Sprite::createWithSpriteFrameName(picPath.c_str());
        CCASSERT(_fubenXingSp != nullptr, "");
        _fubenXingSp->setPosition(_container->getContentSize().width*0.927,_container->getContentSize().height*0.531);
        _fubenXingSp->setTag(kFuBenXingSpTag);
        _container->addChild(_fubenXingSp);
    }
    
    if (_fubenXingLab && _fubenXingLab->getParent() != nullptr)
    {
        _fubenXingLab->setString(StringUtils::format("%d/%d",haveGot,total));
    }
    else
    {
        _fubenXingLab = LabelBMFont::create(StringUtils::format("%d/%d",haveGot,total).c_str(), FONT_TEXT);
        CCASSERT(_fubenXingLab != nullptr, "");
        _fubenXingLab->setScale(0.7);
//        _fubenXingLab->enableStroke(Color3B::BLACK, 1);
        _fubenXingLab->setPosition(_container->getContentSize().width*0.93, _container->getContentSize().height*0.281);
        _fubenXingLab->setTag(kFuBenXingLabTag);
        _container->addChild(_fubenXingLab);
    }
}

void SelectButton::timeInfo(const char *c)
{
    if (_timeLab && _timeLab->getParent() != nullptr)
    {
        _timeLab->setString(c);
    }
    else
    {
        _timeLab = LabelBMFont::create(c, FONT_GUANKA);
        CCASSERT(_timeLab != nullptr,"");
        _timeLab->setPosition(_container->getContentSize().width*0.602, _container->getContentSize().height*0.704);
        _timeLab->setScale(0.7f);
        _timeLab->setTag(kFuBenTime);
        
        _container->addChild(_timeLab);
    }
}

#pragma mark /**关卡按钮**/
void SelectButton::guankaInfo(CSVINFO_FBMapInfo *guanKaInfo)
{
    auto info = GuanKaMsgDAO::getInstance()->getGuanKaInfoWith(guanKaInfo->_guanQiaID);
    //是否通关、是否是新的之类
    if (info.nIsNew)
    {
        guankaStatus(kNewFuBen);
    }
    else if (info.nTongGuan)
    {
        guankaStatus(kTongGuanFuBen);
    }
    else
    {
        guankaStatus(kNotTongGuan);
    }
    
    //boss图片
    bossSp(guanKaInfo->_bossIcon.c_str(),guanKaInfo->_bossType);
    //名字
    guanKaName(guanKaInfo->_guanQiaName.c_str());
    //体力
    tiLi(guanKaInfo->_TiLi);
    //战力
//    zhanLi(guanKaInfo->_ZhanLi);
    //掉落
    diaoLuo(guanKaInfo->_dropRes.c_str());//这个值包含了掉落物品id和数量
    //星
    xingInfo(info.nGotXing);
    //尹段
}

void SelectButton::guankaStatus(eFuBenButtonState state)
{
    _fuBenState = state;
    string path = "UI_10019_3.png";//通关的sp
    if (state == kNewFuBen)
    {
        path = "UI_10019_4.png";
    }
    else if (state == kNotTongGuan)
    {
        path = "blank.png";
    }
    if (_guanKaStateSp && _guanKaStateSp->getParent() != nullptr)
    {
        _guanKaStateSp->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(path.c_str()));
    }
    else
    {
        _guanKaStateSp = Sprite::createWithSpriteFrameName(path.c_str());
        CCASSERT(_guanKaStateSp != nullptr, "");
        _guanKaStateSp->setPosition(_container->getContentSize().width*0.35,_container->getContentSize().height*0.828);
        _guanKaStateSp->setTag(kGuanKaStateSpTag);
        _container->addChild(_guanKaStateSp);
    }
}

void SelectButton::bossSp(const char *picPath,int bossType)
{
    if (_bossHeadSp && _bossHeadSp->getParent() != nullptr)
    {
        _bossHeadSp->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picPath));
        _bossHeadSp->headFrame(bossType);
    }
    else
    {
        _bossHeadSp = PetHeadSprite::createWithPngName(picPath);
        CCASSERT(_bossHeadSp != nullptr, "");
        _bossHeadSp->headFrame(bossType);
        _bossHeadSp->setPosition(_container->getContentSize().width*0.132,_container->getContentSize().height*0.537);
        _bossHeadSp->setTag(kGuanKaBossSpTag);
        _container->addChild(_bossHeadSp);
    }
}

void SelectButton::guanKaName(const char *name)
{
    if (_guankaNameLab && _guankaNameLab->getParent() != nullptr)
    {
        _guankaNameLab->setString(name);
    }
    else
    {
        _guankaNameLab = LabelBMFont::create(name, FONT_GUANKA);
        CCASSERT(_guankaNameLab != nullptr, "");
        _guankaNameLab->setScale(0.9);
//        _guankaNameLab->enableStroke(Color3B::BLACK, 1);
        _guankaNameLab->setAnchorPoint(Point(0, 0.5));
        _guankaNameLab->setPosition(_container->getContentSize().width*0.261,_container->getContentSize().height*0.582);
        _guankaNameLab->setTag(kGuanKaNameTag);
        _container->addChild(_guankaNameLab);
    }
}

void SelectButton::tiLi(int needTiLi)
{
    if (_guankaTiLi && _guankaTiLi->getParent() != nullptr)
    {
        _guankaTiLi->setString(StringUtils::format("%d",needTiLi).c_str());
    }
    else
    {
        _guankaTiLi = LabelBMFont::create(StringUtils::format("%d",needTiLi).c_str(),FONT_TEXT);
        CCASSERT(_guankaTiLi != nullptr, "");
        _guankaTiLi->setScale(0.7);
        _guankaTiLi->setAnchorPoint(Point(0, 0.5));
        _guankaTiLi->setPosition(_container->getContentSize().width*0.48,_container->getContentSize().height*0.269);
        _guankaTiLi->setTag(kGuanKaTiLiTag);
        _container->addChild(_guankaTiLi);
        
        auto tiliXiaohao = LabelBMFont::create("体力消耗:", FONT_TEXT);
        tiliXiaohao->setScale(0.7);
        tiliXiaohao->setPosition(_container->getContentSize().width*0.381,_container->getContentSize().height*0.269);
        _container->addChild(tiliXiaohao);
    }
}

void SelectButton::zhanLi(int needZhanLi)
{
    if (_guankaZhanLi && _guankaZhanLi->getParent() != nullptr)
    {
        _guankaZhanLi->setString(StringUtils::format("%d",needZhanLi).c_str());
    }
    else
    {
        _guankaZhanLi = LabelBMFont::create(StringUtils::format("%d",needZhanLi).c_str(),FONT_TEXT);
        CCASSERT(_guankaZhanLi != nullptr, "");
        _guankaZhanLi->setScale(0.7);
//        _guankaZhanLi->enableStroke(Color3B::BLACK, 1);
        _guankaZhanLi->setAnchorPoint(Point(0, 0.5));
        _guankaZhanLi->setPosition(_container->getContentSize().width*0.817,_container->getContentSize().height*0.851);
        _guankaZhanLi->setTag(kGuanKaZhanLiTag);
        _container->addChild(_guankaZhanLi);
        
        auto lab = LabelBMFont::create("战力:", FONT_TEXT);
        lab->setScale(0.6f);
//        lab->enableStroke(Color3B::BLACK, 1);
        lab->setPosition(_container->getContentSize().width*0.755,_container->getContentSize().height*0.851);
        _container->addChild(lab);
    }
}

void SelectButton::xingInfo(int curXing)
{
    for (int i = 0; i<3; ++i)
    {
        if (_xing[i] && _xing[i]->getParent() != nullptr)
        {
            if (i < curXing)//得到了的星显示出来
            {
                _xing[i]->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_10019_2.png"));
            }
            else//灰色
            {
                _xing[i]->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_10019_1.png"));
            }
        }
        else
        {
            if (i < curXing)
            {
                _xing[i] = Sprite::createWithSpriteFrameName("UI_10019_2.png");
            }
            else
            {
                _xing[i] = Sprite::createWithSpriteFrameName("UI_10019_1.png");
            }
            CCASSERT(_xing[i] != nullptr, "");
            _xing[i]->setPosition(_container->getContentSize().width*(0.899 - (2-i)*0.07),_container->getContentSize().height*0.597);
            _container->addChild(_xing[i]);
        }
    }
}

void SelectButton::diaoLuo(const char *picPath)
{
    if (_guankaDiaoLuo && _guankaDiaoLuo->getParent() != nullptr)
    {
        _guankaDiaoLuo->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(picPath));
    }
    else
    {
        _guankaDiaoLuo = Sprite::createWithSpriteFrameName(picPath);
        _guankaDiaoLuo->setPosition(_container->getContentSize().width*0.914,_container->getContentSize().height*0.254);
        _container->addChild(_guankaDiaoLuo);
        _guankaDiaoLuo->setScale(0.9);
        
        auto diao = LabelBMFont::create("掉落", FONT_TEXT);
        diao->setScale(0.6f);
//        diao->enableStroke(Color3B::BLACK, 1);
        diao->setPosition(_container->getContentSize().width*0.805,_container->getContentSize().height*0.254);
        _container->addChild(diao);
    }
}