using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RedGoblin : MonsterAI
{
    [SerializeField]
    GameObject mTarget;
    Transform mTargetTransform;

    [SerializeField]
    GameObject mSkill1FXPrf;
    List<GameObject> mSkill1FX = new List<GameObject>();

    public override void Start()
    {
        base.Start();

        ChangeState(mStates[(int)States.Idle]);

        for (int i = 0; i < 5; ++i)
        {
            mSkill1FX.Add(Instantiate(mSkill1FXPrf, transform.position, transform.rotation));
            mSkill1FX[i].SetActive(false);
        }
    }

    public override void SetState()
    {
        mStates[(int)States.Idle] = new State_Idle();
        mStates[(int)States.Trace] = new State_Trace();
        mStates[(int)States.NomalAttack] = new State_NomalAttack();
        mStates[(int)States.Skill1] = new State_SkillYG();
        mStates[(int)States.Damaged] = new State_Damaged();
        mStates[(int)States.Die] = new State_Die();
    }

    void Attack()
    {
        ((State_NomalAttack)mStates[(int)States.NomalAttack]).Attack();
    }


    IEnumerator SkillUnActivated(int i)
    {
        yield return new WaitForSeconds(3f);

        mSkill1FX[i].SetActive(false);
        yield break;
    }

    void Skill()
    {
        for (int i = 0; i < 5; ++i)
        {
            if (mSkill1FX[i].activeSelf == false)
            {
                mSkill1FX[i].SetActive(true);
                mSkill1FX[i].transform.position = transform.position;
                mSkill1FX[i].transform.rotation = transform.rotation;
                StartCoroutine(SkillUnActivated(i));
                break;
            }
        }

    }
}
