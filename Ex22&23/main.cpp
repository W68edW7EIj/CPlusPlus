#include "set.h"
#include <vector>
#include <algorithm>
using namespace Set;

void f(Plateau &dest, const Plateau &source)
{
	dest = source;
}

// ============================================================================
// Ex23 功能函数 (Ex23 Functions)
// ============================================================================

/**
 * 题目 4：使用传统迭代器遍历所有卡牌
 */
void afficherCartes()
{
	Jeu &jeu = Jeu::getInstance();
	cout << "\n=== 使用 Iterator 遍历所有卡牌 ===" << endl;
	int count = 0;
	for (Jeu::Iterator it = jeu.first(); !it.isDone(); it.next())
	{
		cout << it.getCurrentItem() << " ";
		if (++count % 9 == 0)
			cout << "\n";
	}
	cout << "\n总共 " << count << " 张卡牌\n"
		 << endl;
}

/**
 * 题目 5：使用形状过滤迭代器遍历特定形状的卡牌
 */
void afficherCartes(Forme f)
{
	Jeu &jeu = Jeu::getInstance();
	cout << "\n=== 使用 FormeIterator 遍历形状为 " << f << " 的卡牌 ===" << endl;

	// 需要先找到第一张匹配的卡牌
	Jeu::FormeIterator it = jeu.firstFormeIterator(f);

	// 找到第一张匹配的卡牌
	while (!it.isDone() && it.getCurrentItem().getForme() != f)
		it.next();

	int count = 0;
	while (!it.isDone())
	{
		cout << it.getCurrentItem() << " ";
		if (++count % 9 == 0)
			cout << "\n";
		it.next();
	}
	cout << "\n总共 " << count << " 张 " << f << " 形状的卡牌\n"
		 << endl;
}

/**
 * 题目 6：使用 STL 风格迭代器遍历 Plateau
 */
void afficherCartes(const Plateau &p)
{
	cout << "\n=== 使用 STL 风格迭代器遍历 Plateau ===" << endl;
	int count = 0;
	for (Plateau::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		cout << *it << " ";
		if (++count % 6 == 0)
			cout << "\n";
	}
	cout << "\n总共 " << count << " 张卡牌在 Plateau 上\n"
		 << endl;
}

/**
 * 查找 Plateau 中所有有效的 SET 组合
 */
std::vector<Combinaison> trouverTousSets(const Plateau &p)
{
	std::vector<Combinaison> sets;
	size_t n = p.getNbCartes();

	// 使用迭代器遍历所有三张卡的组合
	std::vector<const Carte *> cartes;
	for (Plateau::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		cartes.push_back(&(*it));
	}

	// 三重循环检查所有可能的三张卡组合
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			for (size_t k = j + 1; k < n; k++)
			{
				Combinaison combo(*cartes[i], *cartes[j], *cartes[k]);
				if (combo.estUnSet())
				{
					sets.push_back(combo);
				}
			}
		}
	}

	return sets;
}

/**
 * 题目 7：完整的 SET 游戏
 */
void jouerSet()
{
	cout << "\n";
	cout << "========================================" << endl;
	cout << "       欢迎来到 SET 纸牌游戏！         " << endl;
	cout << "========================================" << endl;
	cout << "\nSET 规则：" << endl;
	cout << "找出三张卡牌，对于每个特征（颜色、形状、数量、填充）" << endl;
	cout << "这三张卡必须全相同或全不同\n"
		 << endl;

	Controleur ctrl;
	ctrl.distribuer();

	cout << "当前桌面：" << endl;
	cout << ctrl.getPlateau() << endl;

	// 自动查找所有 SET
	cout << "正在查找所有可能的 SET 组合..." << endl;
	std::vector<Combinaison> sets = trouverTousSets(ctrl.getPlateau());

	if (sets.empty())
	{
		cout << "❌ 当前桌面上没有有效的 SET 组合！" << endl;
		cout << "需要从牌堆再发牌..." << endl;
	}
	else
	{
		cout << "✓ 找到 " << sets.size() << " 个有效的 SET 组合：\n"
			 << endl;
		for (size_t i = 0; i < sets.size(); i++)
		{
			cout << "SET #" << (i + 1) << ": " << sets[i] << endl;
		}
	}

	cout << "\n剩余牌堆卡牌数: " << ctrl.getPioche().getNbCartes() << endl;
}

int main()
{
	try
	{
		// Test 1: Display all possible values
		cout << "=== Test 1: Display characteristic values ===" << endl;
		printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();
		cout << endl;

		// Test 2: Get Jeu instance and display some cards
		cout << "=== Test 2: Display some cards from Jeu ===" << endl;
		Jeu &j = Jeu::getInstance();
		for (size_t i = 0; i < 10; i++)
			cout << j.getCarte(i) << "\n";
		cout << endl;

		// Test 3: Use Iterator
		cout << "=== Test 3: Iterate using Iterator ===" << endl;
		Jeu::Iterator it = j.first();
		int count = 0;
		while (!it.isDone() && count < 10)
		{
			cout << it.getCurrentItem();
			it.next();
			count++;
		}
		cout << "\n"
			 << endl;

		// Test 4: Use const_iterator with range-based for loop
		cout << "=== Test 4: Range-based for loop ===" << endl;
		count = 0;
		for (const Carte &c : j)
		{
			cout << c << "\n";
			if (++count >= 10)
				break;
		}
		cout << endl;

		// Test 5: Test Plateau operations
		cout << "=== Test 5: Plateau operations ===" << endl;
		Plateau p1;
		p1.ajouter(j.getCarte(0));
		p1.ajouter(j.getCarte(1));
		p1.ajouter(j.getCarte(2));
		cout << "Plateau p1:" << endl;
		cout << p1;

		Plateau p2;
		p2.ajouter(j.getCarte(3));
		p2.ajouter(j.getCarte(4));
		cout << "Plateau p2:" << endl;
		cout << p2;

		// Test copy constructor
		Plateau p3(p1);
		cout << "Plateau p3 (copy of p1):" << endl;
		cout << p3;

		// Test assignment operator
		p2 = p1;
		cout << "Plateau p2 after p2 = p1:" << endl;
		cout << p2;
		cout << endl;

		// Test 6: Combinaison and estUnSet
		cout << "=== Test 6: Test Combinaison ===" << endl;
		Combinaison combo1(j.getCarte(0), j.getCarte(1), j.getCarte(2));
		cout << "Combinaison: " << combo1 << endl;
		cout << "Est un SET? " << (combo1.estUnSet() ? "Oui" : "Non") << endl;
		cout << endl;

		// Test 7: Controleur
		cout << "=== Test 7: Test Controleur ===" << endl;
		Controleur ctrl;
		ctrl.distribuer();
		cout << ctrl.getPlateau();
		cout << "Nombre de cartes dans la pioche: " << ctrl.getPioche().getNbCartes() << endl;
		cout << endl;

		// ====================================================================
		// Ex23 测试：单例模式和迭代器模式
		// ====================================================================
		cout << "\n";
		cout << "============================================================" << endl;
		cout << "               Ex23: 单例模式与迭代器模式测试               " << endl;
		cout << "============================================================" << endl;

		// 题目 1-3: 单例模式测试
		cout << "\n=== 题目 1-3: 单例模式测试 ===" << endl;
		Jeu &jeu1 = Jeu::getInstance();
		Jeu &jeu2 = Jeu::getInstance();
		cout << "Jeu 单例测试：" << endl;
		cout << "  jeu1 地址: " << &jeu1 << endl;
		cout << "  jeu2 地址: " << &jeu2 << endl;
		cout << "  是否为同一实例: " << (&jeu1 == &jeu2 ? "是 ✓" : "否 ✗") << endl;
		cout << "  总卡牌数: " << jeu1.getNbCartes() << endl;

		// 题目 4: 传统迭代器
		afficherCartes();

		// 题目 5: 形状过滤迭代器
		afficherCartes(Forme::ovale);
		afficherCartes(Forme::vague);
		afficherCartes(Forme::losange);

		// 题目 6: STL 风格迭代器 - Jeu
		cout << "\n=== STL 风格迭代器遍历 Jeu（前 20 张）===" << endl;
		int count2 = 0;
		for (const Carte &c : Jeu::getInstance())
		{
			cout << c << " ";
			if (++count2 >= 20)
				break;
			if (count2 % 10 == 0)
				cout << "\n";
		}
		cout << "\n"
			 << endl;

		// 题目 6: STL 风格迭代器 - Plateau
		Plateau testPlateau;
		Jeu &jeu = Jeu::getInstance();
		for (size_t i = 0; i < 12; i++)
		{
			testPlateau.ajouter(jeu.getCarte(i));
		}
		afficherCartes(testPlateau);

		// 使用 range-based for 遍历 Plateau
		cout << "\n=== 使用 range-based for 遍历 Plateau ===" << endl;
		int count3 = 0;
		for (const Carte &c : testPlateau)
		{
			cout << c << " ";
			if (++count3 % 6 == 0)
				cout << "\n";
		}
		cout << "\n"
			 << endl;

		// 题目 7: 完整的 SET 游戏
		cout << "\n";
		cout << "============================================================" << endl;
		cout << "                  题目 7: 完整的 SET 游戏                   " << endl;
		cout << "============================================================" << endl;
		jouerSet();

		// 额外测试：多次发牌直到找到 SET
		cout << "\n\n=== 额外测试：多次尝试找到 SET ===" << endl;
		Controleur ctrl2;
		int attempts = 0;
		const int maxAttempts = 5;

		while (attempts < maxAttempts)
		{
			attempts++;
			ctrl2.distribuer();

			cout << "\n第 " << attempts << " 次尝试：" << endl;
			cout << "桌面卡牌数: " << ctrl2.getPlateau().getNbCartes() << endl;

			std::vector<Combinaison> foundSets = trouverTousSets(ctrl2.getPlateau());

			if (!foundSets.empty())
			{
				cout << "✓ 找到 " << foundSets.size() << " 个 SET！" << endl;
				cout << "显示第一个 SET: " << foundSets[0] << endl;
				break;
			}
			else
			{
				cout << "✗ 未找到 SET，继续发牌..." << endl;
			}

			if (ctrl2.getPioche().getNbCartes() == 0)
			{
				cout << "牌堆已空，游戏结束。" << endl;
				break;
			}
		}

		cout << "\n";
		cout << "============================================================" << endl;
		cout << "                    Ex23 测试完成！                         " << endl;
		cout << "============================================================" << endl;
	}
	catch (SetException &e)
	{
		std::cout << "Exception: " << e.getInfo() << "\n";
	}

	return 0;
}