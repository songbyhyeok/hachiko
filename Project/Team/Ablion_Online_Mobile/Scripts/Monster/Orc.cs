using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Orc : MonsterAI
{
    [SerializeField]
    GameObject mBuffFxPrf;
    GameObject BuffFX_Self;
    List<GameObject> BuffFX_Mobs = new List<GameObject>();

    [SerializeField]
    GameObject mSkill1FXPrf;
    List<GameObject> mSkill1FX = new List<GameObject>();

    [SerializeField]
    Transform player;
    Transform target;

    [SerializeField]
    float UnActiveTime = 3f;

    public override void Start()
    {
        base.Start();

        ChangeState(mStates[(int)States.Idle]);

        for (int i = 0; i < 5; ++i)
        {
            BuffFX_Mobs.Add(Instantiate(mBuffFxPrf, transform.position, transform.rotation));
            BuffFX_Mobs[i].SetActive(false);

            mSkill1FX.Add(Instantiate(mSkill1FXPrf, transform.position, transform.rotation));
            mSkill1FX[i].SetActive(false);
        }
    }

    public override void SetState()
    {
        mStates[(int)States.Idle] = new State_Idle();
        mStates[(int)States.Trace] = new State_Trace();
        mStates[(int)States.NomalAttack] = new State_NomalAttack();
        mStates[(int)States.Walk] = new State_Move();
        mStates[(int)States.Buff] = new State_Buff();
        mStates[(int)States.Skill1] = new State_Skill1();
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

    void SkillFX1()
    {
        if (mCurrState == mStates[(int)States.Buff])
        {
            StartCoroutine(BuffMobs());
        }

        if (mCurrState == mStates[(int)States.Skill1])
        {
            StartCoroutine(Skill());
        }
    }

    void SkillFX2()
    {
        ChangeState(mStates[(int)States.Trace]);
    }

    public IEnumerator BuffMobs()
    {
        BuffFX_Self = Instantiate(mBuffFxPrf, transform.position, transform.rotation);

        yield return new WaitForSeconds(2f);

        Collider[] colliders = Physics.OverlapSphere(transform.position, 35f, 1 << 10);

        int buffNum = colliders.Length < 5 ? colliders.Length : 5;

        for (int i = 0; i < buffNum; ++i)
        {
            MonsterAI mob = colliders[i].GetComponent<MonsterAI>();

            if (mob != null && !mob.mIsDeath)
            {
                BuffFX_Mobs[i].SetActive(true);
                BuffFX_Mobs[i].transform.position = mob.transform.position;
            }

        }

        yield return new WaitForSeconds(2f);

        BuffFX_Self.SetActive(false);

        for (int i = 0; i < buffNum; ++i)
        {

            BuffFX_Mobs[i].SetActive(false);
        }

        yield break;
    }

    public IEnumerator Skill()
    {
        target = player;

        yield return new WaitForSeconds(1f);

        for (int i = 0; i < 5; ++i)
        {
            if (mSkill1FX[i].activeSelf == false)
            {
                mSkill1FX[i].SetActive(true);
                mSkill1FX[i].transform.position = target.position;
                mSkill1FX[i].transform.rotation = target.rotation;
                StartCoroutine(SkillUnActivated(i));
                break;
            }
        }
    }

    IEnumerator SkillUnActivated(int i)
    {
        yield return new WaitForSeconds(UnActiveTime);

        mSkill1FX[i].SetActive(false);
        yield break;
    }
}