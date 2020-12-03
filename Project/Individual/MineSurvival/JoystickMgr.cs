using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class JoystickMgr : MonoBehaviour, IPointerDownHandler, IDragHandler, IPointerUpHandler
{
    public delegate void OnStickDown(Vector2 direction, float distance);
    public delegate void OnStickUp();

    public event OnStickDown eventStickDown;
    public event OnStickUp eventStickUp;

    RectTransform mOutlineRT, mCenterRT, mHandleRT, mLineRT;

    [SerializeField] float maxDistance, lineStroke = 3;

    bool isInputExecute;

    private void Awake()
    {
        mOutlineRT = transform.Find("Outline").GetComponent<RectTransform>();
        mCenterRT = transform.Find("Center").GetComponent<RectTransform>();
        mHandleRT = transform.Find("Handle").GetComponent<RectTransform>();
        mLineRT = transform.Find("Line").GetComponent<RectTransform>();

        maxDistance = mOutlineRT.rect.width * 0.5f;

        isInputExecute = false;
    }

    private void Update()
    {
        if (isInputExecute)
        {
            Vector2 dirPos;
            float distance;
            GetInputInf(out dirPos, out distance);
            eventStickDown(dirPos, distance);
        }
    }

    public void OnDrag(PointerEventData eventData)
    {
        UpdataJoystick(eventData);
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        mLineRT.gameObject.SetActive(true);
        UpdataJoystick(eventData);
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        isInputExecute = false;

        mLineRT.gameObject.SetActive(false);
        ResetJoystick();
        eventStickUp();
    }

    void GetInputInf(out Vector2 DirectionPos, out float distance)
    {
        Vector3 distanceVec3 = mHandleRT.position - mCenterRT.position;
        DirectionPos = new Vector2(distanceVec3.x, distanceVec3.y);
        distance = distanceVec3.magnitude;
    }

    void UpdataJoystick(PointerEventData eventData = null)
    {
        isInputExecute = true;

        if (eventData != null)
            mHandleRT.position = eventData.position;

        float jsDistance = Vector3.Magnitude(mHandleRT.position - mCenterRT.position);
        Vector3 jsNor = Vector3.Normalize(mHandleRT.position - mCenterRT.position);

        if (jsDistance > maxDistance)
            mHandleRT.position = mCenterRT.position + jsNor * maxDistance;

        // Line Update
        {
            jsDistance = jsDistance > maxDistance ? maxDistance : jsDistance;
            mLineRT.sizeDelta = new Vector2(jsDistance, lineStroke);

            float theta = Mathf.Acos(jsNor.x);
            if (jsNor.y < 0)
                theta = Mathf.PI - theta;

            mLineRT.eulerAngles = new Vector3(0f, 0f, theta * Mathf.Rad2Deg);
            mLineRT.position = mCenterRT.position + jsNor * (jsDistance * 0.5f);
        }
    }

    void ResetJoystick()
    {
        mHandleRT.position = mCenterRT.position;
        mLineRT.position = mCenterRT.position;
    }
}
