using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    private Vector3 mDirection;
    private int speed = 1;
    public GameObject explosion;
    public GameObject fx_obj;

    private GameObject eventTrigger;
    private GameObject[] apperaGoblin;
    private GameObject[] apperaGoblin1;

    public Transform EnemyTr;
    public Rigidbody ballrigid;
    public float turn;
    public float ballVelocity;


    public void Shoot(Vector3 direction)
    {
        this.mDirection = direction * speed * Time.deltaTime;
        fx_obj = Instantiate(explosion, transform.position, Quaternion.LookRotation(direction));

        Invoke("DestroyBullet", 5f);        
    }

    public void DestroyBullet()
    {
        ObjectPoolIG.sReturnObject(this);
        Destroy(fx_obj);
    }

    private void Start()
    {
        eventTrigger = GameObject.Find("EventTrigger");
        apperaGoblin = eventTrigger.transform.GetChild(0).GetComponent<AppearY_Goblin>().mP_YellowGoblins;
        apperaGoblin1 = eventTrigger.transform.GetChild(1).GetComponent<AppearY_Goblin>().mP_YellowGoblins;
    }

    private void FixedUpdate()
    {
        ballrigid.velocity = transform.forward * ballVelocity;
        var ballTargetRotation = Quaternion.LookRotation(EnemyTr.position + new Vector3(0, 0.8f) - transform.position);
        ballrigid.MoveRotation(Quaternion.RotateTowards(transform.rotation, ballTargetRotation, turn));
    }

    void Update()
    {
        //transform.Translate(mDirection);
    }

    private void OnCollisionEnter(Collision collision)
    {
        foreach (GameObject YelloMon in apperaGoblin)
        {
            EnemyTr = YelloMon.GetComponent<YellowGoblin>().transform;

            if (collision.gameObject.tag == YelloMon.tag)
            {
                if (YelloMon.GetComponent<YellowGoblin>().mHp == 0)
                {
                    YelloMon.GetComponent<YellowGoblin>().Die();
                }
                else
                {
                    YelloMon.GetComponent<YellowGoblin>().mHp -= 1;
                }
            }


        }
    }



}