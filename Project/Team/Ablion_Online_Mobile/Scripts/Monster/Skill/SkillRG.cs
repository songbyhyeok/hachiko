using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillRG : MonoBehaviour
{
    [SerializeField]
    float mSpeed = 8f;

    void Start()
    {
        StartCoroutine(Disappear());
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(transform.forward * mSpeed * Time.deltaTime, Space.World);
    }

    public IEnumerator Disappear()
    {
        yield return new WaitForSeconds(3f);

        gameObject.SetActive(false);

        yield break;
    }
}
