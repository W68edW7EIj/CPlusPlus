#include "agenda.h"

namespace TIME
{

    Agenda &Agenda::operator<<(Evt &e)
    {
        evenements.push_back(&e); // 只存地址，不复制
        return *this;
    }

    void Agenda::afficher(std::ostream &f) const
    {
        f << "===== Agenda =====\n";
        for (const auto &evt : evenements)
        {
            evt->afficher(f); // 多态输出
            f << "-----------------\n";
        }
    }

} // namespace TIME