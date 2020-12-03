using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class CsPanelInventory : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
    [SerializeField] int slotNum;
    [SerializeField] GameObject mSlotPrefabs;
    [SerializeField] List<GameObject> testWeapon, testArmor;

    GridLayoutGroup gridLayoutGroup;
    GraphicRaycaster mGraphicRaycaster;

    List<GameObject> slotList = new List<GameObject>();
    List<RaycastResult> result = new List<RaycastResult>();

    Button mCancel;
    GameObject selectedOB = null;

    bool isDrag = false, isEmpty = false;

    private void Awake()
    {
        gridLayoutGroup = transform.Find("Background/GridCover/Grid").GetComponent<GridLayoutGroup>();

        for (int i = 0; i < slotNum; i++)
        {
            slotList.Add(Instantiate(mSlotPrefabs, new Vector2(0, 0), Quaternion.identity));
            slotList[i].transform.SetParent(transform.Find("Background/GridCover/Grid"));
            slotList[i].name = "Slot" + (i+1).ToString();
            slotList[i].tag = "Slot";
        }

        mCancel = transform.Find("Background/Cancel").GetComponent<Button>();
        mCancel.onClick.AddListener(RemoteControl);

        for (int i = 0; i < testWeapon.Count + testArmor.Count; i++)
        {
            if (i < testWeapon.Count)
            {
                slotList[i].tag = "HasChild";

                testWeapon[i] = Instantiate(testWeapon[i], new Vector2(slotList[i].transform.position.x, slotList[0].transform.position.y), Quaternion.identity);
                testWeapon[i].layer = LayerMask.NameToLayer("Equipment");
                testWeapon[i].transform.SetParent(slotList[i].transform);
                testWeapon[i].GetComponent<RectTransform>().sizeDelta = gridLayoutGroup.cellSize;
            }

            else if (i < testWeapon.Count + testArmor.Count)
            {
                slotList[i].tag = "HasChild";

                testArmor[i - testWeapon.Count] = Instantiate(testArmor[i - testWeapon.Count], new Vector2(slotList[i].transform.position.x, slotList[0].transform.position.y), Quaternion.identity);
                testArmor[i - testWeapon.Count].layer = LayerMask.NameToLayer("Equipment");
                testArmor[i - testWeapon.Count].transform.SetParent(slotList[i].transform);
                testArmor[i - testWeapon.Count].GetComponent<RectTransform>().sizeDelta = gridLayoutGroup.cellSize;
            }
        }

        mGraphicRaycaster = GameObject.Find("Canvas").GetComponent<GraphicRaycaster>();
    }

    public void RemoteControl()
    {
        if (this.gameObject.active)
            this.gameObject.SetActive(false);
        else
            this.gameObject.SetActive(true);
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        if (!isDrag)
        {
            if (eventData.pointerCurrentRaycast.gameObject.transform.parent.transform.CompareTag("HasChild") ||
                                             eventData.pointerCurrentRaycast.gameObject.CompareTag("Weapon") ||
                                             eventData.pointerCurrentRaycast.gameObject.CompareTag("Helmet") ||
                                              eventData.pointerCurrentRaycast.gameObject.CompareTag("Cloth") ||
                                              eventData.pointerCurrentRaycast.gameObject.CompareTag("Pants"))
            {
                eventData.pointerCurrentRaycast.gameObject.transform.position = eventData.position;
                selectedOB = eventData.pointerCurrentRaycast.gameObject;

                isDrag = true;
            }

            else if (eventData.pointerCurrentRaycast.gameObject.transform.CompareTag("Slot"))
                    isEmpty = true;
        }
    }

    public void OnDrag(PointerEventData eventData)
    {
        if (isDrag)
            selectedOB.transform.position = eventData.position;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        isDrag = false;

        mGraphicRaycaster.Raycast(eventData, result);
        if (selectedOB != null)
            for (int i = 0; i < result.Count; i++)
            {
                if (result[i].gameObject.transform.parent.CompareTag("HasChild") && result[i].gameObject != selectedOB)
                {
                    bool isChange = false;

                    if (selectedOB.transform.parent.CompareTag("EquipmentFull") && selectedOB.tag == result[i].gameObject.tag ||
                        selectedOB.transform.parent.CompareTag("HasChild"))
                        isChange = true;

                    if (isChange)
                    {
                        GameObject tempParent = result[i].gameObject.transform.parent.gameObject;
                        result[i].gameObject.transform.SetParent(selectedOB.transform.parent.transform);
                        result[i].gameObject.transform.position = selectedOB.transform.parent.position;

                        selectedOB.transform.SetParent(tempParent.transform);
                        selectedOB.transform.position = tempParent.transform.position;
                    }

                    else
                        selectedOB.transform.position = selectedOB.transform.parent.position;

                    break;
                }

                else if (result[i].gameObject.transform.CompareTag("Slot"))
                {
                    if (isEmpty)
                    {
                        isEmpty = false;

                        break;
                    }

                    else if (selectedOB.transform.parent.CompareTag("HasChild") ||
                             selectedOB.transform.parent.CompareTag("EquipmentFull"))
                    {
                        GameObject tempParent = selectedOB.transform.parent.gameObject;

                        result[i].gameObject.transform.tag = "HasChild";
                        selectedOB.transform.SetParent(result[i].gameObject.transform);
                        selectedOB.transform.position = result[i].gameObject.transform.position;

                        if (tempParent.CompareTag("HasChild"))
                            tempParent.tag = "Slot";

                        else if (tempParent.CompareTag("EquipmentFull"))
                            tempParent.tag = "EquipmentEmpty";

                        break;
                    }
                }

                else if (result[i].gameObject.CompareTag("EquipmentEmpty") ||
                         result[i].gameObject.CompareTag("EquipmentFull"))
                {
                    if (selectedOB.CompareTag("Helmet") && result[i].gameObject.name == "helmet" ||
                        selectedOB.CompareTag("Cloth") && result[i].gameObject.name == "cloth" ||
                        selectedOB.CompareTag("Pants") && result[i].gameObject.name == "pants" ||
                        selectedOB.CompareTag("Weapon") && result[i].gameObject.name == "left" ||
                        selectedOB.CompareTag("Weapon") && result[i].gameObject.name == "right"
                        )
                    {
                        GameObject tempParent = selectedOB.transform.parent.gameObject;

                        selectedOB.transform.SetParent(result[i].gameObject.transform);
                        selectedOB.transform.position = result[i].gameObject.transform.position;

                        if (result[i].gameObject.CompareTag("EquipmentEmpty"))
                        {
                            result[i].gameObject.tag = "EquipmentFull";

                            if (tempParent.CompareTag("HasChild"))
                                tempParent.tag = "Slot";

                            else if (tempParent.CompareTag("EquipmentFull"))
                                tempParent.tag = "EquipmentEmpty";
                        }

                        else if (result[i].gameObject.CompareTag("EquipmentFull"))
                        {
                            GameObject tempTarget = result[i].gameObject.transform.GetChild(0).gameObject;
                            result[i].gameObject.transform.GetChild(0).SetParent(tempParent.transform);
                            tempTarget.transform.position = tempParent.transform.position;
                        }

                        break;
                    }
                }

                else if (i == result.Count - 1)
                    selectedOB.transform.position = selectedOB.transform.parent.position;
            }

        result.Clear();
    }
}
