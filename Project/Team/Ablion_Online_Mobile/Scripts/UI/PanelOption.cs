using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class PanelOption : MonoBehaviour, IPointerDownHandler
{
    private GameObject Inventroy;

    private void Awake()
    {
        Inventroy = GameObject.Find("Panel_Inventory");
    }

    public void Open_Inventory()
    {
        Inventroy.SetActive(true);
    }

    private void Open_Quest()
    {

    }

    private void Open_RoyalShop()
    {

    }

    public void OnPointerDown(PointerEventData eventData)
    {
    }
}
