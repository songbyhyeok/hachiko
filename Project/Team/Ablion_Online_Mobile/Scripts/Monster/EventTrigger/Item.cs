using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    Transform mTargetPosition = null;
    [SerializeField]
    float mSpeed = 2f;

    void Start()
    {
        StartCoroutine(GoToPlayer());
    }

    void Update()
    {
        if (mTargetPosition == null)
            return;

        transform.Translate((mTargetPosition.transform.position - transform.position)  * mSpeed * Time.deltaTime, Space.World);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer != 9)
            return;

        gameObject.SetActive(false);
    }

    IEnumerator GoToPlayer()
    {
        Collider[] colliders = Physics.OverlapSphere(transform.position, 50f);

        for (int i = 0; i < colliders.Length; ++i)
        {

            PlayerIG player = colliders[i].GetComponent<PlayerIG>();

            do
            {
                yield return new WaitForSeconds(1f);

            } while (!player.CheckAllMonsterDie());

            if (player != null && !player.mIsDeath)
            {
                mTargetPosition = player.transform;
                yield break;
            }
        }
    }
}
