using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AI_Function : MonoBehaviour
{
    int attack, defense, moveSpeed;
}

public class Monster : AI_Function
{
    [SerializeField] List<int> monsterList;
}
