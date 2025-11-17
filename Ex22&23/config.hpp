#ifndef SET_CONFIG_H
#define SET_CONFIG_H

#include <cstddef> // 引入 size_t 类型定义

/**
 * ============================================================================
 * 配置文件说明 (Configuration File Documentation)
 * ============================================================================
 *
 * 设计理念：
 * 之前的代码是直接在类中使用魔法数字（如 81、3 等）来表示卡牌数量和配置。
 * 这种方式虽然直观，但存在以下问题：
 * 1. 可维护性差：修改配置需要在多处查找和替换
 * 2. 易出错：不同地方的数字可能不一致
 * 3. 可读性差：数字本身无法表达其含义
 *
 * 改进方案：
 * 使用配置文件统一管理所有常量，遵循"单一数据源"原则。
 * 优势：
 * - 集中管理：所有配置在一个地方定义
 * - 类型安全：使用 constexpr 在编译期确定值
 * - 易于扩展：添加新配置无需修改核心代码
 * - 语义清晰：常量名称表达了其用途
 *
 * 数学基础：
 * SET 游戏的卡牌总数 = 3^4 = 81
 * （4 个特征，每个特征有 3 种可能）
 */

namespace config
{
    // ========================================================================
    // 游戏核心配置 (Game Core Configuration)
    // ========================================================================

    /**
     * NB_CARTES: 游戏中卡牌的总数
     * 计算公式: NB_COULEURS × NB_NOMBRES × NB_FORMES × NB_REMPLISSAGES
     *          = 3 × 3 × 3 × 3 = 81
     * 这是 SET 游戏的固定规则，每张卡牌都是唯一的
     */
    constexpr size_t NB_CARTES = 81;

    /**
     * NB_COULEURS: 卡牌颜色的种类数
     * 可选值：rouge (红), mauve (紫), vert (绿)
     */
    constexpr size_t NB_COULEURS = 3;

    /**
     * NB_NOMBRES: 卡牌上符号的数量种类
     * 可选值：1, 2, 3
     */
    constexpr size_t NB_NOMBRES = 3;

    /**
     * NB_FORMES: 卡牌符号的形状种类数
     * 可选值：ovale (椭圆), vague (波浪), losange (菱形)
     */
    constexpr size_t NB_FORMES = 3;

    /**
     * NB_REMPLISSAGES: 卡牌符号的填充方式种类数
     * 可选值：plein (实心), vide (空心), hachure (阴影)
     */
    constexpr size_t NB_REMPLISSAGES = 3;

    // ========================================================================
    // 游戏规则配置 (Game Rules Configuration)
    // ========================================================================

    /**
     * PLATEAU_MIN_CARTES: 游戏桌面上最少应保持的卡牌数
     * 根据 SET 游戏规则，正常情况下桌面应有 12 张卡牌
     */
    constexpr size_t PLATEAU_MIN_CARTES = 12;

    /**
     * PLATEAU_INITIAL_CAPACITY: Plateau 动态数组的初始容量
     * 避免频繁扩容，提高性能
     */
    constexpr size_t PLATEAU_INITIAL_CAPACITY = 5;

    /**
     * PLATEAU_INCREMENT: Plateau 扩容时每次增加的容量
     * 当数组满时，以此值为增量进行扩容
     */
    constexpr size_t PLATEAU_INCREMENT = 5;

    // ========================================================================
    // 显示配置 (Display Configuration)
    // ========================================================================

    /**
     * PLATEAU_CARTES_PER_LINE: 打印 Plateau 时每行显示的卡牌数
     * 用于格式化输出，让显示更整齐
     */
    constexpr size_t PLATEAU_CARTES_PER_LINE = 3;
}

#endif // SET_CONFIG_H