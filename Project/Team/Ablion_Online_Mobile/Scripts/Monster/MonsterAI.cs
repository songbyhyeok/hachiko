using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

enum States
{
    Idle, Walk, JumpDown, Trace, NomalAttack, Buff, Skill1, Skill2, Damaged, Die, States_End
}

public abstract class MonsterAI : MonoBehaviour
{
    protected State mCurrState;
    public State[] mStates { get; protected set; } = new State[10];

    private Animator mAnimator;
    private NavMeshAgent mPathFider;

    public int mHp = 3;
    public int mMaxHp = 3;
    public int mSpeed = 10;
    public bool mIsDeath = false;

    public bool mChangeTrace = true;
    public float mSkillDistance = 0f;

    [SerializeField]
    GameObject itemPrf;

    void Awake()
    {
        mAnimator = GetComponent<Animator>();
        mPathFider = GetComponent<NavMeshAgent>();
    }

    public virtual void Start()
    {
        SetState();

        foreach (State state in mStates)
        {
            if(state != null)
                state.Awake(gameObject);
        }
    }

    public virtual void Update()
    {
        if (Input.GetKeyDown(KeyCode.P))
        {
            mHp -= 1;

            if (mHp > 0)
            {
                ChangeState(mStates[(int)States.Damaged]);
            }
            else if(mIsDeath == false)
            {
                ChangeState(mStates[(int)States.Die]);
                StartCoroutine(CoroutineDie());

                int rand = Random.Range(1, 3);
                for (int i = 0; i < rand; ++i)
                    Instantiate(itemPrf, transform.position + Vector3.up * 2 + new Vector3(Random.Range(0f, 3f), 0f, Random.Range(0f, 3f)),
                        Quaternion.Euler(90f, 0f, 0f));
            }
        }
        mCurrState.Update();
    }

    public void ChangeState(State nextState)
    {
        if(mCurrState != null && nextState != mCurrState)
            mCurrState.Disable();
        mCurrState = nextState;
        mCurrState.Enable();
        StartCoroutine(mCurrState.Coroutine());
    }

    public abstract void SetState();

    public IEnumerator CoroutineDie()
    {
        yield return new WaitForSeconds(3f);

        gameObject.SetActive(false);
    }

    public void PullItem()
    {

        int rand = Random.Range(1, 3);
        for (int i = 0; i < rand; ++i)
            Instantiate(itemPrf, transform.position + Vector3.up * 2 + new Vector3(Random.Range(0f, 3f), 0f, Random.Range(0f, 3f)),
                Quaternion.Euler(90f, 0f, 0f));
    }
}