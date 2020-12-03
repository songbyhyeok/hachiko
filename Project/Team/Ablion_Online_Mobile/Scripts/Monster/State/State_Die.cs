using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Die : State
{
    public override void Enable()
    {
        mMonsterAnimator.SetTrigger("triggerDie");

        mMonsterAI.mIsDeath = true;
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