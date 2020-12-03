using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CSVReader.Data("Name")]
public class SkillData
{
    public string Name;
    public string ClassName;
    public string JobName;
    public int Damage;
    public float CoolTime;
    public float FirstDelay;
    public float EndDelay;
    public float ProjectileSpeed;
}