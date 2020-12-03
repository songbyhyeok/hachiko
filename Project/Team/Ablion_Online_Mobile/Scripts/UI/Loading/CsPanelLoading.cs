using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CsPanelLoading : MonoBehaviour
{
    Image mLoadingBarGage;

    private void Awake()
    {
        mLoadingBarGage = transform.Find("LoadingBarGage").GetComponent<Image>();

        StartCoroutine(LoadScene());
    }

    IEnumerator LoadScene()
    {
        yield return null; // 업데이트 -> 한 프레임 우선 return null로 처리 후 밑에 코드처리

        AsyncOperation op = SceneManager.LoadSceneAsync("MainScene");
        op.allowSceneActivation = false; // 씬 로딩이 끝나도 다음 씬으로 이동을 못하게 대기 상태처리

        float timer = 0.0f;
        while (!op.isDone) // isDone 해당 동작이 준비되었는지의 여부
        {
            yield return null; // 한 턴 우선 넘기고

            timer += Time.deltaTime; // 시간 증감

            if (op.progress < 0.9f) // float progress 작업의 진행 정도 0 과 1 사이의 값으로 확인
            {
                mLoadingBarGage.fillAmount = Mathf.Lerp(mLoadingBarGage.fillAmount, op.progress, timer);

                if (mLoadingBarGage.fillAmount >= op.progress)
                    timer = 0f;
            }
            else
            {
                mLoadingBarGage.fillAmount = Mathf.Lerp(mLoadingBarGage.fillAmount, 1f, timer);

                if (mLoadingBarGage.fillAmount == 1.0f)
                {
                    op.allowSceneActivation = true;

                    yield break;
                }
            }
        }
    }
}
