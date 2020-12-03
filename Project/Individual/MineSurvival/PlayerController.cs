using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private enum Behaviour { Arise, Idle, Walk, Punch }

    [SerializeField] float moveSpeed = 0f;
    Animator animator;
    CameraScr camera;

    private void Awake()
    {
        animator = GetComponent<Animator>();
        animator.SetInteger("State", (int)Behaviour.Arise);
        
        camera = GameObject.Find("Main Camera").GetComponent<CameraScr>();

        JoystickMgr jsMgr = GameObject.Find("PanelJoystick").GetComponent<JoystickMgr>();
        jsMgr.eventStickDown += OnStickDown;
        jsMgr.eventStickUp += OnStickUp;

        ButtonScr buttonScr = GameObject.Find("PanelUtility").GetComponent<ButtonScr>();
        buttonScr.eventPunch += PunchAnim;
    }

    void OnStickDown(Vector2 stickDirectionPos, float amount)
    {
        Vector3 worldDiectionPos = new Vector3(stickDirectionPos.x, 0f, stickDirectionPos.y);

        Vector3 cameraToDir = Camera.main.transform.TransformDirection(worldDiectionPos);
        cameraToDir.y = 0f;
        cameraToDir = cameraToDir.normalized;

        if (animator.GetInteger("State") != (int)Behaviour.Arise)
        {
            transform.LookAt(transform.position + cameraToDir * 0.5f);
            transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime, Space.Self);

            animator.SetInteger("State", (int)Behaviour.Walk);
        }

        camera.UseZoom_P = false;
    }

    void OnStickUp()
    {
        if (animator.GetInteger("State") != (int)Behaviour.Arise)
            animator.SetInteger("State", (int)Behaviour.Idle);

        camera.UseZoom_P = true;
    }

    void PunchAnim()
    {
        animator.SetInteger("State", (int)Behaviour.Punch);
    }

    void EndAnim()
    {
        animator.SetInteger("State", (int)Behaviour.Idle);
    }
}
