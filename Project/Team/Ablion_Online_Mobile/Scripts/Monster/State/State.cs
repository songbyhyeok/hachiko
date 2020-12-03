using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class State
{
    protected Transform mTransform;
    protected MonsterAI mMonsterAI;
    protected Animator mMonsterAnimator;


    public virtual void Awake(GameObject monster)
    {
        this.mTransform = monster.transform;
        this.mMonsterAI = monster.GetComponent<MonsterAI>();
        this.mMonsterAnimator = monster.GetComponent<Animator>();
    }

    public abstract void Enable();

    public abstract void Update();

    public abstract IEnumerator Coroutine();

    public abstract void Disable();

}
