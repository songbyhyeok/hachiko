using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class PanelSkillUI : MonoBehaviour
{
    public int mBtn_num;
    public bool mBtn_skill;

    // atk = 0 | skill_fire = 1 | skill_ice = 2 | skill_heal = 3

    public bool mAttack_Btn = false;
    public bool mFireSkill_Btn = false;
    public bool mIceSkill_Btn = false;
    public bool mHeal_UiBtn = false;



    
    private void Update()
    {
        if (mAttack_Btn)
        {
            UIEventToInGame.Instance.OnEventAttackBtn(mAttack_Btn);
            mAttack_Btn = false;
            UIEventToInGame.Instance.OnEventAttackBtn(mAttack_Btn);
        }
        else if (mIceSkill_Btn)
        {
            UIEventToInGame.Instance.OnEventIceSkillBtn(mIceSkill_Btn);
            mIceSkill_Btn = false;
            UIEventToInGame.Instance.OnEventIceSkillBtn(mIceSkill_Btn);
        }
        else if (mFireSkill_Btn)
        {     
            UIEventToInGame.Instance.OnEventFireSkillBtn(mFireSkill_Btn);
            mFireSkill_Btn = false;
            UIEventToInGame.Instance.OnEventFireSkillBtn(mFireSkill_Btn);
        }
        else if (mHeal_UiBtn)
        {
            UIEventToInGame.Instance.OnEventHealSkillBtn(mHeal_UiBtn);
            mHeal_UiBtn = false;
            UIEventToInGame.Instance.OnEventHealSkillBtn(mHeal_UiBtn);
        }

    }

    public void EventAttackBtn()
    {
        mAttack_Btn = true;
    }
    public void EventSkill_Icebtn()
    {
        mIceSkill_Btn = true;
    }
    public void EventSkill_FireBtn()
    {
        mFireSkill_Btn = true;
    }
    public void EventHealBtn()
    {
        mHeal_UiBtn = true;
    }


}