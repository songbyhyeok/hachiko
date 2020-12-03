using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_Move : State
{

    public override void Enable()
    {
        mMonsterAnimator.SetBool("isWalk", true);
    }

    public override void Update()
    {
        mMonsterAI.transform.Translate(mMonsterAI.transform.forward * 2 * Time.deltaTime, Space.World);
    }

    public override IEnumerator Coroutine()
    {

        while (true)
        {
            yield return new WaitForSeconds(1.5f);

            mMonsterAI.mChangeTrace = true;
            mMonsterAI.ChangeState(mMonsterAI.mStates[(int)States.Buff]);

            yield break;
        }
    }

    public override void Disable()
    {
        mMonsterAnimator.SetBool("isWalk", false);
    }
}
