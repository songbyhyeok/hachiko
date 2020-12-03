#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solution(int n, vector<int> arr1, vector<int> arr2) 
{
	vector<vector<vector<int>>> binaryVec3(2, vector<vector<int>>(n, vector<int>(n, 0)));

	int mapIdx = 0;
	while(mapIdx < binaryVec3.size())
	{
		vector<int> currMap = mapIdx == 0 ? arr1 : arr2;
		int  mapPos = 0, currPos = 0, binaryPos = 0;

		while (mapPos < currMap.size())
		{
			binaryVec3[mapIdx][mapPos][binaryPos] = currMap[currPos] % 2;
			binaryPos != 4 ? binaryPos++ : binaryPos = 0;
			currMap[currPos] != 0 ? (currMap[currPos] /= 2) : currPos++;
			mapPos = currPos < n ? mapPos : mapPos++;
		}

		mapIdx++;
	} 
	
	/*for (int i = binaryVec.size() - 1; i >= 0; i--)
		for (int j = 0; j < binaryVec[i].size(); j++)
		{
			cout << binaryVec[i][j] << ' ';
		}

	cout << endl;*/

	vector<string> answer;
	//return answer;
}


int main()
{
	// Case.1
	int n = 5;
	vector<int> arr1 = { 9, 20, 28, 18, 11 }, arr2 = { 30, 1, 21, 17, 28 };
	/*for (int i = 0; i < n; i++)
		cout << solution(n, arr1, arr2)[i] << ' ';
	cout << endl;*/

	// Case.2
	int n2 = 6;
	vector<int> arr3 = { 46, 33, 33, 22, 31, 50 }, arr4 = { 27, 56, 19, 14, 14, 10 };
	/*for (int i = 0; i < n2; i++)
		cout << solution(n2, arr3, arr4)[i] << ' ';*/

	solution(n, arr1, arr2);
	solution(n2, arr3, arr4);

	return 0;
}