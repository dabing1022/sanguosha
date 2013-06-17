#ifndef __PLAYER_UI_H__
#define __PLAYER_UI_H__

#include "ClientPlayer.h"


using namespace sgs::client;

namespace sgs {
    namespace ui {

        class PlayerUI
        {
        public:
            PlayerUI(void);
            ~PlayerUI(void);

            virtual void showTimeBar(float time) = 0;
            virtual void hiddenTimeBar() = 0;

            virtual void drawCard(vector<boost::shared_ptr<Card> > cards) = 0;
            virtual void discardCards(set<boost::shared_ptr<Card> > cards) = 0;
            virtual void setPlayer(boost::shared_ptr<ClientPlayer> player);
            virtual void setRole(Player::Role role) = 0;
            
            virtual void setPhase(Player::Phase phase) = 0;

        protected:
            boost::shared_ptr<ClientPlayer> player_;
        };

         /**
        * @brief �׶ζ�����
        */
        class PhaseAnimationArea : public CCNode {
        public:
            PhaseAnimationArea();
            ~PhaseAnimationArea();
            bool init();
            CREATE_FUNC(PhaseAnimationArea);
            /**
            * @brief �����ж��׶�
            */
            void showJudgeAnimation();
            /**
            * @brief ����ץ�ƽ׶�
            */
            void showDrawAnimation();
            /**
            * @brief ���ŷ��ƽ׶�
            */
            void showPlayAnimation();
            /**
            * @brief �������ƽ׶�
            */
            void showDiscardAnimation();
            /**
            * @brief ���ŻغϽ���
            */
            void showFinishAnimation();

            void showAnimation(Player::Phase phase);
        private:
            void showAnimation(CCSprite* sprite);
            CCSprite * judgeSpritePtr_;
            CCSprite * drawSpritePtr_;
            CCSprite * playSpritePtr_;
            CCSprite * discardSpritePtr_;
            CCSprite * finishSpritePtr_;
        };


         /**
        * @brief ��Ҽ�ʱ��
        **/
        class PlayerTimeBar : public CCNode {
        public:
            PlayerTimeBar();
            ~PlayerTimeBar();
            bool init();
            CREATE_FUNC(PlayerTimeBar);
            void showAnimation(float time);
            void cancelAnimation();
            void hidden();
        };


    }
}

#endif