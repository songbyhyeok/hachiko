using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WalkOrc : MonoBehaviour
{
    [SerializeField]
    Orc mOrc;

    private void OnTriggerEnter(Collider other)
    {
        mOrc.ChangeState(mOrc.mStates[1]);
    }
}
