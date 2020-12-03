using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoundaryTree : MonoBehaviour
{
    [SerializeField]
    PlayerIG mPlayer;

    private void OnTriggerEnter(Collider other)
    {
        
    }

    void OnEventBoundary(Vector2 direction)
    {
        if (direction.y > 0f)
        {
            Debug.Log(direction.y);
            Vector3 worldDirection = new Vector3(direction.x, 0f, direction.y);
            mPlayer.transform.Translate(-worldDirection.normalized * mPlayer.mSpeed * Time.deltaTime, Space.World);
        }
    }
}
