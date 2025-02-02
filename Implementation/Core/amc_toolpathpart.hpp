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


#ifndef __AMC_TOOLPATHPART
#define __AMC_TOOLPATHPART

#include <memory>
#include <string>
#include <thread>
#include <mutex>

#include "lib3mf/lib3mf_dynamic.hpp"
#include "libmcdata_dynamic.hpp"


namespace AMC {

	class CToolpathPart;
	typedef std::shared_ptr<CToolpathPart> PToolpathPart;

	class CToolpathPart {
	private:		
		std::string m_sUUID;
		std::string m_sMeshUUID;
		std::string m_sName;		
		std::string m_sPartNumber;
		
		Lib3MF::PModel m_p3MFModel;
		Lib3MF::PBuildItem m_pBuildItem;
		Lib3MF::PWrapper m_pWrapper;
		
	public:
	
		CToolpathPart(Lib3MF::PModel p3MFModel, Lib3MF::PBuildItem pBuildItem, Lib3MF::PWrapper pWrapper);
		virtual ~CToolpathPart();		

		std::string getUUID ();
		std::string getMeshUUID ();
		std::string getName ();
		std::string getPartNumber ();

		Lib3MF::PModel getModel();
		Lib3MF::PBuildItem getBuildItem();

	};

	
}


#endif //__AMC_TOOLPATHENTITY

