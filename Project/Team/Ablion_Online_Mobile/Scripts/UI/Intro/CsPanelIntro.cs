using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CsPanelIntro : MonoBehaviour
{
    GameObject mCRFATF_CHARACTER, mREDEEM_CODE, mLOGOUT, mACCOUNT;

    private void Awake()
    {
        mCRFATF_CHARACTER = transform.Find("CRFATF_CHARACTER").gameObject;
        mREDEEM_CODE = transform.Find("REDEEM_CODE").gameObject;
        mLOGOUT = transform.Find("LOGOUT").gameObject;
        mACCOUNT = transform.Find("ACCOUNT").gameObject;

        mACCOUNT.GetComponent<Button>().onClick.AddListener(LoadingMake);

        //Font font = Resources.GetBuiltinResource<Font>("Arial.ttf");
    }

    public void LoadingMake()
    {
        Scene.LoadScene();
    }
}
