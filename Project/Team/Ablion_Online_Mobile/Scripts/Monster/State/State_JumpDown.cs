using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_JumpDown : State
{

    public override void Enable()
    {
        mMonsterAnimator.SetBool("isJumpDown", true);
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
