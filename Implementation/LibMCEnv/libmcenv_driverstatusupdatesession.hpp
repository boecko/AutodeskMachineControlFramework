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


Abstract: This is the class declaration of CDriverStatusUpdateSession

*/


#ifndef __LIBMCENV_DRIVERSTATUSUPDATESESSION
#define __LIBMCENV_DRIVERSTATUSUPDATESESSION

#include "libmcenv_interfaces.hpp"

// Parent classes
#include "libmcenv_base.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "amc_parametergroup.hpp"
#include "amc_logger.hpp"
#include "common_chrono.hpp"

namespace LibMCEnv {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDriverStatusUpdateSession 
**************************************************************************************************************************/

class CDriverStatusUpdateSession : public virtual IDriverStatusUpdateSession, public virtual CBase {
private:
	AMC::PParameterGroup m_pParameterGroup;
	AMC::PLogger m_pLogger;
	std::string m_sDriverName;
	AMCCommon::PChrono m_pGlobalChrono;

	AMCCommon::CChrono m_Chrono;

public:

	CDriverStatusUpdateSession(AMC::PParameterGroup pParameterGroup, AMC::PLogger pLogger, std::string sDriverName, AMCCommon::PChrono pGlobalChrono);
	
	virtual ~CDriverStatusUpdateSession();

	void SetStringParameter(const std::string & sParameterName, const std::string & sValue) override;

	void SetUUIDParameter(const std::string & sParameterName, const std::string & sValue) override;

	void SetDoubleParameter(const std::string & sParameterName, const LibMCEnv_double dValue) override;

	void SetIntegerParameter(const std::string & sParameterName, const LibMCEnv_int64 nValue) override;

	void SetBoolParameter(const std::string & sParameterName, const bool bValue) override;

	void LogMessage(const std::string & sLogString) override;

	void LogWarning(const std::string & sLogString) override;

	void LogInfo(const std::string & sLogString) override;

	void Sleep(const LibMCEnv_uint32 nDelay) override;

};

} // namespace Impl
} // namespace LibMCEnv

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCENV_DRIVERSTATUSUPDATESESSION
