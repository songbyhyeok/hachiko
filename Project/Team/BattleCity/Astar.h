#include "pch.h"

/* Astar Class Infor

// Ŭ������ ����.
Astar::Coordinate SP(0,0);
Astar::Coordinate DP(0,4);
Astar astar(SP, DP); // �ؽ�Ʈ ���� �ҷ��� �ʱ�ȭ, ������� ������ ���� �� �� ã�� �Լ����� ����.

// ���
astar.PrintPath(); // ����� ��ǥ�� ���������� ���. ex) 00 01 02 12 ...
astar.PrintMap(); // astar�� ����Ǿ� �ִ� ���� ���
astar.PrintNavi(); // ���� ����ϵ� astar ��θ� ���� 7�� ǥ��

// ��θ� ��������
/ ��ǥ ��������(GetPos(����))
astar.GetPos(1); // 1��° ����� ��ǥ�� ������
ex) cout << astar.GetPos(1).x << astar.GetPos(1).y << endl;
/ ��� ��ü�� ����Ʈ�� ��������(GetPath())
list<Astar::Coordinate*> path = astar.GetPath();
list<Astar::Coordinate*>::iterator iter = path.begin();

// �� ã��
astar.FindPath(); // �� ã�⸦ �ٽ� ����(���� �����Ǿ��� ��� �����ؾ� ��)

// ���� ����
astar.SetFree(0, 3); // �ش� ��ǥ�� ��ֹ��� ����
astar.SetObstacle(0, 3); // �ش� ��ǥ�� ��ֹ��� ��ġ

*/
typedef struct battletagTileAstar
{
	TERRAIN terrain;
	RECT rcTile;
	int frameX;
	int frameY;
	int objframeX;
	int objframeY;

}BATTLE_TILE_INFO_Astar;

typedef struct battletagMoveTileAstar
{
	POINT pos;
	TERRAIN terrain;

}MOVE_TILE_INFO_Astar;

class BattleScene;
class Astar
{
	

public: // ���� Ŭ����
	class Coordinate // x, y ��ǥ Ŭ����
	{
	public:
	
		int x;
		int y;
	public:
		void Set(int _x = 0, int _y = 0)
		{
			x = _x; y = _y;
		}
	public:
		Coordinate() {}
		Coordinate(int _x, int _y) : x(_x), y(_y) {}
	};

	class Node // ��� Ŭ����
	{
	public:
		Coordinate point;
		int F, G, H; // F = ���, G = ���� �Ÿ�, H = ���� �Ÿ�

		Coordinate end;
		Node* pParent;

	public:
		Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint);
		
		Node();
		~Node();
	};

	class Map // �� Ŭ����
	{
	public:
		BattleScene* battlescene;
		BATTLE_TILE_INFO* battleAstar;
		MOVE_TILE_INFO_Astar moveAstar[TILE_X / 2 * TILE_Y / 2];
		int sizeX, sizeY;
		int** map;
	public:
		void SetBattleScene(BattleScene* _battlescene) { battlescene = _battlescene; }
		void Copy(Map* _map); // �Ű������� Map ���� �޾ƿ��� �Ű��������� �������簡 �Ͼ.
		void PrintMap();
	public:

		Map();
		~Map();
	};



private: // ���� �Լ�
	list<Coordinate*> FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint);
	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); // ���³�� �� F���� ���� ���� ��� ã�Ƽ� ��ȯ
	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); // ��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ. ������ end()��ȯ.
	void ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint); // 8���� ��带 Ž���ϰ� ���� ��忡 �߰� �� �θ� ������ ������

public:
	void FindPath();
	Coordinate GetPos(int order); // order��° ����� ��ǥ�� �޾ƿ�
	list<Coordinate*> GetPath() { return path; } // ��θ� Coordinate* ����Ʈ�� ��°�� �޾ƿ�
	void SetFree(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ����
	void SetObstacle(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ��ġ
	void PrintPath();
	void PrintMap();
	int** PrintNavi();

private:
	Map Navi; // �� ����
	Map printNavi; // ��¿� �� ����(��α��� ���)

private:
	Coordinate StartPoint; // �������
	Coordinate EndPoint; // ��ǥ����
	list<Coordinate*> path; // ���
	list<Coordinate*>::iterator iter; // ��� iterator

public:
	Astar(Coordinate _StartPoint, Coordinate _EndPoint)
	{
		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
		FindPath();
	}
	~Astar()
	{ // path �����Ҵ� ����
		iter = path.begin();
		for (; iter != path.end(); iter++)
		{
			delete *iter;
		}
	}
};

