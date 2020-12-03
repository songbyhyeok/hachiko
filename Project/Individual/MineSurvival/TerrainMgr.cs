using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerlinNoise : MonoBehaviour
{
    private GameObject obj;
    private float frequency, amplitude, yOffset;

    public PerlinNoise(GameObject _o, int _f, int _a, int _y)
    {
        this.obj = _o;
        this.frequency = _f;
        this.amplitude = _a;
        this.yOffset = _y;
    }

    public void MapInit(int column, int row)
    {
        // 4등분 1
        for (int x = 0; x <= 2; x++)
        {
            for (int z = 0; z < row; z++)
            {
                if (z < row - 3)
                    NoiseSet(x, z);
                // 4등분 2
                else
                {
                    for (int i = 0; i < column; i++)
                    {
                        if (i < column - 3)
                            NoiseSet(i, z);
                        // 4등분 3
                        else
                        {
                            for (int j = row - 1; j >= 0; j--)
                            {
                                if (j >= 3)
                                    NoiseSet(i, j);
                                // 4등분 4
                                else
                                    for (int k = column - 1; k >= 3; k--)
                                        NoiseSet(k, j);
                            }
                        }
                    }
                }
            }
        }
    }

    void NoiseSet(int x, int z)
    {
        float lacunarity_X = x / frequency, lacunarity_Z = z / frequency;
        int persistance_Y = (int)(Mathf.PerlinNoise(lacunarity_X, lacunarity_Z) * amplitude + yOffset);
        Vector3 vecPos = new Vector3(x * 2.0f, persistance_Y, z * 2.0f);
        CreateBlock(persistance_Y, vecPos);
    }

    void CreateBlock(int persistance_Y, Vector3 blockPos)
    {
        if (persistance_Y <= 3)
        {
            GameObject blockOB;

            if (blockPos.y == 3)
            {
                blockPos.y = 4;

                Vector3 tempVec3 = blockPos;
                tempVec3.y = 2;
                blockOB = Instantiate(obj, tempVec3, Quaternion.identity);
                blockOB.transform.parent = GameObject.Find("Terrain").GetComponent<Transform>();
            }

            blockOB = Instantiate(obj, blockPos, Quaternion.identity);
            blockOB.transform.parent = GameObject.Find("Terrain").GetComponent<Transform>();
        }
    }
}

public class FloodFill
{
    private int col, row, val;
    private List<int>[] gVecList;

    public FloodFill(List<int>[] _gVecList)
    {
        col = 0;
        row = 0;
        val = 0;
        gVecList = _gVecList;
    }

    public FloodFill(int _col, int _row, int _val)
    {
        this.col = _col;
        this.row = _row;
        this.val = _val;
    }

    public int Col_Name
    {
        get { return col; }
    }

    public int Row_Name
    {
        get { return row; }
    }

    public int Val_Name
    {
        get { return val; }
    }

    public void Create(int x, int y, int curVal, List<FloodFill> result)
    {
        if (curVal == gVecList[x][y])
        {
            result.Add(new FloodFill(x, y, curVal));

            gVecList[x][y] = 9999;

            if (y > 0 && curVal == gVecList[x][y - 1])
                Create(x, y - 1, curVal, result);
            if (y < gVecList[0].Count - 1 && curVal == gVecList[x][y + 1])
                Create(x, y + 1, curVal, result);
            if (x > 0 && curVal == gVecList[x - 1][y])
                Create(x - 1, y, curVal, result);
            if (x < gVecList.Length - 1 && curVal == gVecList[x + 1][y])
                Create(x + 1, y, curVal, result);
        }
    }
}

public class TerrainMgr : MonoBehaviour
{
    enum Probability { A = 5, B = 15, C = 30, D = 50, E = 70, F = 100};
    enum PositionType { A = 0, B = 1, C = 2, Max = 3};
    enum WaterType { A, B, MAX };
    enum HillType { A, B, C, D, MAX };

    [SerializeField] GameObject m_SoilPrefab, m_GrassPrefab, m_HillGrassPrefab, m_ForestGrassPrefab, m_TreeApplePrefab, m_RockPrefab, m_Rock1Prefab, m_Rock2Prefab, m_WaterPrefab;
    [SerializeField] int row, column;

    int temp = 999, n = 0, r = 999, select = 999;
    List<int>[] listArr;
    List<GameObject> listObejct = new List<GameObject>(0);

    PerlinNoise m_PerlinNoise;
    FloodFill m_FloodFill;

    private void Awake()
    {
        m_PerlinNoise = new PerlinNoise(m_HillGrassPrefab, 2, 2, 2);

        listArr = new List<int>[column];
        for (int i = 0; i < column; i++)
        {
            listArr[i] = new List<int>();
            for (int j = 0; j < row; j++)
                listArr[i].Add(0);
        }

        listObejct.Add(m_SoilPrefab); listObejct.Add(m_GrassPrefab); listObejct.Add(m_HillGrassPrefab);
        listObejct.Add(m_ForestGrassPrefab); listObejct.Add(m_TreeApplePrefab);
        listObejct.Add(m_RockPrefab); listObejct.Add(m_Rock1Prefab); listObejct.Add(m_Rock2Prefab);
        listObejct.Add(m_WaterPrefab);

        // 사용할 퍼센트 변수
        double a = (10.0 / 100) * row , b = (30.0 / 100) * row, c = (40.0 / 100) * row,
        d = (70.0 / 100) * row, e = (90.0 / 100) * row;

        for (int i = 0; i < column; i++)
        {
            if (n == 0)
            {
                n = Random.Range(0, 5);
                temp = PositionRange((int)a, (int)b, (int)c, (int)d, (int)e);
                select = Random.Range(0, (int)Probability.F);
                // 물
                if (select < (int)Probability.A && i < 95)
                {
                    int waterSelect = Random.Range((int)WaterType.A, (int)WaterType.MAX);
                    switch(waterSelect)
                    {
                        case (int)WaterType.A:
                            listArr[i][temp] = 2;

                            for (int k = temp; k <= temp + 2; k++)
                                listArr[i + 1][k - 1] = 2;

                            listArr[i + 2][temp] = 2;
                            break;

                        case (int)WaterType.B:
                            for (int k = temp; k <= temp + 2; k++)
                            {
                                listArr[i][k] = 2;
                                listArr[i + 4][k] = 2;
                            }
                            for (int k = temp; k <= temp + 4; k++)
                            {
                                listArr[i + 1][k - 1] = 2;
                                listArr[i + 2][k - 1] = 2;
                                listArr[i + 3][k - 1] = 2;
                            }
                            break;
                    }
                }
                // 언덕
                else if (select < (int)Probability.B && i < 95)
                {
                    int hSelect = Random.Range((int)HillType.A, (int)HillType.MAX);
                    switch(hSelect)
                    {
                        case (int)HillType.A:
                            for (int k = temp; k <= temp + 2; k++)
                                listArr[i][k] = 3;
                            break;

                        case (int)HillType.B:
                            for (int k = 0; k < 3; k++)
                                listArr[i + k][temp] = 3;
                            break;

                        case (int)HillType.C:
                            for (int k = 0; k < 3; k++)
                                for (int u = temp - 1; u < temp + 2; u++)
                                {
                                    listArr[i + k][u] = 3;

                                    if (k == 1 && u == temp)
                                        listArr[i + k][u] = 4;
                                }
                            break;

                        case (int)HillType.D:
                            for (int k = 0; k < 6; k++)
                                for (int u = temp - 1; u < temp + 5; u++)
                                {
                                    listArr[i + k][u] = 3;

                                    if (0 < k && k < 5 && temp - 1 < u && u < temp + 4)
                                        listArr[i + k][u] = 4;
                                }
                            break;
                    }
                }

                else
                    n = 0;

                temp = PositionRange((int)a, (int)b, (int)c, (int)d, (int)e);
                select = Random.Range(0, (int)Probability.F);
            }
            else
                n--;

            int q = 0;
            if (select < (int)Probability.B && temp != 999)
                for (int j = 0; j < row; j++)
                {
                    if (!(2 <= listArr[i][j] && listArr[i][j] <= 4))
                    {
                        if (r == (int)PositionType.A && a <= j && j <= temp)
                            listArr[i][j] = 1;
                        else if (r == (int)PositionType.B && c <= j && j <= temp)
                            listArr[i][j] = 1;
                        else if (r == (int)PositionType.C && d <= j && j <= temp)
                            listArr[i][j] = 1;

                        if (Random.Range(0, 100) < 1 && q == 0)
                            q = 5;
                        else if (q != 0)
                        {
                            q--;
                            listArr[i][j] = 0;
                        }
                    }
                }
        }
        m_FloodFill = new FloodFill(listArr);

        for (int i = 0; i < column; i++)
        {
            GameObject terrainObj;
            for (int j = 0; j < row; j++)
            {
                if (Random.Range((int)a, (int)e) == j && listArr[i][j] != 2 && listArr[i][j] != 3 && listArr[i][j] != 4 && listArr[i][j] != 9999)
                {
                    terrainObj = Instantiate(listObejct[Random.Range(3, listObejct.Count - 1)], new Vector3(i * 2, 1f, j * 2), Quaternion.identity);
                    terrainObj.transform.parent = GameObject.Find("Terrain").GetComponent<Transform>();
                }

                if (listArr[i][j] == 0 || listArr[i][j] == 9999)
                {
                    if (listArr[i][j] == 0)
                    {
                        terrainObj = Instantiate(listObejct[1], new Vector3(i * 2, 0f, j * 2), Quaternion.identity);
                        terrainObj.transform.parent = GameObject.Find("Terrain").GetComponent<Transform>();
                    }

                    continue;
                }

                List<FloodFill> list = new List<FloodFill>();
                m_FloodFill.Create(i, j, listArr[i][j], list);

                for (int k = 0; k < list.Count; k++)
                {
                    float tempHeight = 0.0f;
                    GameObject currGameOb = null;

                    if (list[k].Val_Name == 1)
                        currGameOb = listObejct[0];

                    else if (list[k].Val_Name == 2)
                    {
                        currGameOb = listObejct[listObejct.Count - 1];
                        tempHeight = -0.3f;
                    }

                    else if (list[k].Val_Name == 3 || list[k].Val_Name == 4)
                    {
                        currGameOb = listObejct[2];

                        if (list[k].Val_Name == 3)
                            tempHeight = 1.0f;
                        else
                            tempHeight = 2.0f;
                    }

                    terrainObj = Instantiate(currGameOb, new Vector3(list[k].Col_Name * 2, tempHeight, list[k].Row_Name * 2), Quaternion.identity);
                    terrainObj.transform.parent = GameObject.Find("Terrain").GetComponent<Transform>();
                }
            }
        }

        m_PerlinNoise.MapInit(column, row);
    }

    int PositionRange(int _a, int _b, int _c, int _d, int _e)
    {
        int temp = 0;
        r = Random.Range(0, (int)PositionType.Max);

        if (r == (int)PositionType.A)
            temp = Random.Range(_a, _b + _a);
        else if (r == (int)PositionType.B)
            temp = Random.Range(_c, _d);
        else if (r == (int)PositionType.C)
            temp = Random.Range(_d, _e);

        return temp;
    }
}
