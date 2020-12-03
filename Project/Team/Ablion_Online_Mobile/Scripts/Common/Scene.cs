using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Scene : Singleton<Scene>
{
    public static string nextScene;

    [SerializeField] Image progressBar = null;

    public static void LoadScene(string sceneName = null)
    {
        //nextScene = sceneName;
        SceneManager.LoadScene("LoadingScene");
    }
}
