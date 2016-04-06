﻿using UnityEngine;
using System.Collections;
using System;

public class CannonMovement : MonoBehaviour, IMoveable
{
    
    public float m_turnSpeed = 1.0f;

    [SerializeField]
    private Transform cannon;   // HACK: How should I handle accessibility for sub-comps?
    private float axisInput;
    

    public Vector3 position
    {
        get
        {
            return cannon.position;
        }
    }

    public Vector3 forward
    {
        get
        {
            return cannon.forward;
        }
    }

    public void MoveForward(float value)
    {
        return;
    }

    public void TurnRight(float value)
    {
        axisInput = Mathf.Clamp(value, -1.0f, 1.0f);
    }

    public void FixedUpdate()
    {
        cannon.Rotate(transform.up, axisInput * m_turnSpeed);
    }
}