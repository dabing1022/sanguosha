#ifndef __CARD_SELECTOR_H__
#define __CARD_SELECTOR_H__

#include <cocos2d.h>
#include "CardItem.h"

using namespace cocos2d;
using namespace sgs::ui;

namespace sgs {
    namespace selector {

        /**
        * ��Ƭѡ����
        **/
        class CardSelector
        {
        public:

            CardSelector(void);
            ~CardSelector(void);

            void selecteCard(CardItem* cardPtr);
            void unselecteCard(CardItem* cardPtr);

            //����ѡ������
            void setSelectCount(const int count);
            //��ȡѡ��Ŀ�Ƭ
            CCArray* getSelectedCards();

            //����ѡ��Ľ���������κο�Ƭ��ز�����ֻ���ѡ����
            void clear();

        private:
            int selectCount_;
            CCArray* cardArray_;
        };

    }
}

#endif