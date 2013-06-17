#ifndef __ANIMATION_MANAGER_H__
#define __ANIMATION_MANAGER_H__

#include <cocos2d.h>
#include <string>

using namespace std;
using namespace cocos2d;

namespace sgs {
    namespace manager {

        class AnimationManager
        {
        public:
            ~AnimationManager(void);
            static AnimationManager* getInstance();
            /**
            * @��ȡ����
            **/
            //CCAnimation* getAnimation(const string& key);
            /**
            * @��ȡɱ����
            **/
            CCAnimation* getSlashAnimation();
            /**
            * @��ȡ������
            **/
            CCAnimation* getJinkAnimation();
            /**
            * @��ȡ�Ҷ���
            **/
            CCAnimation* getPeachAnimation();
            /**
            * @��ȡ�˺�����
            **/
            CCAnimation* getDamageAnimation();

        private:
            static AnimationManager* instance_;
            AnimationManager(void);
            /**
            * @��������
            **/
            CCAnimation* createAnimation(const int& count,const char* formatStr, float unit);
        private:
            bool init_;
        };

    }
}

#endif