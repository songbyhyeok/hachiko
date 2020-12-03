using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class PlayerIG : MonoBehaviour
{
    [SerializeField]
    private GameObject attackPoint;

    Animation mAnim;
    public float mHp = 2f;
    public float mMaxHp = 2f;
    public int mSpeed = 10;
    private float mMove = 0f;

    private bool mIsIdle = false;
    private bool mIsWalk = false;
    private bool mIsAttack = false;
    private bool mIsFire = false;
    private bool mIsIce = false;
    private bool mIsHeal = false;
    public bool mIsDeath { get; private set; } = false;
    public bool mNextScene;
    private bool skill_true  = false;
    public bool skill_Use //프로퍼티
    {
        get { return skill_true; }
        set { skill_true = value; }
    }
    private GameObject monster;
    private GameObject nextPortal;
    
    void Start()
    {
        UIEventToInGame.Instance.EventStickMove += OnEventMove;
        UIEventToInGame.Instance.EventStickUp += OnEventStop;
        UIEventToInGame.Instance.EventAttackBtn += skillAttack;
        UIEventToInGame.Instance.EventFireSkillBtn += skillFire;
        UIEventToInGame.Instance.EventIceSkillBtn += skillIce;
        UIEventToInGame.Instance.EventHealSkillBtn += skillHeal;
        mAnim = GetComponent<Animation>();
        monster = GameObject.FindGameObjectWithTag("Enemy");
        if (SceneManager.GetActiveScene().name == "Field2")
        {
            nextPortal = GameObject.FindGameObjectWithTag("nextScene");
        }
        mIsIdle = true;

        mHp = mMaxHp;
        //mAnim.CrossFade("free", 0.2f);
    }

    private void FixedUpdate()
    {
        if (mHp == 0f)
            return;
    }

    void Update()
    {
        if(mIsIdle)
        {
            mAnim.CrossFade("free", 0.2f);

            //if (!mIsAttack)
            //    skillAttack(mIsAttack);
            //else if (mIsFire)
            //    skillFire(mIsFire);
            //else if (mIsIce)
            //    skillIce(mIsIce);
            //else if (mIsHeal)
            //    skillHeal(mIsHeal);
            //else
            //    mAnim.CrossFade("free", 0.2f);
        }
        skillAttack(mIsAttack);
        skillFire(mIsFire);
        skillIce(mIsIce);
        //NearEnemyAttack();

        if (mIsWalk)
        {
            mAnim.CrossFade("walk", 0.2f);
        }

        if (mHp == 0f)
        {
            mIsDeath = true;
        }

        if(mIsDeath)
        {
            die();
        }
        
    }

    private void skillAttack(bool attack)
    {
        if (attack)
        {
            mIsIdle = false;
            mAnim.CrossFade("attack", 0.2f);
            var bullet = ObjectPoolIG.GetObject();
            bullet.transform.position = attackPoint.transform.position;

            bullet.Shoot(transform.forward * 10f);
        }
    }
    

    public void OnAnimEventAttackEnd()
    {
        mIsIdle = true;
    }

    public void OnEventSkillEnd()
    {
        mIsIdle = true;
    }

    private void skillFire(bool skillfire)
    {
        if (skillfire)
        {
            StartCoroutine(CoroutinSkill_Fire());
        }
    }
    private void skillIce(bool skillice)
    {
        if (skillice)
        {
            StartCoroutine(CoroutinSkill_Ice());
        }
    }
    private void skillHeal(bool skillheal)
    {
        if (skillheal)
        {
            StartCoroutine(CoroutinSkill_Heal());
        }
    }

    private void die()
    {
        bool t = true;
        if (t)
        {
            mAnim.CrossFade("death", 0.2f);
            InGameEventToUI.Instance.OnEventDie(mIsDeath);
            //게임 재시작
            //Invoke("DieFinish", 3f);
            t = false;
        }
        else
            Invoke("DieF", 10f);
    }
    private void DieFinish()
    {
        mAnim.Stop("death");
    }
    private void DieF()
    {
        SceneManager.LoadScene("Field2");
    }

    private void reStartGame()
    {
        //게임 재시작
        //SceneManager.LoadScene();
    }
    private void OnDestroy()
    {
        UIEventToInGame.Instance.EventStickMove -= OnEventMove;
        UIEventToInGame.Instance.EventStickUp -= OnEventStop;
        UIEventToInGame.Instance.EventFireSkillBtn -= skillFire;
        UIEventToInGame.Instance.EventIceSkillBtn -= skillIce;
        UIEventToInGame.Instance.EventHealSkillBtn -= skillHeal;
    }

    void OnEventMove(Vector2 direction)
    {
        Vector3 worldDirection = new Vector3(direction.x, 0f, direction.y);
        transform.Translate(worldDirection.normalized * mSpeed * Time.deltaTime, Space.World);
        mIsWalk = true;

        if(direction.x != 0 || direction.y != 0)
        {
            Quaternion q = Quaternion.LookRotation(worldDirection);
            float y = q.eulerAngles.y;
            transform.rotation = Quaternion.Euler(new Vector3(0, y, 0));
        }
    }

    void OnEventStop(bool walk)
    {
        if (walk)
        {
            mIsIdle = false;
            mIsWalk = true;
        }
        else if (walk != true)
        {
            mIsWalk = false;
            mIsIdle = true;
        }
    }

    IEnumerator CoroutinSkill_Fire()
    {
        Vector3 monsVec;
        mIsIdle = false;
        mAnim.CrossFade("skill", 0.2f);
        var skill_FireBox = ObjectPoolIG.GetFireObject();
        skill_FireBox.transform.position = transform.Find("Skill_Fire").position;
        monsVec = skill_FireBox.transform.position;
        //NearEnemyAttack(out monsVec);
        skill_FireBox.Shoot(transform.forward * 10f);
        skill_true = true;
       
        yield return new WaitForSeconds(3f);
    }

    IEnumerator CoroutinSkill_Ice()
    {
        mIsIdle = false;
        mAnim.CrossFade("skill", 0.2f);
        var skill_IceBox = ObjectPoolIG.GetIceObject();
        skill_IceBox.transform.position = transform.Find("Skill_Ice").position;
        skill_IceBox.Shoot(transform.position + transform.forward * 10f);

        yield return new WaitForSeconds(3f);

    }

    IEnumerator CoroutinSkill_Heal()
    {
        mIsIdle = false;
        mAnim.CrossFade("skill", 0.2f);
        var skill_HealBox = ObjectPoolIG.GetHealObject();
        skill_HealBox.transform.position = transform.Find("Skill_Heal").position;
        skill_HealBox.Shoot(transform.position + transform.forward * 10f);
      
        yield return new WaitForSeconds(3f);
      
    }
    
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject == nextPortal)
        {
            mNextScene = true;
            Debug.Log(mNextScene);
        }
    }

    //private void OnCollisionEnter(Collision collision)
    //{

    //    if (collision.gameObject == monster)
    //    { 
    //        mHp -= 1;
    //        Debug.Log("hp:" + mHp);
    //        if(mHp == 0)
    //        {
    //            mIsDeath = true;
    //        }
    //    }
    //}

    public void NearEnemyAttack(out Vector3 monsVec)
    {
        monsVec = new Vector3(transform.position.x +10, transform.position.y, transform.position.z + 1);
        //주변에 있는 모든 적을 추출해서 배열에 저장 (원점, 반경, 레이어)
        Collider[] colls = Physics.OverlapSphere(monsVec, 300f, 1 << 10);

        for (int i = 0; i < colls.Length; i++) //자기자신포함
        {
            MonsterAI mon = colls[i].GetComponent<MonsterAI>();

            if (mon != null && !mon.mIsDeath)
            {
                var bullet = ObjectPoolIG.GetObject();
                bullet.transform.position = mon.transform.position;
            }
            monsVec = colls[i].transform.position;
        }
    }

    public bool CheckAllMonsterDie()
    {
        Collider[] colliders = Physics.OverlapSphere(transform.position, 20f, 1 << 10);

        for (int i = 0; i < colliders.Length; ++i)
        {

            MonsterAI mob = colliders[i].GetComponent<MonsterAI>();

            if (mob != null && !mob.mIsDeath)
            {
                return false;
            }
        }

        return true;
    }
}

