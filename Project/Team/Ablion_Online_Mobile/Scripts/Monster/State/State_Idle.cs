using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Idle : State
{

    public override void Enable()
    {
        mMonsterAnimator.SetBool("isJumpDown", false);
    }

    public override void Update()
    {
    }

    public override IEnumerator Coroutine()
    {
        if (!mMonsterAI.mChangeTrace)
            yield break;

        while (true)
        {
            yield return new WaitForSeconds(1f);

            mMonsterAI.ChangeState(mMonsterAI.mStates[(int)States.Trace]);

            yield break;
        }
    }

    public override void Disable()
    {
    }
}
