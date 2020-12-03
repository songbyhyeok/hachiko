using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPoolIG : MonoBehaviour
{
    public static ObjectPoolIG sInstance;

    [SerializeField]
    private GameObject mPoolingObjectPrefab;
    private GameObject mPoolingObjectFX;

    [SerializeField]
    private GameObject mPoolingObject_FirePrefab;
    private GameObject mPoolingObject_FireFX;

    [SerializeField]
    private GameObject mPoolingObject_IcePrefab;
    private GameObject mPoolingObject_IceFX;

    [SerializeField]
    private GameObject mPoolingObject_HealPrefab;
    private GameObject mPoolingObject_HealFX;

    Queue<Bullet> mPoolingObjectQueue = new Queue<Bullet>();
    Queue<Bullet_FireObj> mPooling_FireObjectQueue = new Queue<Bullet_FireObj>();
    Queue<Bullet_IceObj> mPooling_IceObjectQueue = new Queue<Bullet_IceObj>();
    Queue<Bullet_HealObj> mPooling_HealObjectQueue = new Queue<Bullet_HealObj>();

    private void Awake()
    {
        sInstance = this;

        Initialize(10);
        Initialize_FireObj(10);
        Initialize_IceObj(10);
        Initialize_HealObj(10);
    }

    private void Initialize(int initCount)
    {
        for (int i = 0; i < initCount; i++)
        {
            mPoolingObjectQueue.Enqueue(CreateNewObject());
        }
    }

    private void Initialize_FireObj(int initCount)
    {
        for (int i = 0; i < initCount; i++)
        {
            mPooling_FireObjectQueue.Enqueue(CreateNewFireObject());
        }
    }

    private void Initialize_IceObj(int initCount)
    {
        for (int i = 0; i < initCount; i++)
        {
            mPooling_IceObjectQueue.Enqueue(CreateNewIceObject());
        }
    }

    private void Initialize_HealObj(int initCount)
    {
        for (int i = 0; i < initCount; i++)
        {
            mPooling_HealObjectQueue.Enqueue(CreateNewHealObject());
        }
    }

    private Bullet CreateNewObject()
    {
        var newObj = Instantiate(mPoolingObjectPrefab).GetComponent<Bullet>();
        newObj.gameObject.SetActive(false);
       // newObj.transform.SetParent(transform);
        return newObj;

    }

    private Bullet_FireObj CreateNewFireObject()
    {
        var newFireObj = Instantiate(mPoolingObject_FirePrefab).GetComponent<Bullet_FireObj>();
        newFireObj.gameObject.SetActive(false);
        // newObj.transform.SetParent(transform);
        return newFireObj;

    }

    private Bullet_IceObj CreateNewIceObject()
    {
        var newIceObj = Instantiate(mPoolingObject_IcePrefab).GetComponent<Bullet_IceObj>();
        newIceObj.gameObject.SetActive(false);
        // newObj.transform.SetParent(transform);
        return newIceObj;

    }

    private Bullet_HealObj CreateNewHealObject()
    {
        var newHealObj = Instantiate(mPoolingObject_HealPrefab).GetComponent<Bullet_HealObj>();
        newHealObj.gameObject.SetActive(false);
        // newObj.transform.SetParent(transform);
        return newHealObj;

    }


    public static Bullet GetObject()
    {
        if(sInstance.mPoolingObjectQueue.Count > 0)
        {
            var obj = sInstance.mPoolingObjectQueue.Dequeue();
            obj.transform.SetParent(null);
            obj.gameObject.SetActive(true);
            return obj;
        }
        else
        {
            var newObj = sInstance.CreateNewObject();
            newObj.gameObject.SetActive(true);
            newObj.transform.SetParent(null);
            return newObj;
        }
    }

    public static Bullet_FireObj GetFireObject()
    {
        if (sInstance.mPooling_FireObjectQueue.Count > 0)
        {
            var obj = sInstance.mPooling_FireObjectQueue.Dequeue();
            obj.transform.SetParent(null);
            obj.gameObject.SetActive(true);
            return obj;
        }
        else
        {
            var newObj = sInstance.CreateNewFireObject();
            newObj.gameObject.SetActive(true);
            newObj.transform.SetParent(null);
            return newObj;
        }
    }

    public static Bullet_IceObj GetIceObject()
    {
        if (sInstance.mPooling_IceObjectQueue.Count > 0)
        {
            var obj = sInstance.mPooling_IceObjectQueue.Dequeue();
            obj.transform.SetParent(null);
            obj.gameObject.SetActive(true);
            return obj;
        }
        else
        {
            var newObj = sInstance.CreateNewIceObject();
            newObj.gameObject.SetActive(true);
            newObj.transform.SetParent(null);
            return newObj;
        }
    }

    public static Bullet_HealObj GetHealObject()
    {
        if (sInstance.mPooling_HealObjectQueue.Count > 0)
        {
            var obj = sInstance.mPooling_HealObjectQueue.Dequeue();
            obj.transform.SetParent(null);
            obj.gameObject.SetActive(true);
            return obj;
        }
        else
        {
            var newObj = sInstance.CreateNewHealObject();
            newObj.gameObject.SetActive(true);
            newObj.transform.SetParent(null);
            return newObj;
        }
    }

    public static void sReturnObject(Bullet obj)
    {
        obj.gameObject.SetActive(false);
       // obj.transform.SetParent(sInstance.transform);
        sInstance.mPoolingObjectQueue.Enqueue(obj);
    }

    public static void sReturnFireObject(Bullet_FireObj obj)
    {
        obj.gameObject.SetActive(false);
       // obj.transform.SetParent(sInstance.transform);
        sInstance.mPooling_FireObjectQueue.Enqueue(obj);
    }

    public static void sReturnIceObject(Bullet_IceObj obj)
    {
        obj.gameObject.SetActive(false);
        // obj.transform.SetParent(sInstance.transform);
        sInstance.mPooling_IceObjectQueue.Enqueue(obj);
    }

    public static void sReturnHealObject(Bullet_HealObj obj)
    {
        obj.gameObject.SetActive(false);
        // obj.transform.SetParent(sInstance.transform);
        sInstance.mPooling_HealObjectQueue.Enqueue(obj);
    }

}
