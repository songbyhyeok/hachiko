using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_HealObj : MonoBehaviour
{
    private Vector3 mDirection;
    public GameObject fx_obj;
    public GameObject explosionHeal;


    public void Shoot(Vector3 direction)
    {
        this.mDirection = direction * Time.deltaTime;
        fx_obj = Instantiate(explosionHeal, transform.position, transform.rotation);
        Invoke("DestroyBullet", 5f);
    }

    public void DestroyBullet()
    {
        ObjectPoolIG.sReturnHealObject(this);
        Destroy(fx_obj);
    }

   
}
