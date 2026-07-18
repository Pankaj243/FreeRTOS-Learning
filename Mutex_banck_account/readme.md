# FreeRTOS Mutex - Bank Account

## Description

This project demonstrates mutual exclusion using a FreeRTOS mutex.

Three tasks are created

- Deposit Task (+100 every 2 seconds)
- Withdraw Task (-50 every 3 seconds)
- Check Balance Task (prints balance every 1 second)

The shared variable `balance` is protected using a mutex to prevent race conditions.

## Concepts Used

- FreeRTOS Tasks
- Mutex
- Shared Resource
- Critical Section
- Race Condition
- Mutual Exclusion

## Language

- C

## Platform

- FreeRTOS Windows Simulator (Visual Studio)