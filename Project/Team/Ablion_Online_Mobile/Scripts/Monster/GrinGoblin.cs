using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrinGoblin : MonsterAI
{
    public override void Start()
    {
        base.Start();

        ChangeState(mStates[(int)States.Idle]);
    }

    public override void SetState()
    {
        mStates[(int)States.Idle] = new State_Idle();
        mStates[(int)States.Trace] = new State_Trace();
        mStates[(int)States.NomalAttack] = new State_NomalAttack();
        mStates[(int)States.Damaged] = new State_Damaged();
        mStates[(int)States.Die] = new State_Die();
    }

    void Attack()
    {
        ((State_NomalAttack)mStates[(int)States.NomalAttack]).Attack();
    }

    void Die()
    {
        StartCoroutine(CoroutineDie());
    }

    IEnumerator CoroutineDie()
    {
        yield return new WaitForSeconds(3f);

        gameObject.SetActive(false);
        yield break;
    }
}
