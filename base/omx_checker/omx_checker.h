/******************************************************************************
*
* Copyright (C) 2017 Allegro DVT2.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX OR ALLEGRO DVT2 BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of  Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*
* Except as contained in this notice, the name of Allegro DVT2 shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Allegro DVT2.
*
******************************************************************************/

#pragma once

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <string.h>

enum AL_ComponentMethods
{
  AL_GetComponentVersion = 100,
  AL_SendCommand,
  AL_GetParameter,
  AL_SetParameter,
  AL_GetConfig,
  AL_SetConfig,
  AL_GetExtensionIndex,
  AL_GetState,
  AL_ComponentTunnelRequest,
  AL_UseBuffer,
  AL_AllocateBuffer,
  AL_FreeBuffer,
  AL_EmptyThisBuffer,
  AL_FillThisBuffer,
  AL_SetCallbacks,
  AL_ComponentDeinit,
  AL_UseEGLImage,
  AL_ComponentRoleEnum
};

/*****************************************************************************/
class OMXChecker
{
public:
  /* Variables */

  /* Methods */

  /*************************************************************************//*!
     \brief  The CheckStateOperation method test if the OMX_Method can be called in the
            current state
     \param[in]  methodName Name of the OMX_Method
     \param[in]  curState Current component's state
     \return OMX_ErrorNone if the method can be called
            OMX_ErrorInvalidState if the current state is invalid
            OMX_ErrorIncorrectStateOperation otherwise
  *****************************************************************************/
  static OMX_ERRORTYPE CheckStateOperation(const AL_ComponentMethods methodName, const OMX_STATETYPE curState);

  static bool CheckStateExistance(const OMX_STATETYPE state);

  /*************************************************************************//*!
     \brief  The CheckStateTransition method test if the transition between old state
            and new state can be done
     \param[in]  curState Current component's state
     \param[in]  newState New component's state
     \return OMX_ErrorNone if transition can be done
            OMX_ErrorSameState if the new state equal the current state
            OMX_ErrorIncorrectStateTransition otherwise
  *****************************************************************************/
  static OMX_ERRORTYPE CheckStateTransition(const OMX_STATETYPE curState, const OMX_STATETYPE newState);

  /*************************************************************************//*!
     \brief  The CheckNotNull method test if the parameter send is not null
     \param[in]  ptr Pointer
     \return OMX_ErrorNone if ptr is not null
            OMX_ErrorBadParameter otherwise
  *****************************************************************************/
  template<typename T>
  static
  inline
  OMX_ERRORTYPE CheckNotNull(T const ptr)
  {
    if(!ptr)
      return OMX_ErrorBadParameter;
    return OMX_ErrorNone;
  };

  /*************************************************************************//*!
     \brief  The CheckIsEqual method test if the parameters send are equal
     \param[in]  param1
     \param[in]  param2
     \return OMX_ErrorNone if param1 equal param2
            OMX_ErrorBadParameter otherwise
  *****************************************************************************/
  template<typename T>
  static
  inline
  OMX_ERRORTYPE CheckIsEqual(const T param1, const T param2)
  {
    if(param1 != param2)
      return OMX_ErrorBadParameter;
    return OMX_ErrorNone;
  };

  /*************************************************************************//*!
     \brief  The SetHeaderVersion method set the omx-il version header used. It also set to 0 everything else.
     \param[in]  header
  *****************************************************************************/
  template<typename T>
  static
  inline
  void SetHeaderVersion(T& header)
  {
    memset(&header, 0x0, sizeof(T));
    header.nSize = sizeof(header);
    header.nVersion.nVersion = OMX_VERSION;
  };

  /*************************************************************************//*!
     \brief  The CheckHeader method check if the header is at the omx-il version used
     \param[in]  version
     \return OMX_ErrorVersionMismatch if version != OMX_VERSION
             OMX_ErrorNone otherwise
  *****************************************************************************/
  static
  inline
  OMX_ERRORTYPE CheckHeaderVersion(OMX_VERSIONTYPE const version)
  {
    if(version.nVersion != OMX_VERSION)
      return OMX_ErrorVersionMismatch;
    return OMX_ErrorNone;
  };
};

