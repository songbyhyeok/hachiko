using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class TouchMgr : MonoBehaviour
{
    EventTrigger mForwardET, mBackET, mLeftET, mRightET;
    EventTrigger mNorthWestET, mNorthEastET, mSouthWestET, mSouthEastET;

    Vector3 currDir = Vector3.zero;
    float moveSpeed = 5f;

    private void Awake()
    {
        // Entry PointerUp Vector3 Zero
        {
            EventTrigger.Entry entry_PtUp = new EventTrigger.Entry();
            entry_PtUp.eventID = EventTriggerType.PointerUp;
            entry_PtUp.callback.AddListener((data) => { OnPointerUp((BaseEventData)data); });

            // Forward
            {
                EventTrigger.Entry forward_PtDown = new EventTrigger.Entry();
                forward_PtDown.eventID = EventTriggerType.PointerDown;
                forward_PtDown.callback.AddListener((data) => { VerticalButton((BaseEventData)data, (bool)true); });

                mForwardET = transform.Find("Forward").gameObject.AddComponent<EventTrigger>();
                mForwardET.triggers.Add(forward_PtDown);
                mForwardET.triggers.Add(entry_PtUp);

                Image forwardImg = transform.Find("Forward").gameObject.GetComponent<Image>();
                forwardImg.sprite = Resources.Load<Sprite>("Use Images/Direction") as Sprite;
            }

            // Back
            {
                EventTrigger.Entry back_PtDown = new EventTrigger.Entry();
                back_PtDown.eventID = EventTriggerType.PointerDown;
                back_PtDown.callback.AddListener((data) => { VerticalButton((BaseEventData)data, (bool)false); });

                mBackET = transform.Find("Back").gameObject.AddComponent<EventTrigger>();
                mBackET.triggers.Add(back_PtDown);
                mBackET.triggers.Add(entry_PtUp);

                Image backImg = transform.Find("Back").gameObject.GetComponent<Image>();
                backImg.sprite = Resources.Load<Sprite>("Use Images/Direction") as Sprite;
            }

            // Left
            {
                EventTrigger.Entry left_PtDown = new EventTrigger.Entry();
                left_PtDown.eventID = EventTriggerType.PointerDown;
                left_PtDown.callback.AddListener((data) => { horizontalButton((BaseEventData)data, (bool)false); });

                mLeftET = transform.Find("Left").gameObject.AddComponent<EventTrigger>();
                mLeftET.triggers.Add(left_PtDown);
                mLeftET.triggers.Add(entry_PtUp);

                Image leftImg = transform.Find("Left").gameObject.GetComponent<Image>();
                leftImg.sprite = Resources.Load<Sprite>("Use Images/Direction") as Sprite;
            }

            // Right
            {
                EventTrigger.Entry right_PtDown = new EventTrigger.Entry();
                right_PtDown.eventID = EventTriggerType.PointerDown;
                right_PtDown.callback.AddListener((data) => { horizontalButton((BaseEventData)data, (bool)true); });

                mRightET = transform.Find("Right").gameObject.AddComponent<EventTrigger>();
                mRightET.triggers.Add(right_PtDown);
                mRightET.triggers.Add(entry_PtUp);

                Image rightImg = transform.Find("Right").gameObject.GetComponent<Image>();
                rightImg.sprite = Resources.Load<Sprite>("Use Images/Direction") as Sprite;
            }

            {
                mNorthWestET = transform.Find("NorthWest").gameObject.AddComponent<EventTrigger>();
                mNorthWestET.triggers.Add(entry_PtUp);

                Image northWestImg = transform.Find("NorthWest").gameObject.GetComponent<Image>();
                northWestImg.sprite = Resources.Load<Sprite>("Use Images/Diagonal") as Sprite;
            }

            {
                mNorthEastET = transform.Find("NorthEast").gameObject.AddComponent<EventTrigger>();
                mNorthEastET.triggers.Add(entry_PtUp);

                Image northEastImg = transform.Find("NorthEast").gameObject.GetComponent<Image>();
                northEastImg.sprite = Resources.Load<Sprite>("Use Images/Diagonal") as Sprite;
                northEastImg.rectTransform.rotation = Quaternion.Euler(new Vector3(0, 180f, 0));
                northEastImg.rectTransform.Translate(new Vector3(85f, 0, 0));
            }

            {
                mSouthWestET = transform.Find("SouthWest").gameObject.AddComponent<EventTrigger>();
                mSouthWestET.triggers.Add(entry_PtUp);

                Image southWestImg = transform.Find("SouthWest").gameObject.GetComponent<Image>();
                southWestImg.sprite = Resources.Load<Sprite>("Use Images/Diagonal") as Sprite;
                southWestImg.rectTransform.rotation = Quaternion.Euler(new Vector3(0, 0, 90));
                southWestImg.rectTransform.Translate(new Vector3(85f, 0, 0));
            }

            { 
                mSouthEastET = transform.Find("SouthEast").gameObject.AddComponent<EventTrigger>();
                mSouthEastET.triggers.Add(entry_PtUp);

                Image southEastImg = transform.Find("SouthEast").gameObject.GetComponent<Image>();
                southEastImg.sprite = Resources.Load<Sprite>("Use Images/Diagonal") as Sprite;
                southEastImg.rectTransform.rotation = Quaternion.Euler(new Vector3(0, 0, -180.0f));
                southEastImg.rectTransform.position = new Vector3(-85.0f, 85.0f, 0);
            }
        }
    }

    void VerticalButton(BaseEventData data, bool tf)
    {
        if (tf)
            currDir = Vector3.forward;
        else
            currDir = Vector3.back;
    }

    void horizontalButton(BaseEventData data, bool tf)
    {
        if (tf)
            currDir = Vector3.right;
        else
            currDir = Vector3.left;
    }

    void OnPointerUp(BaseEventData data)
    {
        currDir = Vector3.zero;
    }

}
