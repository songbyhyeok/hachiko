using UnityEngine;

public class UIEventToInGame : Singleton<UIEventToInGame>
{
    public event System.Action<Vector2> EventStickMove; // 조이스틱 방향에 관한 정보
    public event System.Action<bool> EventStickUp;      // 조이스틱을 놨을때
    public event System.Action<bool> EventAttackBtn;
    public event System.Action<bool> EventIceSkillBtn;  // 아이스 스킬의 누름의 여부
    public event System.Action<bool> EventFireSkillBtn;
    public event System.Action<bool> EventHealSkillBtn;

    public event System.Action EventSkillUp;

    public void OnEventStickMove(Vector2 direction)
    {
        if (EventStickMove != null)
            EventStickMove(direction);
    }

    public void OnEventStickUp(bool stickup)
    {
        if (EventStickUp != null)
            EventStickUp(stickup);
    }   

    public void OnEventAttackBtn(bool attack)
    {
        if (EventAttackBtn != null)
            EventAttackBtn(attack);
    }

    public void OnEventFireSkillBtn(bool fireskill)
    {
        if (EventFireSkillBtn != null)
            EventFireSkillBtn(fireskill);
    }

    public void OnEventIceSkillBtn(bool iceskill)
    {
        if (EventIceSkillBtn != null)
            EventIceSkillBtn(iceskill);
    }

    public void OnEventHealSkillBtn(bool healskill)
    {
        if (EventHealSkillBtn != null)
            EventHealSkillBtn(healskill);
    }

    public void OnEventBtnUp()
    {
        if (EventSkillUp != null)
            EventSkillUp();
    }
}
