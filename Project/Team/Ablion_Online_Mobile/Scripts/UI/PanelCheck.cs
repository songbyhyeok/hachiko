using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PanelCheck : MonoBehaviour
{
    private GameObject Ad_interface;
    private GameObject Shop_interface;
    private GameObject Option_interface;

    private void Awake()
    {
        Ad_interface = GameObject.Find("Ad");
        Shop_interface = GameObject.Find("RoyalShop");
        Option_interface = GameObject.FindWithTag("Option");

        Ad_interface.SetActive(true);
        Shop_interface.SetActive(true);
    }


}
