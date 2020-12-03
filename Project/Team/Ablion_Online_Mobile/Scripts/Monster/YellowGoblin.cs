using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class YellowGoblin : MonsterAI
{
    public override void Start()
    {
        base.Start();

        ChangeState(mStates[(int)States.JumpDown]);
        gameObject.SetActive(false);
    }

    public override void SetState()
    {
        mStates[(int)States.JumpDown] = new State_JumpDown();
        mStates[(int)States.Idle] = new State_Idle();
        mStates[(int)States.Trace] = new State_Trace();
        mStates[(int)States.NomalAttack] = new State_NomalAttack();
        mStates[(int)States.Damaged] = new State_Damaged();
        mStates[(int)States.Die] = new State_Die();
    }

    void JumpEnd()
    {
        ChangeState(mStates[(int)States.Idle]);
    }

    void Attack()
    {
        ((State_NomalAttack)mStates[(int)States.NomalAttack]).Attack();
    }

    public void Die()
    {
        StartCoroutine(CoroutineDie());
    }

    IEnumerator CoroutineDie()
    {
        ChangeState(mStates[9]);
        yield return new WaitForSeconds(3f);
        gameObject.SetActive(false);
        yield break;
    }
}
