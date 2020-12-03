using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Skill1 : State
{
    GameObject mSkillPrf;
    public override void Awake(GameObject monster)
    {
        base.Awake(monster);

        mSkillPrf = (GameObject)Resources.Load("Skill1FX");
    }
    public override void Enable()
    {
        mMonsterAnimator.SetTrigger("triggerSkill1");
    }

    public override void Update()
    {

    }

    public override IEnumerator Coroutine()
    {
        yield break;
    }

    public override void Disable()
    {

    }
}
