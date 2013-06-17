#ifndef __CHOSE_GENERAL_LAYER_H__
#define __CHOSE_GENERAL_LAYER_H__

#include <cocos2d.h>
#include <boost\smart_ptr.hpp>
#include <boost\function.hpp>
#include "General.h"
#include "CCTouchNode.h"

using namespace cocos2d;
using namespace sgs::core;
using namespace sgs::ui;

namespace sgs {
    namespace layer {

        /**
        * �佫��ui
        **/
        class GeneralItem : public CCTouchNode {
        public:
            GeneralItem(boost::shared_ptr<General> general, bool disable = false);
            virtual bool init();
            
            static GeneralItem* create(boost::shared_ptr<General> general ,bool disable = false);

            virtual void touch();
            bool isDisable();
            void unselect();
        private:
            boost::shared_ptr<General> general_;
            bool disable_;
            static const int CARD_TAG = 1;
            static const int CARD_SELECT_ACTION_TAG = 2;
        };

        class GeneralDetailBoard : public CCNode {
        public:
            virtual bool init();
            CREATE_FUNC(GeneralDetailBoard);
            void setString(const string& detail);
        private:
            static const int TEXT_TAG = 1;
        };
        //
        class ChooseGeneralLayer:public CCLayerColor
        {
        public:
            ChooseGeneralLayer(void);
            ~ChooseGeneralLayer(void);
            virtual bool init(const char* title);
            //
            virtual void onEnter();
            virtual void onExit();
            virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
            //�ر�ѡ��̨
            virtual void closeChoseLayer();
            //��ʾ�佫����
            virtual void showGeneralDetail(boost::shared_ptr<General> generalPtr);
            //ѡ���佫
            virtual void selectGeneral(GeneralItem* generalItem, boost::shared_ptr<General> generalPtr);
            //����ѡ��ص�
            void setSelectCallback(boost::function<void(boost::shared_ptr<General>)> callback);
        private:
            boost::shared_ptr<General> generalPtr_;
            boost::function<void(boost::shared_ptr<General>)> callbackFunc_;
            GeneralItem * currentGeneralItem_;
            static const int DETAIL_BOARD_TAG = 1;
        };

        //����ѡ��
        class ChooseLordLayer : public ChooseGeneralLayer {
        public:
            virtual bool init(vector<boost::shared_ptr<General> > generals);
            static ChooseLordLayer* create(vector<boost::shared_ptr<General> > generals);
        private:
            
        };
        
        //������ѡ��
        class ChooseOtherLayer : public ChooseGeneralLayer {
        public:
            virtual bool init(boost::shared_ptr<General> lord, vector<boost::shared_ptr<General> > generals);
            
            static ChooseOtherLayer* create(boost::shared_ptr<General> lord, vector<boost::shared_ptr<General> > generals);
        }; 
    }
}

#endif