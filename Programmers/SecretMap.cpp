#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2)
{
	vector<vector<vector<int>>> binaryVec3(2, vector<vector<int>>(n, vector<int>(n, 0)));

	int mapIdx = 0;
	while(mapIdx < binaryVec3.size())
	{
		vector<int> currMap = mapIdx == 0 ? arr1 : arr2;
		int mapPos = 0, currPos = 0, binaryPos = 0;

		while (mapPos < currMap.size())
		{
			if (currMap[currPos] != 0)
			{
				binaryVec3[mapIdx][mapPos][binaryPos++] = currMap[currPos] % 2;
				currMap[currPos] /= 2;
			}

			else
			{
				binaryPos = 0;
				currPos++;
				mapPos++;
			}
		}

		mapIdx++;
	} 

	vector<string> answer;

	for (int i = 0; i < n; i++)
	{
		string putChar;

		for (int j = n - 1; j >= 0; j--)
			binaryVec3[0][i][j] + binaryVec3[1][i][j] != 0 ? putChar += '#' : putChar += ' ';

		answer.push_back(putChar);
	}

	return answer;
}


int main()
{
	// Case.1
	int n = 5;
	vector<int> arr1 = { 9, 20, 28, 18, 11 }, arr2 = { 30, 1, 21, 17, 28 };

	// Case.2
	int n2 = 6;
	vector<int> arr3 = { 46, 33, 33, 22, 31, 50 }, arr4 = { 27, 56, 19, 14, 14, 10 };

	vector<string> tempVec = solution(n, arr1, arr2);
	vector<string> tempVec2 = solution(n2, arr3, arr4);

	for (int i = 0; i < tempVec.size(); i++)
		cout << tempVec[i] << endl;

	return 0;
}