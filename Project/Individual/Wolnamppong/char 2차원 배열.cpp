#include <iostream>

using namespace std;

int main()
{
	char type[2][3];

	//���� 0���� �� ����ũ�� ��
	cout << sizeof(type[0][0]) << endl;
	cout << sizeof(type[0][1]) << endl;
	cout << sizeof(type[0][2]) << endl;

	// ���� ���� 1 ������ ��� ���� ũ�⸸ŭ �����Ѵ�.
	cout << sizeof(type[1]) << endl;
	cout << sizeof(type[2]) << endl;

	//type[0][0] = 'a';
	//type[0][1] = 'b';
	//type[0][2] = 'c';

	strcpy_s(type[0], 3, "��");
	strcpy_s(type[1], 3, "��");

	//cin.getline(*type, 5);

	//cin >> type[0];
	//cin >> type[1];

	//cin >> *type;

	cout << type[0] << endl;
	cout << type[1] << endl;

	char ** type1 = new char*[4];

	type1[0] = new char[3];
	type1[1] = new char[3];
	type1[2] = new char[3];
	type1[3] = new char[3];

	


	











	return 0;
}