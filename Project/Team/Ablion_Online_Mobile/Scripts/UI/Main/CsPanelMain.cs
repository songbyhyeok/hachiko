using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CsPanelMain : MonoBehaviour
{
    Image mProfile, mNameBar, mHPGage, mMPGage;
    Text mNameBarText;
    Button mInventory;

    private void Awake()
    {
        mProfile = transform.Find("Profile").GetComponent<Image>();
        mNameBar = transform.Find("NameBar").GetComponent<Image>();
        mHPGage = transform.Find("Bar").transform.Find("HPGage").GetComponent<Image>();
        mMPGage = transform.Find("Bar").transform.Find("MPGage").GetComponent<Image>();

        mInventory = transform.Find("Inventory").GetComponent<Button>();
        mInventory.onClick.AddListener(GameObject.Find("Panel_Inventory").GetComponent<CsPanelInventory>().RemoteControl);
    }

    private void Update()
    {
        TransitionProFile();
    }

    void TransitionProFile()
    {
        if (mHPGage.fillAmount <= 0)
            mProfile.sprite = Resources.Load<Sprite>("UI/Main/StatusCharacterBlackIMG") as Sprite;
        else
            mProfile.sprite = Resources.Load<Sprite>("UI/Main/StatusCharacterWhiteIMG") as Sprite;
    }

}
