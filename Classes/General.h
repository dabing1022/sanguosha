#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <cocos2d.h>
#include <boost\smart_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>
#include <string>
#include <vector>
#include <set>
#include "Macros.h"

using namespace std;
using namespace cocos2d;

namespace sgs {
namespace package {
    class Package;
};
};
using namespace sgs::package;

namespace sgs {
namespace core {
    class Skill;
    class TriggerSkill;
    /**
    * @brief �佫��
    **/
    class General: public boost::enable_shared_from_this<General>
    {
    private:
        static CCDictionary * GENERAL_STRINGS;
    public:
        //�Ա�ö��
        enum Gender {SexLess, Male, Female, Neuter};
        //������
        CC_SYNTHESIZE_PASS_BY_REF(boost::shared_ptr<Package>, packagePtr_, PackagePtr);
        //����
        CC_SYNTHESIZE_PASS_BY_REF(string, name_, Name);
        //����
        CC_SYNTHESIZE_PASS_BY_REF(string, kingdom_, Kingdom);
        //��Ѫ��
        CC_SYNTHESIZE(int, maxHp_, MaxHp);
        //�Ա�
        CC_SYNTHESIZE(Gender, gender_, Gender);
        //�Ƿ����أ��������ﲻ��ѡ��
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(hidden_, Hidden);
        //�Ƿ�Ϊ����
        CC_SYNTHESIZE_PASS_BY_REF_FOR_BOOL(lord_, Lord);
        /**
        * @brief ���캯��
        * @param Package ������
        * @param string name �佫��
        * @param string kingdom ������
        * @param maxHp ���Ѫ��
        * @param male �Ա�
        * @param hidden �Ƿ�����
        * @param neverShown 
        **/
        explicit General(boost::shared_ptr<Package> packagePtr, const string &name, const string &kingdom, int max_hp = 4, Gender male = Male, bool hidden = false, bool never_shown = false);
        /**
        * @brief ��������
        */
        ~General(void);

        
        string getChineseName() const;
        /**
        * @brief ��Ӽ��� �����ڵ�һ����ӣ�����������Ĺ���
        * @param Skill ����
        * @return void
        */
        void addSkill(boost::shared_ptr<Skill> skillPtr);
        /**
        * @brief ��Ӽ��������ڷǵ�һ����ӣ����罪ά�Ĺ���
        * @param string ��������
        * @return void
        */
        void addExtraSkill(boost::shared_ptr<Skill> skillPtr);

        /**
        * @brief �Ƿ�ӵ�м���
        * @param string ��������
        * @return bool
        */
        bool hasSkill(const string &skill_name) const;

        string getSkillDescription();
        /**
        * @brief ��ȡ�����б�
        * @return vector<const boost::shared_ptr<Skill>> �����б�
        */
        vector<boost::shared_ptr<Skill> > getSkillList() const;
        /**
        * @brief ��ȡ�ɼ��ļ����б�
        * @return vector<const boost::shared_ptr<Skill>> �����б�
        */
        vector<boost::shared_ptr<Skill> > getVisibleSkillList() const;
         /**
        * @brief ��ȡ�ɼ��ļ��ܼ���
        * @return vector<const boost::shared_ptr<Skill>> �����б�
        */
        set<boost::shared_ptr<Skill> > getVisibleSkills() const;
         /**
        * @brief ��ȡ���������б����ǡ��ɼ��ȣ�
        * @return vector<const boost::shared_ptr<Skill>> �����б�
        */
        set<boost::shared_ptr<TriggerSkill> > getTriggerSkills() const;
        /**
        * @brief �Ƿ�Ϊ����
        * @return bool
        */
        bool isMale();
        /**
        * @brief �Ƿ�ΪŮ��
        * @return bool
        */
        bool isFeMale();
    private:
        //���ܼ���
        set<boost::shared_ptr<Skill> > skillSet_;
        //���ܼ���
        set<string> skillNameSet_;
        //��չ���ܼ���
        set<string> extraNameSet_;
        set<boost::shared_ptr<Skill> > extraSet_;
    };

};
};

#endif
