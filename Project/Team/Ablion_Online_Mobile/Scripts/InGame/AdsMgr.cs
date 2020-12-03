using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Advertisements;

public class simpleAdsMgr : MonoBehaviour
{
    //몇초 보고 스킵가능한 스킵용이라는데
    public void ShowAd()
    {
        if(Advertisement.IsReady())
        {
            
            Advertisement.Show("video");
        }
    }
    
}
