#include "agenda.h"

namespace TIME
{

    Agenda &Agenda::operator<<(Evt1j &e)
    {
        evenements.push_back(&e); // 只存地址
        /*
        agenda不拥有事件
            不new, 不delete

        Agenda和事件的 UML 关系是聚合：
            - Agenda 引用事件
            - 但不负责创建 / 销毁
            - 事件可以独立存在
        Agenda ◇────────── Evt1j
                (aggregation)
        */
        return *this;
    }

    void Agenda::afficher(std::ostream &f) const
    {
        f << "===== Agenda =====\n";
        for (const auto &evt : evenements)
        {
            evt->afficher(f); // ★ 多态调用
            f << "-----------------\n";
        }
    }

} // namespace TIME