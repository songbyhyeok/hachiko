using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Escape : State
{
    public override void Enable()
    {
        mMonsterAnimator.SetBool("isRun", true);

        mMonsterAI.mIsDeath = true;
    }

    public override void Update()
    {
        mTransform.Translate( -mTransform.forward * 2f * Time.deltaTime, Space.World);
    }

    public override IEnumerator Coroutine()
    {
        yield break;
    }

    public override void Disable()
    {
    }
}