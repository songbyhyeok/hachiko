using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonScr : MonoBehaviour
{
    public delegate void DelegatePunch();
    public event DelegatePunch eventPunch;

    GameObject m_View, m_Punch;
    CameraScr cameraCurrMode;

    bool viewModeSwitch = true;

    void Awake()
    {
        cameraCurrMode = GameObject.Find("Main Camera").GetComponent<CameraScr>();

        m_View = transform.Find("View").gameObject;
        m_View.GetComponent<Button>().onClick.AddListener(ViewButton);
        m_Punch = transform.Find("Punch").gameObject;
        m_Punch.GetComponent<Button>().onClick.AddListener(PunchButton);
    }

    void ViewButton()
    {
        if (viewModeSwitch)
        {
            cameraCurrMode.CurrMode("TopView");
            viewModeSwitch = false;
        }
        else
        {
            cameraCurrMode.CurrMode("QuarterView");
            viewModeSwitch = true;
        }
    }

    void PunchButton()
    {
        eventPunch();
    }
}
