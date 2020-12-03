using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Advertisements;

public class rewardedAdsMgr : MonoBehaviour
{
    public void showRewarededAd()
    {
        if(Advertisement.IsReady("rewardedvideo"))
        {
            // 광고가 끝난 뒤 콜백함수 "HandleShowResult" 호출 
            var options = new ShowOptions { resultCallback = HandleShowResult };
            Advertisement.Show("rewardedVideo", options);
        }
    }
    // 광고가 종료된 후 자동으로 호출되는 콜백 함수 
    private void HandleShowResult(ShowResult result)
    {
        switch (result)
        {
            case ShowResult.Finished:
                //광고를 성공적으로 시청한 경우 보상지급
                Debug.Log("두배로 주겠다.");
                break;
            case ShowResult.Skipped:
                //스킵되었다면 보상 ㄴㄴ 창띄우기
                Debug.Log("스킵되면 안준다.");
                break;
            case ShowResult.Failed:
                Debug.Log("에러떴다.");
                break;
        }
    }
}
