using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Damaged : State
{
    public override void Enable()
    {
        mMonsterAnimator.SetTrigger("triggerDamaged");
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
