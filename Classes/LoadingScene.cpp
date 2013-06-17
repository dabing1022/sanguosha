
#include "TableScene.h"
#include "LoadingScene.h"

#include <boost\thread.hpp>
#include "MQScene.h"
#include "Constants.h"
#include "UIThreadMQ.h"
#include "StringResource.h"

namespace sgs {
    namespace scene {
         

        bool Loading::init() {
            bool bRet = false;
            do 
            {
                //////////////////////////////////////////////////////////////////////////
                // super init first
                //////////////////////////////////////////////////////////////////////////
                CC_BREAK_IF(! CCLayer::init());
                //����
                CCSprite* mainBgSprite = CCSprite::create(IMAGE_LOBBY_BG_PATH);
                CC_BREAK_IF(! mainBgSprite);

                mainBgSprite->setPosition(ccp(0,0));
                mainBgSprite->setAnchorPoint(ccp(0,0));
                this->addChild(mainBgSprite, -1);

                //loading bg
                //CCLabelBMFont* label = CCLabelBMFont::create("","",50,CCTextAlignment::kCCTextAlignmentLeft);
                //CCLabelTTF* loadLabel = CCLabelTTF::create(G2U("1�����ۣ�\n�����������ö�������˺�����\n2�����ݣ�\n��������������Ҫʹ�ã�������һ�š�����ʱ������Է������ݡ�����κ������ɫ���ж�˳������ѡ���Ƿ���һ�š��������ṩ�����㣨��Ϊ����ʹ�û�������ֱ����һ����ɫ��û���κν�ɫ���������ʱΪֹ��"), "����", 32
                //    , ::CCSize(960,640), CCTextAlignment::kCCTextAlignmentLeft);
                CCLabelTTF* loadLabel = CCLabelTTF::create("loading", "����", 32);
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                loadLabel->setPosition(ccp(winSize.width/2, 60));
                loadLabel->setColor(ccc3(255,0,0));
                this->addChild(loadLabel);
                //loadLabel->runAction(::CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.0f),CCFadeIn::create(1.0f))));

                this->loadResources();
                //boost::thread th(boost::bind(&Loading::loadResources, this));

                bRet = true;
            }while(0);
            return bRet;
        }

        void Loading::loadResources() {
            
            CCSpriteFrameCache* pFrameCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
            char plistStr[50] = {0};
            char pvrStr[50] = {0};
            for(int i = 0; i< 6 ;i++) {
                sprintf(plistStr, "image/nonalpha_%d.plist", i);
                sprintf(pvrStr, "image/nonalpha_%d.png", i); 
                pFrameCache->addSpriteFramesWithFile(plistStr, pvrStr);
            }
            
            for(int i = 0; i< 2 ;i++) {
                sprintf(plistStr, "image/alpha_%d.plist", i);
                sprintf(pvrStr, "image/alpha_%d.png", i); 
                pFrameCache->addSpriteFramesWithFile(plistStr, pvrStr);
            }

            for(int i = 0; i< 2 ;i++) {
                sprintf(plistStr, "image/image_%d.plist", i);
                sprintf(pvrStr, "image/image_%d.png", i); 
                pFrameCache->addSpriteFramesWithFile(plistStr, pvrStr);
            }
            
            ADD_MESSAGE(boost::bind(&Loading::afterLoadResources, this));
        }

        void Loading::afterLoadResources() {
            
            CCSprite* mainBgSprite = CCSprite::createWithSpriteFrameName(IMAGE_TABLE_PLAYER_BG_PATH);
            
                mainBgSprite->setPosition(CCPointZero);
                this->addChild(mainBgSprite, 1, 0);
            
            //CCDirector::sharedDirector()->replaceScene(PlayerTable::scene(8));
            CCLog("Loading::afterLoadResources");
        }

        cocos2d::CCScene* Loading::scene() {
            CCScene * scene = NULL;
            do 
            {
                // 'scene' is an autorelease object
                scene = MQScene::create();
                CC_BREAK_IF(! scene);

                // 'layer' is an autorelease object
                Loading *layer = Loading::create();
                CC_BREAK_IF(! layer);

                // add layer as a child to scene
                scene->addChild(layer);
            } while (0);

            // return the scene
            return scene;
        }

    }
}