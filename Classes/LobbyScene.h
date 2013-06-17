#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__


#include "AsioClient.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <boost\smart_ptr.hpp>
#include "Macros.h"

#include "SgsClient.h"

using namespace cocos2d;
using namespace sgs::net;
using namespace cocos2d::extension;

namespace sgs {
    namespace scene {
        /**
        * @brief �û�����
        **/
        class LobbyBoardUser :public cocos2d::CCNode {
        public:
            LobbyBoardUser();
            ~LobbyBoardUser();
            virtual bool init();
            CREATE_FUNC(LobbyBoardUser);
        };

        /**
        * @brief �û����
        **/
        class LobbyBoardInfo : public cocos2d::CCNode {
        public:
            LobbyBoardInfo();
            ~LobbyBoardInfo();
            virtual bool init();
            CREATE_FUNC(LobbyBoardInfo);
            void createTouchDownAction(CCObject* pSender, CCControlEvent event) ;
            void backTouchDownAction(CCObject* pSender, CCControlEvent event);
        };

        /**
        * @brief ������Ԫ
        **/
        class LobbyTableCell : public cocos2d::extension::CCTableViewCell {
        public:
            LobbyTableCell(const CCSize& size);
            ~LobbyTableCell();
            bool init();
            static LobbyTableCell * create(const CCSize& size);
            void select();
            void unselect();
            bool isSelect();
            void setRoomName(const string& name);
            CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(selectable_, Selectable);
            CC_SYNTHESIZE_PASS_BY_REF(string, ip_ , Ip);
        private:
            CCSize cellSize_;
            //�Ƿ�ѡ��
            bool selected_;
            CCSprite* selectBg_;
            CCSprite* unselectBg_;
            CCLabelTTF * lable_;
        };


        /**
        * @brief ����
        **/
        class Lobby : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
        {
        public:
            Lobby();
            ~Lobby();
            // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
            virtual bool init();  

            // there's no 'id' in cpp, so we recommand to return the exactly class pointer
            static cocos2d::CCScene* scene();

            // implement the "static node()" method manually
            CREATE_FUNC(Lobby);
            virtual void onEnter ();
            virtual void onExit ();

            void addRoom(const string& name, const string& ip);

            /**
            * @brief ��֤ͨ���ص�
            **/
            void authSuccessCallback();

            /**
            * @brief �����ص�����������ֱ�ӵ���UIThread�ӿ�
            **/
            void seacherCallback(const sgs::net::IpAndNameStruct&);

            //ScrolView
            virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
            virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
            //from CCTableViewDelegate
            virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
            //CCTableViewDataSource
            virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
            virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
            virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

        private:
            //table�ߴ�
            CCSize cellSize_;
            //��󷿼���
            int maxCount_;
            //����������
            boost::shared_ptr<UdpSearcher> seacherPtr_;
            cocos2d::extension::CCTableView* tableView_;
            vector<LobbyTableCell *> cellVector_;
            boost::shared_ptr<sgs::client::SgsClient> client_;
        };

    }
}
#endif  // __HELLOWORLD_SCENE_H__