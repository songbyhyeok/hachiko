using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScr : MonoBehaviour
{
    Animator playerAnimator;
    Transform target;
    Vector3 targetDirection;
    float targetDistance;

    [SerializeField] float speed = 5f, zoomSpeed = 0f, zoomMax = 0f, zoomMin = 0f;

    string currMode = "null";
    bool zoomMode = true;

    public bool UseZoom_P
    {
        set { zoomMode = value; }
    }

    private void Awake()
    {
        target = GameObject.Find("Player").GetComponent<Transform>();
        playerAnimator = GameObject.Find("Player").GetComponent<Animator>();
        
        CurrMode();
    }

    private void LateUpdate()
    {
        Zoom();
        Move();

        if (!zoomMode)
        {
            if (currMode == "QuarterView")
                QuarterViewUpdate();
            else if (currMode == "TopView")
                TopViewUpdate();
        }
    }

    public void CurrMode(string currName = "QuarterView")
    {
        currMode = currName;
        if (currMode == "QuarterView")
            QuarterViewInit("Player");
        else if (currMode == "TopView")
            TopViewInit("Player");

        target = GameObject.Find("Player").GetComponent<Transform>();
        targetDistance = Vector3.Magnitude(target.position - transform.position);
        targetDirection = Vector3.Normalize(target.position - transform.position);
    }

    void QuarterViewInit(string targetName)
    {
        transform.position = new Vector3(target.position.x, 9.72f, target.position.z - 10.79f);
        transform.rotation = Quaternion.Euler(new Vector3(37.29f, 0.0f, 0.0f));
    }

    void TopViewInit(string targetName)
    {
        transform.position = new Vector3(target.position.x, 14.52f, target.position.z);
        transform.rotation = Quaternion.Euler(new Vector3(85.0f, 0.0f, 0.0f));
    }

    void QuarterViewUpdate()
    {
        Vector3 followPoint = target.position - targetDirection * targetDistance;
        //Debug.Log("카메라" + transform.position);
        //Debug.Log("follow point" + followPoint);
        transform.position = Vector3.Lerp(transform.position, followPoint, speed * Time.deltaTime);
        //Debug.Log("결과물" + transform.position);
    }

    void TopViewUpdate()
    {
        Vector3 followPoint = target.position - targetDirection * targetDistance;
        transform.position = Vector3.Lerp(transform.position, followPoint, speed * Time.deltaTime);
    }

    void Move()
    {
        if (Input.GetMouseButton(2))
        {
            float posX = Input.GetAxis("Mouse X");
            float posZ = Input.GetAxis("Mouse Y");
            transform.position += new Vector3(posX, 0, posZ);
        }
    }

    void Zoom()
    {
        float zoomDirection = Input.GetAxis("Mouse ScrollWheel");
        if (transform.position.y <= zoomMax && zoomDirection > 0)
            return;
        if (transform.position.y >= zoomMin && zoomDirection < 0)
            return;
        transform.position += transform.forward * zoomDirection * zoomSpeed;
    }

}
