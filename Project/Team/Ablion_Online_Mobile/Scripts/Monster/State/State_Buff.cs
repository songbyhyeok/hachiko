using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Buff : State
{
    GameObject mBuffFxPrf;
    GameObject BuffFX_Self;

    public override void Enable()
    {
        mMonsterAnimator.SetTrigger("Buff");
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
