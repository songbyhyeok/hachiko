using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneMgr : MonoBehaviour
{
    private void Awake()
    {
        SceneManager.LoadScene("MaingameUI", LoadSceneMode.Additive);
    }
}
