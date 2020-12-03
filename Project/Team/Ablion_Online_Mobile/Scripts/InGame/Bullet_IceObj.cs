using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_IceObj : MonoBehaviour
{
    private Vector3 mDirection;
    public GameObject fx_obj;
    public GameObject explosionIce;

    public void Shoot(Vector3 direction)
    {
        this.mDirection = direction * Time.deltaTime;
        fx_obj = Instantiate(explosionIce, transform.position, transform.rotation);
        Invoke("DestroyBullet", 5f);
    }

    public void DestroyBullet()
    {
        ObjectPoolIG.sReturnIceObject(this);
        Destroy(fx_obj);
    }

}
