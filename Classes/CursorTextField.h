#ifndef __CURSOR_TEXT_FIELD_H__
#define __CURSOR_TEXT_FIELD_H__

#include "cocos2d.h"
#include <string>
#include  <boost/function.hpp>

using namespace std;
USING_NS_CC;

namespace sgs {
    namespace ui {

        class CursorTextField: public CCTextFieldTTF, public CCTextFieldDelegate, public CCTouchDelegate
        {
        private:
            // �����ʼλ��
            CCPoint m_beginPos;

            // ��꾫��
            CCSprite *m_pCursorSprite;

            // ��궯��
            CCAction *m_pCursorAction;

            // �������
            CCPoint m_cursorPos;

            // ���������
            std::string *m_pInputText;
            //�ߴ�
            CCSize m_fieldSize;
            CCSize contentSize;
            //ȷ������
            boost::function<void(const string&)> func_;
        public:
            CursorTextField();
            ~CursorTextField();

            string getInputText();
            // static
            static CursorTextField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, CCSize inputSize);

            // CCLayer
            void onEnter();
            void onExit();

            // ��ʼ����꾫��
            void initCursorSprite(int nHeight);

            // CCTextFieldDelegate
            virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
            virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
            virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
            virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);

            // CCLayer Touch
            bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
            void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

            // �ж��Ƿ�����TextField��
            bool isInTextField(CCTouch *pTouch);
            // �õ�TextField����
            CCRect getRect();

            // �����뷨
            void openIME();
            // �ر����뷨
            void closeIME();
            //���ûس��ص�
            void setOnEnterFunc(boost::function<void(const string&)> func);
        };

    }
}
#endif
