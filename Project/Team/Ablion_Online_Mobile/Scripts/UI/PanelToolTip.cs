using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PanelToolTip : MonoBehaviour
{
    public Image mPlayerHp;
    private float mNowHp;

    private void Start()
    {
        InGameEventToUI.Instance.EventHp += ChangeHp;
    }
    
    private void OnDestroy()
    {
        InGameEventToUI.Instance.EventHp -= ChangeHp;
    }

    private void ChangeHp(float hp)
    {
        float w = hp;
        if (w > 0)
            mPlayerHp.fillAmount = w / 20f;
    }

}