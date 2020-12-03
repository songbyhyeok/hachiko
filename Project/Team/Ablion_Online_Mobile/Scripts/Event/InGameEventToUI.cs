using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class InGameEventToUI : Singleton<InGameEventToUI>
{
    public event System.Action<bool> EventDie;
    public event System.Action<float> EventHp;

    public void OnEventDie(bool die)
    {
        if (EventDie != null)
            EventDie(die);
    }

    public void OnEventReturnHp(float hp)
    {
        if (EventHp != null)
            EventHp(hp);
    }
}
