/**
 * ============================================================================
 * SET 游戏实现文件 (SET Game Implementation)
 * ============================================================================
 *
 * 本文件包含 set.h 中声明的所有类和函数的实现。
 *
 * 主要内容：
 * 1. 枚举值列表的定义
 * 2. 枚举类型的转换和输出函数
 * 3. Carte、Jeu、Pioche、Plateau 等类的方法实现
 * 4. SET 判断逻辑的实现
 */

#include "set.h"
#include <cstdlib> // 提供 rand() 函数用于随机抽牌

namespace Set
{
	// ========================================================================
	// 全局常量列表定义 (Global Constant Lists Definition)
	// ========================================================================

	/**
	 * 特征值列表：定义每个特征的所有可能值
	 *
	 * 使用 initializer_list 的好处：
	 * - 可以在 range-based for 循环中遍历
	 * - 类型安全，编译期检查
	 * - 常量存储，不可修改
	 *
	 * 这些列表用于：
	 * 1. 生成所有 81 张卡牌（4 层嵌套循环）
	 * 2. 打印所有可能的特征值
	 * 3. 测试和验证
	 */
	std::initializer_list<Couleur> Couleurs = {Couleur::rouge, Couleur::mauve, Couleur::vert};
	std::initializer_list<Nombre> Nombres = {Nombre::un, Nombre::deux, Nombre::trois};
	std::initializer_list<Forme> Formes = {Forme::ovale, Forme::vague, Forme::losange};
	std::initializer_list<Remplissage> Remplissages = {Remplissage::plein, Remplissage::vide, Remplissage::hachure};

	string toString(Couleur c)
	{
		switch (c)
		{
		case Couleur::rouge:
			return "R";
		case Couleur::mauve:
			return "M";
		case Couleur::vert:
			return "V";
		default:
			throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v)
	{
		switch (v)
		{
		case Nombre::un:
			return "1";
		case Nombre::deux:
			return "2";
		case Nombre::trois:
			return "3";
		default:
			throw SetException("Nombre inconnue");
		}
	}

	string toString(Forme f)
	{
		switch (f)
		{
		case Forme::ovale:
			return "O";
		case Forme::vague:
			return "~";
		case Forme::losange:
			return "\004";
		default:
			throw SetException("Forme inconnue");
		}
	}

	string toString(Remplissage r)
	{
		switch (r)
		{
		case Remplissage::plein:
			return "P";
		case Remplissage::vide:
			return "_";
		case Remplissage::hachure:
			return "H";
		default:
			throw SetException("Remplissage inconnu");
		}
	}

	std::ostream &operator<<(std::ostream &f, Couleur c)
	{
		f << toString(c);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Nombre v)
	{
		f << toString(v);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Forme x)
	{
		f << toString(x);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Remplissage r)
	{
		f << toString(r);
		return f;
	}

	void printCouleurs(std::ostream &f)
	{
		for (auto c : Couleurs)
			f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream &f)
	{
		for (auto v : Nombres)
			f << v << " ";
		f << "\n";
	}

	void printFormes(std::ostream &f)
	{
		for (auto x : Formes)
			f << x << " ";
		f << "\n";
	}

	void printRemplissages(std::ostream &f)
	{
		for (auto r : Remplissages)
			f << r << " ";
		f << "\n";
	}

	ostream &operator<<(ostream &f, const Carte &c)
	{
		f << "[" << c.getCouleur() << c.getForme()
		  << c.getNombre() << c.getRemplissage() << "]";
		return f;
	}

	Jeu::Jeu()
	{
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto n : Nombres)
				for (auto f : Formes)
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, n, f, r);
	}

	const Carte &Jeu::getCarte(size_t i) const
	{
		if (i >= 81)
			throw SetException("carte iexistante");
		return *cartes[i];
	}

	Jeu::~Jeu()
	{
		for (size_t i = 0; i < 81; i++)
			delete cartes[i];
	}

	const Carte &Pioche::piocher()
	{ // get a random carte from the pioche
		// test if the pioche is not empty
		if (estVide())
			throw SetException("empty pioche");
		// choose a carte
		size_t i = rand() % nb; // get a random number between 0 and nb
		const Carte *chosenCarte = cartes[i];
		// remove the card from the array
		cartes[i] = cartes[nb - 1]; // replace carte i by the last carte of the pioche
		nb--;
		return *chosenCarte; // returns a reference over the chosen carte
	}

	/**
	 * 向游戏台添加一张卡牌 (Add a card to the plateau)
	 *
	 * @param c 要添加的卡牌的常量引用
	 *
	 * 实现要点：
	 * 1. 动态扩容机制
	 *    - 当数组满时，自动扩容（增加 5 个位置）
	 *    - 将旧数组内容复制到新数组
	 *    - 释放旧数组内存
	 *
	 * 2. 为什么存储指针而不是对象？
	 *    - 卡牌对象由 Jeu 类管理（81 张固定卡牌）
	 *    - 避免重复创建和销毁卡牌对象
	 *    - 节省内存，提高性能
	 *
	 * 3. 扩容步长为什么是 5？
	 *    - 平衡内存使用和分配次数
	 *    - SET 游戏通常每次添加 3 张牌
	 *    - 5 是合理的小步长
	 */
	void Plateau::ajouter(const Carte &c)
	{
		// 检查数组是否已满
		if (nb == nbMax)
		{
			// 数组所有位置都已使用，需要扩容

			// 创建一个更大的数组（增加 5 个位置）
			const Carte **newarray = new const Carte *[nbMax + 5];

			// 将所有卡牌的地址复制到新数组
			for (size_t i = 0; i < nb; i++)
				newarray[i] = cartes[i];

			// 保存旧数组的指针以便后续释放
			const Carte **old = cartes;

			// 将新数组设置为当前使用的数组
			cartes = newarray;

			// 更新最大容量
			nbMax += 5;

			// 释放旧数组的内存（注意：只释放数组本身，不释放卡牌对象）
			delete[] old;
		}

		// 现在可以确定有足够的空间来存储更多卡牌
		// 将新卡牌的地址存储到数组末尾
		cartes[nb] = &c;

		// 增加已存储卡牌的数量
		nb++;
	}

	/**
	 * 从游戏台移除一张卡牌 (Remove a card from the plateau)
	 *
	 * @param c 要移除的卡牌的常量引用
	 * @throws SetException 如果卡牌不存在于游戏台
	 *
	 * 实现策略：
	 * 1. 线性搜索要移除的卡牌（比较指针地址）
	 * 2. 用最后一张卡牌替换要移除的卡牌（避免移动大量元素）
	 * 3. 减少卡牌计数
	 *
	 * 时间复杂度：O(n) - 需要搜索卡牌
	 * 优点：移除操作本身是 O(1)
	 * 缺点：不保持卡牌顺序（但 SET 游戏不需要保持顺序）
	 */
	void Plateau::retirer(const Carte &c)
	{
		// 在数组中搜索要移除的卡牌
		size_t i = 0;
		while (i < nb && cartes[i] != &c) // 比较指针地址
			i++;

		// 如果遍历完整个数组都没找到，说明卡牌不存在
		if (i == nb)
			throw SetException("this card does not exist");

		// 用最后一张卡牌替换要移除的卡牌（高效的移除方法）
		cartes[i] = cartes[nb - 1];

		// 减少卡牌计数（原来的最后一张卡牌现在不再有效）
		nb--;
	}

	/**
	 * 拷贝构造函数 (Copy Constructor)
	 *
	 * @param p 要拷贝的源 Plateau 对象
	 *
	 * 为什么需要自定义拷贝构造函数？
	 * =====================================
	 * 如果使用默认拷贝构造函数（编译器自动生成）：
	 * - 会执行浅拷贝：只复制指针 cartes 的值
	 * - 结果：两个 Plateau 对象的 cartes 指向同一个数组
	 * - 问题：修改一个对象会影响另一个对象
	 * - 更严重：析构时会导致双重释放（double free）错误
	 *
	 * 深拷贝实现：
	 * ===========
	 * 1. 为新对象分配独立的数组
	 * 2. 复制所有卡牌指针（注意：复制的是指针，不是卡牌对象）
	 * 3. 复制容量和大小信息
	 *
	 * 结果：每个 Plateau 有自己的数组，但指向相同的卡牌对象
	 */
	Plateau::Plateau(const Plateau &p)
	{
		// 为新 Plateau 分配独立的数组（深拷贝）
		cartes = new const Carte *[p.nbMax];

		// 复制源对象的容量和大小信息
		nb = p.nb;
		nbMax = p.nbMax;

		// 复制所有卡牌指针
		for (size_t i = 0; i < p.nb; i++)
			cartes[i] = p.cartes[i];

		// 现在每个 Plateau 都有自己的数组，但包含相同的卡牌
	}

	/**
	 * 赋值运算符重载 (Assignment Operator)
	 *
	 * @param p 要赋值的源 Plateau 对象
	 * @return 返回当前对象的引用（支持链式赋值）
	 *
	 * 实现要点：
	 * =========
	 * 1. 自赋值检查：if (this != &p)
	 *    - 防止 a = a 这样的操作导致问题
	 *    - 提高性能（避免不必要的操作）
	 *
	 * 2. 赋值策略：
	 *    - 清空当前 Plateau（设置 nb = 0）
	 *    - 保留现有数组容量（避免重新分配）
	 *    - 使用 ajouter() 逐个添加卡牌
	 *    - ajouter() 会在需要时自动扩容
	 *
	 * 3. 为什么不直接复制数组？
	 *    - 利用现有的 ajouter() 逻辑
	 *    - 自动处理扩容
	 *    - 代码复用，减少错误
	 *
	 * 4. 返回 *this 的作用：
	 *    - 支持链式赋值：a = b = c
	 *    - 符合 C++ 赋值运算符的惯例
	 */
	Plateau &Plateau::operator=(const Plateau &p)
	{
		// 检查是否为自赋值（a = a）
		if (this != &p)
		{
			// 注意：此时 *this 和 p 都有各自的数组

			// 清空当前数组（但保留容量）
			nb = 0;
			// 我们认为数组中不再有卡牌
			// 但保留数组的容量，可以继续存储新的指针

			// 从源对象复制所有卡牌
			for (size_t i = 0; i < p.nb; i++)
				ajouter(*p.cartes[i]); // 添加 p 中的每张卡牌
									   // 如果需要，ajouter 会自动扩容
		}

		// 返回当前对象的引用（支持链式赋值）
		return *this;
	}

	/**
	 * 判断三张卡牌是否构成一个 SET (Check if three cards form a SET)
	 *
	 * @return true 如果三张卡牌构成 SET，false 否则
	 *
	 * SET 游戏规则：
	 * =============
	 * 三张卡牌构成一个 SET 当且仅当：
	 * 对于每个特征（颜色、形状、数量、填充），这三张卡牌要么：
	 * - 完全相同（3 张都一样）
	 * - 完全不同（3 张都不一样）
	 *
	 * 示例：
	 * ------
	 * ✓ 合法 SET：[R◇1P] [M◇2P] [V◇3P]
	 *   - 颜色：R, M, V（全不同）✓
	 *   - 形状：◇, ◇, ◇（全相同）✓
	 *   - 数量：1, 2, 3（全不同）✓
	 *   - 填充：P, P, P（全相同）✓
	 *
	 * ✗ 非法组合：[R◇1P] [R◇2P] [V◇3P]
	 *   - 颜色：R, R, V（两同一异）✗
	 *
	 * 实现逻辑：
	 * =========
	 * 对于每个特征，检查：
	 * - 条件1：c1 == c2 && c1 == c3  （全相同）
	 * - 条件2：c1 != c2 && c1 != c3 && c2 != c3  （全不同）
	 *
	 * 原先代码中好像最后一个写错了
	 * 当前条件2写的是：c1 != c2 && c1 != c3 && c2 == c3
	 * 这实际上允许"两同一异"的情况，违反了 SET 规则
	 * 正确的应该是：c1 != c2 && c1 != c3 && c2 != c3
	 */
	bool Combinaison::estUnSet() const
	{
		// 测试颜色：全相同 或 全不同
		// ⚠️ BUG：第二个条件允许 c2 == c3，应该是三者都不同
		bool test1 = (c1->getCouleur() == c2->getCouleur() && c1->getCouleur() == c3->getCouleur()) ||
					 (c1->getCouleur() != c2->getCouleur() && c1->getCouleur() != c3->getCouleur() && c2->getCouleur() != c3->getCouleur());

		// 测试形状：全相同 或 全不同
		bool test2 = (c1->getForme() == c2->getForme() && c1->getForme() == c3->getForme()) ||
					 (c1->getForme() != c2->getForme() && c1->getForme() != c3->getForme() && c2->getForme() != c3->getForme());

		// 测试数量：全相同 或 全不同
		bool test3 = (c1->getNombre() == c2->getNombre() && c1->getNombre() == c3->getNombre()) ||
					 (c1->getNombre() != c2->getNombre() && c1->getNombre() != c3->getNombre() && c2->getNombre() != c3->getNombre());

		// 测试填充：全相同 或 全不同
		bool test4 = (c1->getRemplissage() == c2->getRemplissage() && c1->getRemplissage() == c3->getRemplissage()) ||
					 (c1->getRemplissage() != c2->getRemplissage() && c1->getRemplissage() != c3->getRemplissage() && c2->getRemplissage() != c3->getRemplissage());

		// 所有四个特征都必须满足规则
		return test1 && test2 && test3 && test4;
	}

	/**
	 * 从牌堆向游戏台分发卡牌 (Distribute cards from pioche to plateau)
	}

	/**
	 * 从牌堆向游戏台分发卡牌 (Distribute cards from pioche to plateau)
	 *
	 * 分发规则：
	 * =========
	 * 1. 如果游戏台少于 12 张牌：
	 *    - 尝试补齐到 12 张
	 *    - 从牌堆抽取卡牌，直到达到 12 张或牌堆为空
	 *
	 * 2. 如果游戏台已有 12 张或更多牌：
	 *    - 只添加 1 张牌
	 *    - 用于玩家找不到 SET 时增加选择
	 *
	 * 3. 如果牌堆为空：
	 *    - 什么都不做
	 *    - 游戏可能即将结束
	 *
	 * 实现细节：
	 * =========
	 * - 先添加一张牌（确保至少尝试添加一次）
	 * - 然后检查是否需要继续补充（少于 12 张）
	 * - 使用 while 循环持续抽牌，直到达到条件
	 *
	 * 为什么是 12 张？
	 * ==============
	 * - SET 游戏标准规则：游戏台应始终有 12 张牌
	 * - 12 = 3×4，便于视觉布局（3 行 4 列或 4 行 3 列）
	 * - 统计上，12 张牌中存在 SET 的概率很高
	 */
	void Controleur::distribuer()
	{
		// 如果牌堆不为空，先添加一张牌
		if (!pioche->estVide())
			plateau.ajouter(pioche->piocher());

		// 如果游戏台少于 12 张牌，继续补充
		while (!pioche->estVide() && plateau.getNbCartes() < 12)
			plateau.ajouter(pioche->piocher());
	}

	/**
	 * Combinaison 类的输出运算符重载 (Output operator for Combinaison)
	 *
	 * @param f 输出流对象（如 cout, ofstream 等）
	 * @param c 要输出的组合对象
	 * @return 返回输出流对象（支持链式输出）
	 *
	 * 输出格式：[卡牌1 ; 卡牌2 ; 卡牌3]
	 * 示例：[[R◇1P] ; [M◇2P] ; [V◇3P]]
	 */
	ostream &operator<<(ostream &f, const Combinaison &c)
	{
		f << "[" << c.getCarte1() << " ; " << c.getCarte2() << " ; " << c.getCarte3() << "]";
		return f;
	}

	/**
	 * 打印游戏台的所有卡牌 (Print all cards on the plateau)
	 *
	 * @param f 输出流对象
	 *
	 * 显示格式：
	 * =================== PLATEAU ===================
	 * [卡牌1][卡牌2][卡牌3]
	 * [卡牌4][卡牌5][卡牌6]
	 * ...
	 * ===============================================
	 *
	 * 布局规则：
	 * - 每 3 张卡牌换行
	 * - 便于玩家观察和寻找 SET
	 * - 上下装饰线使输出更清晰
	 */
	void Plateau::print(ostream &f) const
	{
		f << "=================== PLATEAU ===================\n";

		// 遍历并打印所有卡牌
		for (size_t i = 0; i < nb; i++)
		{
			// 每 3 张卡牌换行（创建类似网格的布局）
			if (i % 3 == 0)
				f << "\n";

			// 打印卡牌（自动调用 Carte 的 operator<<）
			f << *cartes[i];
		}

		f << "\n===============================================\n";
	}

	/**
	 * Plateau 类的输出运算符重载 (Output operator for Plateau)
	 *
	 * @param f 输出流对象
	 * @param c Plateau 对象
	 * @return 返回输出流对象（支持链式输出）
	 *
	 * 委托给 print() 方法实现
	 * 使用方法：cout << plateau;
	 */
	ostream &operator<<(ostream &f, const Plateau &c)
	{
		c.print(f);
		return f;
	}

}