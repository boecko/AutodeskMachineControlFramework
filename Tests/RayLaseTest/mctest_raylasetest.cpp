/*++

Copyright (C) 2020 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the Autodesk Inc. nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "libmcplugin_statefactory.hpp"
#include "libmcplugin_interfaceexception.hpp"
#include "libmcplugin_state.hpp"

#include "libmcdriver_raylase_dynamic.hpp"
#include "libmcenv_drivercast.hpp"

using namespace LibMCPlugin::Impl;

#include <iostream>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif


/*************************************************************************************************************************
 Import functionality for Driver into current plugin
**************************************************************************************************************************/
LIBMC_IMPORTDRIVERCLASSES(Raylase, Raylase)


/*************************************************************************************************************************
 Class definition of CPLCData
**************************************************************************************************************************/
class CPLCData : public virtual CPluginData {
protected:
	// We need to globally store driver wrappers in the plugin
	PDriverCast_Raylase m_DriverCast_Raylase;

public:

	PDriver_Raylase acquireRaylaseDriver(LibMCEnv::PStateEnvironment pStateEnvironment)
	{
		return m_DriverCast_Raylase.acquireDriver(pStateEnvironment, "raylase");
	}

};

/*************************************************************************************************************************
 Class definition of CPLCData
**************************************************************************************************************************/
typedef CState<CPLCData> CPLCState;


/*************************************************************************************************************************
 Class definition of CPLCState_Init
**************************************************************************************************************************/
class CPLCState_Init : public virtual CPLCState {
public:

	CPLCState_Init(const std::string& sStateName, PPluginData pPluginData)
		: CPLCState(getStateName(), sStateName, pPluginData)
	{
	}

	static const std::string getStateName()
	{
		return "init";
	}


	void Execute(LibMCEnv::PStateEnvironment pStateEnvironment)
	{

		if (pStateEnvironment.get() == nullptr)
			throw ELibMCPluginInterfaceException(LIBMCPLUGIN_ERROR_INVALIDPARAM);

		pStateEnvironment->LogMessage("Acquiring Driver");
		auto pDriver = m_pPluginData->acquireRaylaseDriver(pStateEnvironment);
		pStateEnvironment->LogMessage("Loading SDK");
		pDriver->LoadSDK();

		pStateEnvironment->LogMessage("Connecting to Card");
		auto pCard = pDriver->ConnectByIP("card1", "169.254.70.75", 49374, 1000.0);
		pStateEnvironment->LogMessage("Resetting to system defaults");
		pCard->ResetToSystemDefaults();
		pStateEnvironment->LogMessage("Enabling pilot");
		pCard->EnablePilot(true);
		pStateEnvironment->LogMessage("Drawing layer");
		pCard->DrawLayer("93cbe258-5b39-4317-9d5b-a55d988b365d", 1);

		pStateEnvironment->SetNextState("success");
	}

};



/*************************************************************************************************************************
 Class definition of CPLCState_Success
**************************************************************************************************************************/
class CPLCState_Success : public virtual CPLCState {
public:

	CPLCState_Success(const std::string& sStateName, PPluginData pPluginData)
		: CPLCState(getStateName(), sStateName, pPluginData)
	{
	}

	static const std::string getStateName()
	{
		return "success";
	}


	void Execute(LibMCEnv::PStateEnvironment pStateEnvironment)
	{

		pStateEnvironment->SetNextState("success");

	}

};


/*************************************************************************************************************************
 Class definition of CMainState_FatalError
**************************************************************************************************************************/
class CPLCState_FatalError : public virtual CPLCState {
public:

	CPLCState_FatalError(const std::string& sStateName, PPluginData pPluginData)
		: CPLCState(getStateName(), sStateName, pPluginData)
	{
	}

	static const std::string getStateName()
	{
		return "fatalerror";
	}


	void Execute(LibMCEnv::PStateEnvironment pStateEnvironment)
	{
		if (pStateEnvironment.get() == nullptr)
			throw ELibMCPluginInterfaceException(LIBMCPLUGIN_ERROR_INVALIDPARAM);

		pStateEnvironment->SetNextState("fatalerror");
	}

};



/*************************************************************************************************************************
 Class definition of CStateFactory
**************************************************************************************************************************/

CStateFactory::CStateFactory(const std::string& sInstanceName)
{
	m_pPluginData = std::make_shared<CPLCData>();
}

IState* CStateFactory::CreateState(const std::string& sStateName)
{

	IState* pStateInstance = nullptr;

	if (createStateInstanceByName<CPLCState_Init>(sStateName, pStateInstance, m_pPluginData))
		return pStateInstance;


	if (createStateInstanceByName<CPLCState_Success>(sStateName, pStateInstance, m_pPluginData))
		return pStateInstance;

	if (createStateInstanceByName<CPLCState_FatalError>(sStateName, pStateInstance, m_pPluginData))
		return pStateInstance;

	throw ELibMCPluginInterfaceException(LIBMCPLUGIN_ERROR_INVALIDSTATENAME);

}


#ifdef _MSC_VER
#pragma warning(pop)
#endif
