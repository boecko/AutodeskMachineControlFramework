/*++

Copyright (C) 2022 Autodesk Inc.

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

#ifndef __AMCSERVER_CONFIGURATION
#define __AMCSERVER_CONFIGURATION


#include <string>
#include <memory>
#include <map>
#include <set>

#include "libmcdata_dynamic.hpp"
#include "amc_server_io.hpp"


namespace AMC {
	

	class CServerLibrary {
	private:
		std::string m_sLibraryPath;
		std::string m_sResourcePath;
	public:
		CServerLibrary(const std::string& sLibraryPath, const std::string& sResourcePath);
		~CServerLibrary();

		std::string getLibraryPath();
		std::string getResourcePath();


	};

	typedef std::shared_ptr<CServerLibrary> PServerLibrary;

	class CServerConfiguration {
	private:
		std::string m_sHostName;
		uint32_t m_nPort;
		std::string m_sDataDirectory;
		LibMCData::eDataBaseType m_DataBaseType;
		std::string m_sConnectionString;

		std::string m_sPackageName;
		std::string m_sPackageCoreClient;
		std::string m_sPackageConfig;

		bool m_bUseSSL;
		std::string m_sServerCertificatePEM;
		std::string m_sServerPrivateKeyPEM;

		std::string m_sBaseTempDirectory;

		std::map<std::string, PServerLibrary> m_Libraries;

	public:

		CServerConfiguration(const std::string & configurationXMLString, PServerIO pServerIO);
		virtual ~CServerConfiguration();

		std::string getHostName ();
		uint32_t getPort ();
		std::string getDataDirectory ();
		LibMCData::eDataBaseType getDataBaseType ();
		std::string getConnectionString ();
		std::string getPackageName ();
		std::string getPackageCoreClient ();
		std::string getPackageConfig ();
		std::string getBaseTempDirectory ();

		std::string getLibraryPath(const std::string & sLibraryName);
		std::string getResourcePath(const std::string& sLibraryName);

		bool useSSL();
		std::string getServerCertificatePEM();
		std::string getServerPrivateKeyPEM();

		std::set<std::string> getLibraryNames ();

		void loadPackageXML(const std::string sPackageFileName);

	};

	typedef std::shared_ptr<CServerConfiguration> PServerConfiguration;
		

	
	
	
}

#endif //__AMCSERVER_CONFIGURATION