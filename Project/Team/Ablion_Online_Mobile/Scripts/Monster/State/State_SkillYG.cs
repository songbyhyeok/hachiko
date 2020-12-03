using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_SkillYG : State
{

    public override void Enable()
    {
        mMonsterAnimator.SetTrigger("triggerSkill");
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