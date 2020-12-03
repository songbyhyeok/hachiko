using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AppearY_Goblin : MonoBehaviour
{
    [SerializeField]
    GameObject[] mYellowGoblins;

    public GameObject[] mP_YellowGoblins
    {
        get { return mYellowGoblins; }
        set { mYellowGoblins = value; }
    }

    private void OnTriggerEnter(Collider other)
    {
        foreach (GameObject goblins in mYellowGoblins)
        {
            goblins.SetActive(true);
        }
        gameObject.SetActive(false);
    }
}
