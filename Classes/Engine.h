#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <boost\smart_ptr.hpp>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "Skill.h"
#include "Package.h"

using namespace std;
using namespace sgs::package;
using namespace boost;

namespace sgs {
namespace core {
    /**
    * @brief ������, ����
    **/
    class Engine
    {
    public:
        static Engine* getInstance();
        ~Engine(void);
    public:
        /**
        * @brief ��ȡ����
        * @param string ��������
        * @return boost::shared_ptr<Skill> ����
        **/
        const boost::shared_ptr<Skill> getSkill(const string &skillName) const;
        /**
        * @brief ��Ӽ���
        * @param vector<boost::shared_ptr<Skill> > �����б�
        * @return void
        **/
        void addSkills( vector< boost::shared_ptr<Skill> > &skills);
        /**
        * @brief ��ȡ��������
        * @param string ��������
        * @return boost::shared_ptr<Skill> ����
        **/
        const boost::shared_ptr<TriggerSkill> getTriggerSkill(const string &skillName) const;
        
        /**
        * @brief ��Ӵ�������
        * @param vector<boost::shared_ptr<Skill> > �����б�
        * @return void
        **/
        void addTriggerSkills(const vector<boost::shared_ptr<TriggerSkill> > &skills);

         /**
        * @brief ��Ӱ�
        * @param boost::shared_ptr<Package> package ��
        * @return void
        **/
        void addPackage(boost::shared_ptr<Package> package);

         /**
        * @brief ��Ӱ�
        * @param const string &name
        * @return void
        **/
        void addPackage(const string &name);

         /**
        * @brief ��ȡ����佫
        * @param int count ����
        * @param const set<string> &ban_set �ѱ�ѡ�佫
        * @return void
        **/
        vector<string> getRandomGenerals(int count, const set<string> &banSet = set<string>()) const;

        /**
        * @brief ��ȡ�佫ʵ��
        **/
        boost::shared_ptr<General> getGeneral(const string& name);
        
        /**
        * @brief ��ȡ�佫ʵ���б�
        **/
        vector<boost::shared_ptr<General> > getGeneral(const vector<string> names);

        /**
        * @brief ��ȡ��Ƭ����
        **/
        int getCardCount() const;

        /**
        * @brief ��ȡ��Ƭʵ��
        **/
        boost::shared_ptr<Card> getCard(int cardId);
        vector<boost::shared_ptr<Card> > getCards(vector<int> cardIds);
        set<boost::shared_ptr<Card> > getCards(set<int> cardIds);

        /**
        * @brief ��ȡ��ȡ���п�Ƭid
        **/
        vector<int> getAllCardsId();
        /**
        * @brief ��ȡ��ȡ���п�Ƭʵ��
        **/
        vector<boost::shared_ptr<Card> > getAllCardsEntity();

    private:
        Engine(void);
    private:
        //Ψһʵ��
        static Engine* instance;
        //���ܱ�
        map<string, const boost::shared_ptr<Skill> > skills_; 
        //�������ܱ�
        map<string, const boost::shared_ptr<TriggerSkill> > triggerSkills_;
        //�佫��
        map<string, const boost::shared_ptr<General> > generals_;
        //����
        CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<string> ,lordList_ , LordList);
        //������
        CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<string> ,nonlordList_ , NonLordList);

        //��Ƭ��
        map<int, const boost::shared_ptr<Card> > cards_; 
        CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<int> ,cardList_ , CardList);
        //vector<string> lordList_, nonlordList_;
    };

}
}
#endif