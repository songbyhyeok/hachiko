#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(string dartResult) 
{
	vector<int> numVec;

	for (int i = 0; i < dartResult.length(); i++)
	{
		if (isdigit(dartResult[i]) != 0)
		{
			if (isdigit(dartResult[i + 1]) != 0)
			{
				numVec.push_back(10);
				i += 1;
			}

			else
				numVec.push_back(atoi(&dartResult[i]));

			continue;
		}

		else
		{
			int starC = (numVec.size() - 2);
			starC = starC < 0 ? 0 : (numVec.size() - 2);

			switch (dartResult[i])
			{
			case 'S':
				numVec[numVec.size() - 1] = pow(numVec[numVec.size() - 1], 1);
				break;
			case 'D':
				numVec[numVec.size() - 1] = pow(numVec[numVec.size() - 1], 2);
				break;
			case 'T':
				numVec[numVec.size() - 1] = pow(numVec[numVec.size() - 1], 3);
				break;
			case '*':	
				for (int i = starC; i < numVec.size(); i++)
					numVec[i] *= 2;
				break;
			case '#':
				numVec[numVec.size() - 1] *= -1;
				break;
			}

			continue;
		}
	}

	int answer = 0;
	for (int i = 0; i < numVec.size(); i++)
		answer += numVec[i];

	return answer;
}

int main()
{
	string dartResult = "1S*2T*3S";
	cout << solution(dartResult);

	return 0;
}