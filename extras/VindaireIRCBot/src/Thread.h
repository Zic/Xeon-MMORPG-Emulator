#ifndef _THREAD_H
#define _THREAD_H

#include "StdAfx.h"

/*
 * C++ Thread class taken from http://www.codeproject.com/KB/threads/ThreadClass.aspx
 */

struct IRunnable {
  virtual void Update() = 0;
};

// define the thread class

class Thread {
public:
  Thread(IRunnable *ptr) {
    _threadObj = ptr;
  }
  void start() {
    // use the Win32 API here

    DWORD threadID;
    CreateThread(0, 0, threadProc, _threadObj, 0, &threadID);
  }
  
protected:
  // Win32 compatible thread parameter and procedure 

  IRunnable *_threadObj; 
  static unsigned long __stdcall threadProc(void* ptr) {
    ((IRunnable*)ptr)->Update();
    return 0;
  }   
};

#endif