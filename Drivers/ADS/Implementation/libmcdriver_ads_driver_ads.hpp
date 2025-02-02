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

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Abstract: This is the class declaration of CDriver_ADS

*/


#ifndef __LIBMCDRIVER_ADS_DRIVER_ADS
#define __LIBMCDRIVER_ADS_DRIVER_ADS

#include "libmcdriver_ads_interfaces.hpp"
#include "libmcdriver_ads_client.hpp"
#include "libmcdriver_ads_sdk.hpp"

// Parent classes
#include "libmcdriver_ads_driver.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include <mutex>
#include <vector>
#include <map>


namespace LibMCDriver_ADS {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDriver_ADS 
**************************************************************************************************************************/

enum class eDriver_ADSParameterType : int32_t {
	ADSParameter_Unknown = 0,
	ADSParameter_BOOL = 1,
	ADSParameter_SINT = 2,
	ADSParameter_USINT = 3,
	ADSParameter_INT = 4,
	ADSParameter_UINT = 5,
	ADSParameter_DINT = 6,
	ADSParameter_UDINT = 7,
	ADSParameter_REAL = 8,
	ADSParameter_LREAL = 9,
	ADSParameter_STRING = 10,
	ADSParameter_STRUCT = 11
};


enum class eDriver_ADSParameterAccess : int32_t {
	ADSParameterAccess_Unknown = 0,
	ADSParameterAccess_Read = 1,
	ADSParameterAccess_Write = 2,
	ADSParameterAccess_ReadWrite = 3
};

class CDriver_ADSParameter {
private:
	std::string m_sName;
	std::string m_sDescription;
	std::string m_sADSName;
	eDriver_ADSParameterType m_eType;
	eDriver_ADSParameterAccess m_eAccess;
	uint32_t m_nFieldSize;
	std::string m_sClassName;
public:
	CDriver_ADSParameter(const std::string & sName, const std::string& sDescription, const std::string & sADSName, const eDriver_ADSParameterType eType, const eDriver_ADSParameterAccess eAccess, const uint32_t nFieldSize = 0, const std::string & sClassName = "");
	virtual ~CDriver_ADSParameter();

	std::string getName ();
	std::string getDescription();
	std::string getADSName ();
	eDriver_ADSParameterType getType ();
	eDriver_ADSParameterAccess getAccess ();
	uint32_t getFieldSize ();
	std::string getClassName ();

};

typedef std::shared_ptr<CDriver_ADSParameter> PDriver_ADSParameter;

class CDriver_ADSStruct {
private:
	std::string m_sName;
	std::string m_sDescription;
	std::string m_sADSName;

	std::vector <PDriver_ADSParameter> m_Parameters;
public:
	CDriver_ADSStruct(const std::string& sName, const std::string& sDescription, const std::string& sADSName);
	virtual ~CDriver_ADSStruct();

	std::string getName();
	std::string getDescription();
	std::string getADSName();

};

typedef std::shared_ptr<CDriver_ADSStruct> PDriver_ADSStruct;


class CDriver_ADS : public virtual IDriver_ADS, public virtual CDriver {
private:

	bool m_bSimulationMode;

	std::string m_sName;
	std::mutex m_driverEnvironmentMutex;
	LibMCEnv::PDriverEnvironment m_pDriverEnvironment;

	std::string m_sCustomSDKResource;

	PADSSDK m_pADSSDK;
	PADSClient m_pADSClient;

	uint32_t m_nMajorVersion;
	uint32_t m_nMinorVersion;
	uint32_t m_nPatchVersion;

	LibMCEnv::PWorkingDirectory m_pWorkingDirectory;
	LibMCEnv::PWorkingFile m_pADSDLLFile;

	std::vector<PDriver_ADSStruct> m_Structs;
	std::map<std::string, PDriver_ADSStruct> m_StructMap;

	std::vector<PDriver_ADSParameter> m_Parameters;
	std::map<std::string, PDriver_ADSParameter> m_ParameterMap;

	PDriver_ADSParameter findParameter(const std::string& sVariableName, bool bFailIfNotExisting);

protected:


public:
	CDriver_ADS(const std::string& sName, LibMCEnv::PDriverEnvironment pDriverEnvironment);

	virtual ~CDriver_ADS();

	void SetCustomSDKResource(const std::string& sResourceName) override;

	void Configure(const std::string& sConfigurationString) override;

	std::string GetName() override;

	std::string GetType() override;

	void GetVersion(LibMCDriver_ADS_uint32& nMajor, LibMCDriver_ADS_uint32& nMinor, LibMCDriver_ADS_uint32& nMicro, std::string& sBuild) override;

	void QueryParameters() override;

	void QueryParametersEx(LibMCEnv::PDriverStatusUpdateSession pDriverUpdateInstance) override;

	void SetToSimulationMode() override;

	bool IsSimulationMode() override;

	void Connect(const LibMCDriver_ADS_uint32 nPort, const LibMCDriver_ADS_uint32 nTimeout) override;

	void Disconnect() override;
	
	bool VariableExists(const std::string & sVariableName) override;

	LibMCDriver_ADS_int64 ReadIntegerValue(const std::string& sVariableName) override;

	void WriteIntegerValue(const std::string& sVariableName, const LibMCDriver_ADS_int64 nValue) override;

	LibMCDriver_ADS_double ReadFloatValue(const std::string& sVariableName) override;

	void WriteFloatValue(const std::string& sVariableName, const LibMCDriver_ADS_double dValue) override;

	bool ReadBoolValue(const std::string& sVariableName) override;

	void WriteBoolValue(const std::string& sVariableName, const bool bValue) override;

	std::string ReadStringValue(const std::string& sVariableName) override;

	void WriteStringValue(const std::string& sVariableName, const std::string& sValue) override;

	void GetVariableBounds(const std::string& sVariableName, LibMCDriver_ADS_int64& nMinValue, LibMCDriver_ADS_int64& nMaxValue) override;

};

} // namespace Impl
} // namespace LibMCDriver_ADS

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDRIVER_ADS_DRIVER_ADS
