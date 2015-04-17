//
//  BaseSprite.cpp
//  
//
//  Created by ChenJinJun on 15-4-16.
//
//

#include "BaseSprite.h"
#include "AudioEngine.h"
int touchCount = 0;

BaseSprite::BaseSprite():
_pressTime(0.0),
_isLongPress(false),
_isSelected(false),
_customPriority(0),
_isCheckTouchCount(false),
_isCheckLongPress(false),
_spriteID(-1),
_spritePos(-1),
_spriteType(kSpriteTypeForDefault),
_canSelect(true),
_beSelected(false),
_needSwallow(false),
selecCount(0),
_touchEndCheck(false),
_clickEvent(true),
_pressEvent(false),
_beLocked(false),
_longPress(false)
{
    _baseDelegate = nullptr;
}

BaseSprite::~BaseSprite()
{
    _baseDelegate = nullptr;
    this->removeAllChildrenWithCleanup(true);
}

BaseSprite* BaseSprite::create()
{
    BaseSprite* _new = new BaseSprite();
    if (_new && _new->init())
    {
        _new->autorelease();
        return _new;
    }
    CC_SAFE_DELETE(_new);
    return nullptr;
}

BaseSprite* BaseSprite::createWith(const char *f)
{
    BaseSprite* _new = new BaseSprite();
    if (_new && _new->initWithFile(f))
    {
        _new->autorelease();
        return _new;
    }
    CC_SAFE_DELETE(_new);
    return nullptr;
}

BaseSprite* BaseSprite::createWithFrameName(const char *fName)
{
    BaseSprite* _new = new BaseSprite();
    if (_new && _new->initWithSpriteFrameName(fName))
    {
        _new->autorelease();
        return _new;
    }
    CC_SAFE_DELETE(_new);
    return nullptr;
}

void BaseSprite::onEnter()
{
    Sprite::onEnter();
    
    _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(_needSwallow);
    
    //触摸事件
    _listener->onTouchBegan = CC_CALLBACK_2(BaseSprite::onTouchBegan, this);
    
    _listener->onTouchMoved = CC_CALLBACK_2(BaseSprite::onTouchMoved, this);
    
    _listener->onTouchEnded = CC_CALLBACK_2(BaseSprite::onTouchEnded, this);
    
    _listener->onTouchCancelled = CC_CALLBACK_2(BaseSprite::onTouchCancelled, this);
    
    if (_customPriority)
    {
        _eventDispatcher->addEventListenerWithFixedPriority(_listener, _customPriority);
    }
    else
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    }
}

void BaseSprite::onExit()
{
    _eventDispatcher->removeEventListener(_listener);
    Sprite::onExit();
}

bool BaseSprite::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
   
    if (!_canSelect)
    {
        return false;
    }
    if (_beSelected)
    {
        return false;
    }
    
    _longPress = false;
    
    auto locationInNode = touch->getLocation();
    auto screenPos = this->getParent()->convertToWorldSpace(this->getPosition());
    auto anchor = this->getAnchorPoint();
    
    auto rect = Rect(screenPos.x - this->getContentSize().width*anchor.x*this->getScaleX(), screenPos.y-this->getContentSize().height*anchor.y*this->getScaleY(), this->getContentSize().width*this->getScaleX(), this->getContentSize().height*this->getScaleY());
    if (rect.containsPoint(locationInNode))
    {
        //  AudioEngine::sharedAudioEngine()->playEffSound(kSub_Menu_Click);
        _isSelected = true;
        if (_isCheckTouchCount)
        {
            ++touchCount;
            log("BaseSprite::touchCount-begin = %d",touchCount);
            if (touchCount>1)
            {
                --touchCount;
                return false;
            }
        }
        if (_isCheckLongPress)
        {
            this->schedule(schedule_selector(BaseSprite::upDateForLongPress), 0.1f);
        }
        
        if (_baseDelegate != nullptr)
        {
            _baseDelegate->_selSpriteID = _spriteID;
            _baseDelegate->_selSpritePos = _spritePos;
            _baseDelegate->_selSpriteType = _spriteType;
            _baseDelegate->touchBeginBaseSprite(this, locationInNode);
        }
        return true;
    }
    return false;
}

void BaseSprite::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    auto screenPos = Point::ZERO;
    auto anchor = this->getAnchorPoint();
    
    auto locationInNode = touch->getLocation();
    if (_baseDelegate != nullptr && _isSelected)
    {
        if (_isCheckLongPress)
        {
            this->unschedule(schedule_selector(BaseSprite::upDateForLongPress));
        }
        _baseDelegate->touchMoveBaseSprite(locationInNode);
    }
}

void BaseSprite::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)

    if (_isCheckTouchCount)
    {
        --touchCount;
        log("BaseSprite::touchCount-end = %d",touchCount);
    }
    auto locationInNode = touch->getLocation();
    auto screenPos = this->getParent()->convertToWorldSpace(this->getPosition());
    auto anchor = this->getAnchorPoint();
    
    if (_touchEndCheck)
    {
        auto rect = Rect(screenPos.x - this->getContentSize().width*anchor.x*this->getScaleX(), screenPos.y-this->getContentSize().height*anchor.y*this->getScaleY(), this->getContentSize().width*this->getScaleX(), this->getContentSize().height*this->getScaleY());
        if (rect.containsPoint(locationInNode))
        {
            if (_isCheckLongPress)
            {
                this->unschedule(schedule_selector(BaseSprite::upDateForLongPress));
                _pressTime = 0.0f;
                _isLongPress = false;
            }
            if (_baseDelegate != nullptr && !_longPress)
            {
                _baseDelegate->touchEndBaseSprite(locationInNode);
            }
        }
        this->setScale(1.0f);
    }
    else
    {
        if (_isCheckLongPress)
        {
            this->unschedule(schedule_selector(BaseSprite::upDateForLongPress));
            _pressTime = 0.0f;
            _isLongPress = false;
        }
        if (_baseDelegate != nullptr && !_longPress)
        {
            _baseDelegate->touchEndBaseSprite(locationInNode);
        }
    }
}

void BaseSprite::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void BaseSprite::upDateForLongPress(float dt)
{
    _pressTime += 0.1f;
    _isLongPress = false;
    if (_pressTime>=0.3f) {
        if (_baseDelegate != nullptr) {
            this->unschedule(schedule_selector(BaseSprite::upDateForLongPress));
            /*if (_pressEvent)
            {
                _baseDelegate->longTimeTouchBaseSprite(this, this->getPosition());
            }*/
            _baseDelegate->longTimeTouchBaseSprite(this, this->getPosition());
            log("BaseSprite::长按操作");
            _pressTime = 0.0f;
            _isLongPress = true;
            _longPress = true;
        }
    }
}