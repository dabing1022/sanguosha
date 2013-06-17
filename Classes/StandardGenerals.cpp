#include "General.h"
#include "Standard.h"

#include <boost\smart_ptr.hpp>

using namespace sgs::core;

namespace sgs {
namespace package {
    
    
    void StandardPackage::addGenerals() {
        //κ
        //�ܲ�
        boost::shared_ptr<General> caocao(new General(shared_from_this(), "caocao$", "wei"));
        caocao->addSkill(boost::shared_ptr<Skill>(new Skill("jianxiong")));
        caocao->addSkill(boost::shared_ptr<Skill>(new Skill("hujia")));
        generals_.push_back(caocao);

        //����
        boost::shared_ptr<General> zhangliao(new General(shared_from_this(), "zhangliao", "wei"));
        generals_.push_back(zhangliao);

        //����
        boost::shared_ptr<General> guojia(new General(shared_from_this(), "guojia", "wei", 3));
        generals_.push_back(guojia);

        //�ĺ
        boost::shared_ptr<General> xiahoudun(new General(shared_from_this(), "xiahoudun", "wei"));
        generals_.push_back(xiahoudun);
        
        //˾��ܲ
        boost::shared_ptr<General> simayi(new General(shared_from_this(), "simayi", "wei", 3));
        generals_.push_back(simayi);

        //����
        boost::shared_ptr<General> xuchu(new General(shared_from_this(), "xuchu", "wei"));
        generals_.push_back(xuchu);

        //�缧
        boost::shared_ptr<General> zhenji(new General(shared_from_this(), "zhenji", "wei", 3 , General::Female));
        generals_.push_back(zhenji);

        //��
        //����
        boost::shared_ptr<General> liubei(new General(shared_from_this(), "liubei$", "shu"));
        liubei->addSkill(boost::shared_ptr<Skill>(new Skill("rende")));
        liubei->addSkill(boost::shared_ptr<Skill>(new Skill("jijiang")));
        generals_.push_back(liubei);

        //���� *zhaoyun, *machao, *zhugeliang, *huangyueying;
        boost::shared_ptr<General> guanyu(new General(shared_from_this(), "guanyu", "shu"));
        generals_.push_back(guanyu);

        //�ŷ�
        boost::shared_ptr<General> zhangfei(new General(shared_from_this(), "zhangfei", "shu"));
        generals_.push_back(zhangfei);

        //����
        boost::shared_ptr<General> zhaoyun(new General(shared_from_this(), "zhaoyun", "shu"));
        generals_.push_back(zhaoyun);

        //��
        boost::shared_ptr<General> machao(new General(shared_from_this(), "machao", "shu"));
        generals_.push_back(machao);

        //�����
        boost::shared_ptr<General> zhugeliang(new General(shared_from_this(), "zhugeliang", "shu", 3));
        generals_.push_back(zhugeliang);

        //����Ӣ
        boost::shared_ptr<General> huangyueying(new General(shared_from_this(), "huangyueying", "shu", 3, General::Female));
        generals_.push_back(huangyueying);

        //��
        //��Ȩ
        boost::shared_ptr<General> sunquan(new General(shared_from_this(), "sunquan$", "wu"));
        sunquan->addSkill(boost::shared_ptr<Skill>(new Skill("zhiheng")));
        sunquan->addSkill(boost::shared_ptr<Skill>(new Skill("jiuyuan")));
        generals_.push_back(sunquan);

        //���
        boost::shared_ptr<General> zhouyu(new General(shared_from_this(), "zhouyu", "wu", 3));
        generals_.push_back(zhouyu);

        //����
        boost::shared_ptr<General> lvmeng(new General(shared_from_this(), "lvmeng", "wu"));
        generals_.push_back(lvmeng);

        //½ѷ
        boost::shared_ptr<General> luxun(new General(shared_from_this(), "luxun", "wu", 3));
        generals_.push_back(luxun);

        //����
        boost::shared_ptr<General> ganning(new General(shared_from_this(), "ganning", "wu"));
        generals_.push_back(ganning);

        //�Ƹ�
        boost::shared_ptr<General> huanggai(new General(shared_from_this(), "huanggai", "wu"));
        generals_.push_back(huanggai);

        //����
        boost::shared_ptr<General> daqiao(new General(shared_from_this(), "daqiao", "wu", 3, General::Female));
        generals_.push_back(daqiao);

        //������
        boost::shared_ptr<General> sunshangxiang(new General(shared_from_this(), "sunshangxiang", "wu", 3, General::Female));
        generals_.push_back(sunshangxiang);

        //Ⱥ
        //����
        boost::shared_ptr<General> lvbu(new General(shared_from_this(), "lvbu", "qun"));
        generals_.push_back(lvbu);
        //��٢
        boost::shared_ptr<General> huatuo(new General(shared_from_this(), "huatuo", "qun", 3));
        generals_.push_back(huatuo);
        //����
        boost::shared_ptr<General> diaochan(new General(shared_from_this(), "diaochan", "qun", 3, General::Female));
        generals_.push_back(diaochan);
    }

}
}
