using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Scenenext : MonoBehaviour
{
    public void btn()
    {
        SceneManager.LoadScene("Field2");
        SceneManager.LoadScene("MaingameUI", LoadSceneMode.Additive);
    }
}
