using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class State_NomalAttack : State
{
    public override void Enable()
    {
        int rand = Random.Range(0, 2);
        if (rand == 0)
            mMonsterAnimator.SetTrigger("triggerAttack1");
        else
            mMonsterAnimator.SetTrigger("triggerAttack2");
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

    public void Attack()
    {
        if (!mMonsterAI.mIsDeath)
        {
            Collider[] colliders = Physics.OverlapBox(mTransform.position, new Vector3(1f, 1f, 1.3f), Quaternion.identity, 1 << 9);

            for (int i = 0; i < colliders.Length; ++i)
            {
                PlayerIG player = colliders[i].GetComponent<PlayerIG>();

                if (player != null && !player.mIsDeath)
                {
                    player.mHp--;
                    InGameEventToUI.Instance.OnEventReturnHp(player.mHp);
                    break;
                }
            }

        }
    }

    public void DelayTime()
    {

    }
}
