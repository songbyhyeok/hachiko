using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PanelSkillCooldwon : MonoBehaviour
{
    public Image coolimage;
    public Button skillbtn;
    public float cooldown;
    public float finishtime;

    private bool isClick = false;

    private void Awake()
    {
        cooldown = 4f;
    }
    private void Start()
    {
        coolimage.enabled = false;
    }
    private void Update()
    {
        if (isClick)
        {
            if (finishtime > 0)
            {
                UIEventToInGame.Instance.OnEventAttackBtn(false);
                finishtime -= Time.deltaTime * 1f;
                if (finishtime < 0)
                {
                    finishtime = 0f;
                    if (skillbtn)
                    {
                        skillbtn.enabled = true;
                    }
                    isClick = false;
                    
                }
                float ratio = 0f + (finishtime / cooldown);
                if (coolimage)
                    coolimage.fillAmount = ratio;
            }
        }
        
    }

    public void StartSkillBtn()
    {
        coolimage.enabled = true;

        finishtime = cooldown;
        isClick = true;
        if (skillbtn)
        {
            skillbtn.enabled = false;
           // UIEventToInGame.Instance.OnEventAttackBtn(false);
        }

    }
}
