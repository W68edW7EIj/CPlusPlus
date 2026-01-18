#include "evenement.h"

namespace TIME
{

    bool operator<(const Evt1j &a, const Evt1j &b)
    {
        // 1) 先比日期
        if (a.getDate() < b.getDate())
            return true;
        if (b.getDate() < a.getDate())
            return false;

        // 2) 同一天：尝试 down-cast 看有没有时间（Evt1jDur 或 Rdv）
        const Evt1jDur *ad = dynamic_cast<const Evt1jDur *>(&a);
        const Evt1jDur *bd = dynamic_cast<const Evt1jDur *>(&b);

        // 规则：没有时间的事件排在有时间的之前（你也可以反过来）
        if (!ad && bd)
            return true;
        if (ad && !bd)
            return false;

        // 两者都没时间：认为不小于（相等意义）
        if (!ad && !bd)
            return false;

        // 两者都有时间：按 horaire 排序
        return ad->getHoraire() < bd->getHoraire();
    }

} // namespace TIME