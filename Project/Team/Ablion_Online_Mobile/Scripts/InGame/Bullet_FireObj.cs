using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_FireObj : MonoBehaviour
{
    private Vector3 mDirection;
    public GameObject fx_obj;
    public GameObject explosionFire;
    private GameObject monster;
    private PlayerIG player;

    private GameObject eventTrigger;
    private GameObject[] apperaGoblin;
    private GameObject[] apperaGoblin1;

    
    

    public void Shoot(Vector3 direction)
    {
        this.mDirection = direction * Time.deltaTime;
        //transform.LookAt(direction);
        fx_obj = Instantiate(explosionFire, transform.position, transform.rotation);
        Invoke("DestroyBullet", 5f);
    }

    public void DestroyBullet()
    {
        ObjectPoolIG.sReturnFireObject(this);
        Destroy(fx_obj);
    }

    private void Start()
    {
        monster = GameObject.FindGameObjectWithTag("Enemy");
        player = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerIG>();
        //eventTrigger = GameObject.Find("EventTrigger");
        //apperaGoblin = eventTrigger.transform.GetChild(0).GetComponent<AppearY_Goblin>().mP_YellowGoblins;
        //apperaGoblin1 = eventTrigger.transform.GetChild(1).GetComponent<AppearY_Goblin>().mP_YellowGoblins;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == 10)
        {
            MonsterAI mob = other.gameObject.GetComponent<MonsterAI>();

            if (mob != null && !mob.mIsDeath)
            {
                mob.mHp--;

                if (mob.mHp > 0)
                {
                    mob.ChangeState(mob.mStates[(int)States.Damaged]);
                }

                else
                {
                    mob.ChangeState(mob.mStates[(int)States.Die]);
                    StartCoroutine(mob.CoroutineDie());

                    mob.PullItem();
                }
            }

        }

        //foreach (GameObject YelloMon in apperaGoblin)
        //{
        //    if (collision.gameObject.tag == YelloMon.tag)
        //    {
        //        if (YelloMon.GetComponent<YellowGoblin>().mHp == 0)
        //        {
        //            YelloMon.GetComponent<YellowGoblin>().Die();
        //        }
        //        else
        //        {
        //            YelloMon.GetComponent<YellowGoblin>().mHp -= 1;
        //        }
        //    }

            
        //}
        //foreach (GameObject YelloMon in apperaGoblin1)
        //{
        //    if (collision.gameObject.tag == YelloMon.tag)
        //    {
        //        if (YelloMon.GetComponent<YellowGoblin>().mHp == 0)
        //        {
        //            YelloMon.GetComponent<YellowGoblin>().Die();
        //        }
        //        else
        //        {
        //            YelloMon.GetComponent<YellowGoblin>().mHp -= 1;
        //        }
        //    }


        //}
    }

}
