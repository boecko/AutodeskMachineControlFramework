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


Abstract: This is the class declaration of CPLCCommandList

*/


#ifndef __LIBMCDRIVER_OPCUA_PLCCOMMANDLIST
#define __LIBMCDRIVER_OPCUA_PLCCOMMANDLIST

#include "libmcdriver_opcua_interfaces.hpp"

// Parent classes
#include "libmcdriver_opcua_base.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.


namespace LibMCDriver_OPCUA {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CPLCCommandList 
**************************************************************************************************************************/

class CPLCCommandList : public virtual IPLCCommandList, public virtual CBase {
private:

	/**
	* Put private members here.
	*/

protected:

	/**
	* Put protected members here.
	*/

public:

	/**
	* Put additional public members here. They will not be visible in the external API.
	*/


	/**
	* Public member functions to implement.
	*/

	void AddCommand(IPLCCommand* pCommandInstance) override;

	void FinishList() override;

	void ExecuteList() override;

	bool WaitForList(const LibMCDriver_OPCUA_uint32 nReactionTimeInMS, const LibMCDriver_OPCUA_uint32 nWaitForTimeInMS) override;

	void PauseList() override;

	void ResumeList() override;

};

} // namespace Impl
} // namespace LibMCDriver_OPCUA

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDRIVER_OPCUA_PLCCOMMANDLIST
