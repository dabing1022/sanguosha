#ifndef __CARD_ITEM_H__
#define __CARD_ITEM_H__

#include <cocos2d.h>
#include <boost\smart_ptr.hpp>
#include "Card.h"
#include "CCTouchNode.h"

using namespace cocos2d;
using namespace sgs::core;

namespace sgs {
    namespace ui {

        /**
        * @brief չʾ����
        **/
        class CardItem : public CCTouchNode
        {
        public:
            CardItem(boost::shared_ptr<Card> cardPtr);
            ~CardItem(void);
            bool init();
            static CardItem* create(boost::shared_ptr<Card> cardPtr =  boost::shared_ptr<Card>());
            void touch();

            //ѡ��
            void select();
            //ȡ��ѡ��
            void unselect();
            //��ʧ
            void fadeOut();

            void clearup();
            
            boost::shared_ptr<Card> getCardPtr();

        private:
            boost::shared_ptr<Card> cardPtr_;
            bool selected_;
        };

    }
}
#endif