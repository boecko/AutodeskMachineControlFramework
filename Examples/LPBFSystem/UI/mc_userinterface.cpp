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

#include "libmcui_interfaceexception.hpp"
#include "libmcui_eventhandler.hpp"
#include "libmcui_event.hpp"

#include <cmath>

#include <thread>

using namespace LibMCUI::Impl;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

/*************************************************************************************************************************
 Class declaration of CEvent_Logout
**************************************************************************************************************************/

class CEvent_Logout : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "logout";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		auto pXMLDocument = pUIEnvironment->CreateXMLDocument("rootnode", "http://test.com/namespace");

		auto pRootNode = pXMLDocument->GetRootNode();
		auto pTestNode = pRootNode->AddChild("", "testNode");
		pTestNode->AddAttribute("", "myattribute", "1234");
		pTestNode->AddAttribute("", "myattribute2", "123532454");

		auto sXMLString = pXMLDocument->SaveToString(true);

		pUIEnvironment->LogMessage(sXMLString);

		auto pNewDocument = pUIEnvironment->ParseXMLString(sXMLString);
		auto pNewRootNode = pNewDocument->GetRootNode();

		auto pNewSubNode = pNewRootNode->FindChild("", "testNode", true);
		pNewSubNode->AddAttribute("", "newattribute", "abc");

		pNewSubNode->RemoveAttribute("", "myattribute");
		pNewSubNode->RemoveAttribute("", "myattribute2");

		auto sNewXMLString = pNewDocument->SaveToString(true);

		pUIEnvironment->LogMessage(sNewXMLString);


		/*auto pBuildJob = pUIEnvironment->GetBuildJob("12345");

		auto pBuildFile = pUIEnvironment->FindStream (pBuildJob->GetStorageUUID());

		auto pZIPStream = pUIEnvironment->CreateZIPStream();

		auto pBuildFileStream = pZIPStream->CreateZIPEntry("build.3mf");
		pBuildFileStream->

		for (uint32_t nLayerIndex = 1; nLayerIndex < nLayerCount; nLayerIndex++) {
			auto pDataTable = pBuildJobExecution->LoadDataTable("recording_layer_" + std::to_string(nLayerIndex));
			auto pLayerCSV = pZIPStream->CreateZIPEntry("layer" + std::to_string (nLayerIndex) + ".csv");
			pDataTable->WriteCSV(pLayerCSV);
		}

		pZIPStream->Finish();


		pUIEnvironment->StartStreamDownload(pZIPStream->GetUUID()); */


		/*pUIEnvironment->LogMessage("Clicked on Logout: " + pUIEnvironment->GetCurrentUserLogin());
		pUIEnvironment->LogMessage("User Role: " + pUIEnvironment->GetCurrentUserRole());
		pUIEnvironment->LogMessage("User Language: " + pUIEnvironment->GetCurrentUserLanguage());
		pUIEnvironment->LogMessage("User UUID: " + pUIEnvironment->GetCurrentUserUUID());
		pUIEnvironment->LogMessage("User Description: " + pUIEnvironment->GetCurrentUserDescription());
		pUIEnvironment->LogMessage("User Permission for permission_user_management: " + std::to_string ( pUIEnvironment->CheckPermission("permission_user_management")) );
		pUIEnvironment->LogMessage("User Permission for permission_that_nobody_has: " + std::to_string(pUIEnvironment->CheckPermission("permission_that_nobody_has")));
		pUIEnvironment->LogMessage("User Permission for permission_view_builds: " + std::to_string(pUIEnvironment->CheckPermission("permission_view_builds")));
		pUIEnvironment->LogMessage("User Permission for permission_invalid: " + std::to_string(pUIEnvironment->CheckPermission("permission_invalid")));
		pUIEnvironment->LogOut();  */

	}

};



/*************************************************************************************************************************
 Class declaration of CEvent_CancelPreview
**************************************************************************************************************************/

class CEvent_CancelPreview : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "cancelpreview";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on CancelPreview Button");
		pUIEnvironment->SetUIProperty("importbuildjob.preview", "builduuid", "");
		pUIEnvironment->SetUIPropertyAsInteger("importbuildjob.preview", "currentlayer", 3);

		pUIEnvironment->ActivatePage("main");
		

	}

};



/*************************************************************************************************************************
 Class declaration of CEvent_StartBuild
**************************************************************************************************************************/

class CEvent_StartBuild : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "startbuild";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on StartBuild Button");

		if (pUIEnvironment->GetMachineParameterAsBool("main", "ui", "build_canbestarted")) {

			auto sBuildUUID = pUIEnvironment->GetUIPropertyAsUUID("importbuildjob.preview", "builduuid");

			pUIEnvironment->SetUIPropertyAsUUID("buildstatus.preview", "builduuid", sBuildUUID);
			pUIEnvironment->SetUIPropertyAsInteger("buildstatus.preview", "currentlayer", 3);

			auto pSignal = pUIEnvironment->PrepareSignal("main", "signal_initjob");
			pSignal->SetString("jobuuid", sBuildUUID);
			//pSignal->SetString("user_who_started_build", pUIEnvironment->GetUserLogin ());
			pSignal->Trigger();

			pUIEnvironment->ActivatePage("buildstatus");
		}
		else {

			pUIEnvironment->LogMessage("Build cannot be started!");
		}

	}

};


/*************************************************************************************************************************
 Class declaration of CEvent_TestJournal
**************************************************************************************************************************/

class CEvent_TestJournal : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "testjournal";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{


		pUIEnvironment->LogMessage("Clicked on Test Journal Button: " + pUIEnvironment->RetrieveEventSender ());
		//pUIEnvironment->SetUIProperty("main.machineimage.testimage", "imageresource", "ui_logo");

		auto pImage = pUIEnvironment->CreateEmptyImage(500, 400, 10.0, 10, LibMCEnv::eImagePixelFormat::RGB24bit);
		pImage->Clear(0x228899);

		std::vector<uint8_t> dataBuffer;
		auto pPNGImage = pImage->CreatePNGImage(nullptr);
		pPNGImage->GetPNGDataStream(dataBuffer);

		auto pTempStream = pUIEnvironment->CreateTemporaryStream("tempimage", "image/png");
		pTempStream->WriteData(dataBuffer);
		pTempStream->Finish();

		std::string sImageUUID = pTempStream->GetUUID();
		pUIEnvironment->LogMessage("temp UUID: " + sImageUUID);

		pUIEnvironment->SetUIProperty("main.machineimage.testimage", "imageresource", sImageUUID);

		/*

		auto pZIPStream = pUIEnvironment->CreateZIPStream("test_zip");
		auto pEntry1 = pZIPStream->CreateZIPEntry("file1.txt");
		pEntry1->WriteLine("LineA");

		auto pEntry2 = pZIPStream->CreateZIPEntry("file2.txt");
		pEntry2->WriteLine("LineB");
		pEntry2->WriteLine("LineC");

		pZIPStream->Finish();

		pUIEnvironment->StartStreamDownload(pZIPStream->GetUUID(), "download.zip"); */

		/*auto pUserManagement = pUIEnvironment->CreateUserManagement();
		auto activeUsers = pUserManagement->GetActiveUsers();
		uint32_t nCount = activeUsers->Count();
		for (uint32_t nIndex = 0; nIndex < nCount; nIndex++) {
			auto sUserName = activeUsers->GetUsername(nIndex);
			pUIEnvironment->LogMessage("UserName: " + sUserName);
		}

		std::string sUserDescription = pUserManagement->GetUserDescription("test");
		pUIEnvironment->LogMessage("user description: " + sUserDescription);

		pUIEnvironment->LogMessage("creating user dummy");

		//pUserManagement->CreateUser("dummy", "administrator", "3fbde1f66fb512223edb195d247fe770130f59fdd914e3ffa7327af53fe4cb46", "dd9a86491eb7572c1a9cda800e6eb81bb9dad55576b01416d06cdf6ae181fb33", "This is the new dummy user."); */

		/*

		auto pJournal = pUIEnvironment->GetCurrentJournal();
		auto pJournalVariable = pJournal->RetrieveJournalVariable ("main.jobinfo.countertest", 10000);
		pUIEnvironment->LogMessage("Variable Name: " +  pJournalVariable->GetVariableName());
		auto nStartTime = pJournalVariable->GetStartTimeStamp();
		auto nEndTime = pJournalVariable->GetEndTimeStamp();

		pUIEnvironment->LogMessage("Start Time: " + std::to_string (nStartTime));
		pUIEnvironment->LogMessage("End Time: " + std::to_string(nEndTime));
		double dAverage = pJournalVariable->ComputeAverage(nStartTime, nEndTime, true); 

		pUIEnvironment->LogMessage("Average: " + std::to_string(dAverage));

		std::vector <LibMCEnv::sTimeStreamEntry> timeStream;
		pJournalVariable->ReceiveRawTimeStream(timeStream);

		std::vector<LibMCEnv::sTimeStreamEntry> entryBuffer;

		uint64_t nTimer = pUIEnvironment->GetGlobalTimerInMilliseconds();
		pUIEnvironment->LogMessage("timer: " + std::to_string (nTimer));
		uint32_t nCount = nTimer / 10;
		for (uint32_t nIndex = 0; nIndex < nCount; nIndex++) {
			entryBuffer.push_back({ nIndex, sin (nIndex * 0.01) * 100 });
		}

		std::string sDataSeriesUUID = pUIEnvironment->GetUIPropertyAsUUID("main.infobox.chart1", "dataseries");
		if (pUIEnvironment->HasDataSeries(sDataSeriesUUID)) {
			auto pDataSeries = pUIEnvironment->FindDataSeries(sDataSeriesUUID);
			pDataSeries->SetAllEntries(entryBuffer);
		}
		else {
			auto pDataSeries = pUIEnvironment->CreateDataSeries("testseries", true);
			pDataSeries->SetAllEntries(entryBuffer);
			auto sUUID = pDataSeries->GetUUID();
			pUIEnvironment->LogMessage("Series UUID: " + sUUID);

			pUIEnvironment->SetUIPropertyAsUUID("main.infobox.chart1", "dataseries", sUUID);
		}

		 */

	}

};

/*************************************************************************************************************************
 Class declaration of CEvent_StartBuild
**************************************************************************************************************************/

class CEvent_NewLayerStarted : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "newlayerstarted";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		auto nCurrentLayer = pUIEnvironment->GetMachineParameterAsInteger("main", "jobinfo", "currentlayer");

		pUIEnvironment->LogMessage("New layer started: " + std::to_string (nCurrentLayer));
		pUIEnvironment->SetUIPropertyAsInteger("buildstatus.preview", "currentlayer", nCurrentLayer);

	}

};


class CEvent_ChangeManualValues : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "changemanualvalues";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		double dO2Value = pUIEnvironment->GetMachineParameterAsDouble("main", "processsettings", "targeto2");
		double dGasFlowSpeed = pUIEnvironment->GetMachineParameterAsDouble("main", "processsettings", "gasflowspeed");
		double dRecoaterSpeed = pUIEnvironment->GetMachineParameterAsDouble("main", "processsettings", "recoaterspeed");
		pUIEnvironment->SetUIPropertyAsDouble("testdialog.infobox.processparameters.o2_value", "value", dO2Value);
		pUIEnvironment->SetUIPropertyAsDouble("testdialog.infobox.processparameters.gasflowspeed", "value", dGasFlowSpeed);
		pUIEnvironment->SetUIPropertyAsDouble("testdialog.infobox.processparameters.recoaterspeed", "value", dRecoaterSpeed);

		pUIEnvironment->ActivateModalDialog("testdialog");

	}

};



class CEvent_OnUploadFinished : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onuploadfinished";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{
		auto sSender = pUIEnvironment->RetrieveEventSender();
		pUIEnvironment->LogMessage("Uploaded success from " + sSender);

		auto sBuildUUID = pUIEnvironment->GetUIPropertyAsUUID(sSender, "uploaduuid");
		pUIEnvironment->LogMessage("Build job ID " + sBuildUUID);

		auto pBuild = pUIEnvironment->GetBuildJob(sBuildUUID);
		pBuild->LoadToolpath();

		pUIEnvironment->LogMessage("Registering PIDIndex");
		auto pAccessor = pBuild->CreateToolpathAccessor();
		pAccessor->RegisterCustomSegmentAttribute("http://schemas.scanlab.com/oie/2023/08", "pidindex", LibMCEnv::eToolpathAttributeType::Double);

		pUIEnvironment->LogMessage("Loading Layer 3");
		auto pLayer = pAccessor->LoadLayer(3);

		uint32_t nAttributeID = pLayer->FindCustomSegmentAttributeID("http://schemas.scanlab.com/oie/2023/08", "pidindex");
		pUIEnvironment->LogMessage("Attribute ID: " + std::to_string (nAttributeID));

		uint32_t nSegmentCount = pLayer->GetSegmentCount ();
		for (uint32_t nSegmentIndex = 0; nSegmentIndex < nSegmentCount; nSegmentIndex++) 
		{
			//double nPIDIndex = pLayer->GetSegmentDoubleAttribute(nSegmentIndex, nAttributeID);
			int64_t nOIEPIDControlIndex = pLayer->GetSegmentProfileIntegerValueDef(nSegmentIndex, "http://schemas.scanlab.com/oie/2023/08", "pidindex", 0);
			pUIEnvironment->LogMessage("Segment #" + std::to_string(nSegmentIndex) + ": PID Index " + std::to_string (nOIEPIDControlIndex));
		}
		
		pUIEnvironment->SetUIProperty("importbuildjob.preview", "builduuid", sBuildUUID);
		pUIEnvironment->SetUIPropertyAsInteger("importbuildjob.preview", "currentlayer", 200);

		pUIEnvironment->ActivatePage("importbuildjob");
	}

};




class CEvent_OnSelectBuild : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onselectbuild";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{
		auto sSender = pUIEnvironment->RetrieveEventSender();
		pUIEnvironment->LogMessage("Build item selected from " + sSender);

		auto sBuildUUID = pUIEnvironment->GetUIPropertyAsUUID(sSender, "selecteduuid");
		pUIEnvironment->LogMessage("Build job ID " + sBuildUUID);

/*		auto pSignal = pUIEnvironment->PrepareSignal("main", "signal_initjob");
		pSignal->SetString("jobuuid", sBuildUUID);
		pSignal->Trigger();

		pUIEnvironment->SetUIPropertyAsUUID("buildstatus.preview", "builduuid", sBuildUUID);
		pUIEnvironment->SetUIPropertyAsInteger("buildstatus.preview", "currentlayer", 2);*/

		pUIEnvironment->SetUIProperty("importbuildjob.preview", "builduuid", sBuildUUID);
		pUIEnvironment->SetUIPropertyAsInteger("importbuildjob.preview", "currentlayer", 200);

		pUIEnvironment->ActivatePage("importbuildjob");

	}

};


class CEvent_OnViewIn3D : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onviewin3d";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{
		auto sSender = pUIEnvironment->RetrieveEventSender();
		pUIEnvironment->LogMessage("Build item selected from " + sSender);

		auto sBuildUUID = pUIEnvironment->GetUIPropertyAsUUID(sSender, "selecteduuid");
		pUIEnvironment->LogMessage("Build job ID " + sBuildUUID);

		auto sButtonUUID = pUIEnvironment->GetUIPropertyAsUUID(sSender, "buttonuuid");
		pUIEnvironment->LogMessage("Button UUID " + sButtonUUID);

		auto pBuildJob = pUIEnvironment->GetBuildJob(sBuildUUID);
		pUIEnvironment->LogMessage("View in 3D");
		pBuildJob->LoadToolpath();

		std::string sBinaryMetaDataName = "layer0_headA";
		auto pToolpathAccessor = pBuildJob->CreateToolpathAccessor();

		if (pToolpathAccessor->HasBinaryMetaData(sBinaryMetaDataName)) {

			std::vector<uint8_t> buffer;
			pToolpathAccessor->GetBinaryMetaData(sBinaryMetaDataName, buffer);

			pUIEnvironment->LogMessage("Binary metadata size of " + sBinaryMetaDataName + ": " + std::to_string(buffer.size()));
		}

		auto pSceneHandler = pUIEnvironment->CreateSceneHandler();
		auto pMeshScene = pSceneHandler->CreateEmptyMeshScene(true);

		auto pToolpath = pBuildJob->CreateToolpathAccessor();
		uint32_t nPartCount = pToolpath->GetPartCount();

		for (uint32_t nPartIndex = 0; nPartIndex < nPartCount; nPartIndex++) {
			auto pPart = pToolpath->GetPart(nPartIndex);
			pUIEnvironment->LogMessage("Part: " + pPart->GetName ());

			auto pComponent = pPart->GetRootComponent();
			uint32_t nSolidCount = pComponent->GetSolidCount();
			pUIEnvironment->LogMessage("Solids: " + std::to_string (nSolidCount));

			for (uint32_t nIndex = 0; nIndex < nSolidCount; nIndex++) {
				auto pMesh = pComponent->GetSolidMesh(nIndex);
				auto pMeshData = pMesh->CreatePersistentMesh (false);
				pUIEnvironment->LogMessage ("triangle count:" + std::to_string (pMeshData->GetTriangleCount()));
				pUIEnvironment->LogMessage("persistent mesh uuid: " + pMeshData->GetUUID ());

				pMeshScene->AddSceneItem(pMeshData, pMesh->GetAbsoluteTransform());
			}


		}

	}

};



class CEvent_OnFakeJob : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onfakejob";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{
		auto sSender = pUIEnvironment->RetrieveEventSender();
		pUIEnvironment->LogMessage("Build item selected from " + sSender);

		auto sBuildUUID = pUIEnvironment->GetUIPropertyAsUUID(sSender, "selecteduuid");
		pUIEnvironment->LogMessage("Build job ID " + sBuildUUID);

		auto sButtonUUID = pUIEnvironment
			->GetUIPropertyAsUUID(sSender, "buttonuuid");
		pUIEnvironment->LogMessage("Button UUID " + sButtonUUID);

		auto pBuildJob = pUIEnvironment->GetBuildJob(sBuildUUID);
		auto pExecution = pBuildJob->StartExecution("This is a test description", pUIEnvironment->GetCurrentUserUUID());

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));

		pExecution->SetStatusToFinished();

	}

};


class CEvent_OnChangeSimulationParameterEvent : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "changesimulationparameter";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{
		auto sSender = pUIEnvironment->RetrieveEventSender();
		pUIEnvironment->LogMessage("Change simulation parameter from " + sSender);

		bool bValue = pUIEnvironment->GetUIPropertyAsBool(sSender, "value");
		pUIEnvironment->LogMessage("Change " + sSender + " to " + std::to_string (bValue));

		auto pSignal = pUIEnvironment->PrepareSignal("main", "signal_changesimulationparameters");
		pSignal->SetBool("simulatelaser", pUIEnvironment->GetUIPropertyAsBool("main.settings.simulationparameters.simulatelaser", "value"));
		pSignal->SetBool("simulateplc", pUIEnvironment->GetUIPropertyAsBool("main.settings.simulationparameters.simulateplc", "value"));
		pSignal->Trigger();
	}

};


class CEvent_OnBuildCancelDialogOK : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onbuildcanceldialogok";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on OK: " + pUIEnvironment->RetrieveEventSender());
		if (pUIEnvironment->GetMachineParameterAsBool("main", "ui", "build_canbecanceled")) {
			auto pSignal = pUIEnvironment->PrepareSignal("main", "signal_cancelbuild");
			pSignal->Trigger();
		}

		pUIEnvironment->CloseModalDialog();

	}

};



class CEvent_OnBuildCancelDialogCancel : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "onbuildcanceldialogcancel";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{		

		pUIEnvironment->LogMessage("Clicked on cancel: " + pUIEnvironment->RetrieveEventSender());

		pUIEnvironment->CloseModalDialog();

	}

};


class CEvent_PauseBuild : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "pausebuild";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on Pause Build");
		if (pUIEnvironment->GetMachineParameterAsBool("main", "ui", "build_canbepaused")) {
			pUIEnvironment->ActivateModalDialog("pausedialog");
		}

	}

};


class CEvent_CancelBuild : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "cancelbuild";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on Cancel Build");
		if (pUIEnvironment->GetMachineParameterAsBool("main", "ui", "build_canbecanceled")) {
			pUIEnvironment->SetUIProperty("generaldialog.infobox.buttongroup.button1", "caption", "Yes");
			pUIEnvironment->SetUIProperty("generaldialog.infobox.buttongroup.button2", "caption", "No");
			pUIEnvironment->SetUIProperty("generaldialog.infobox.buttongroup.button1", "event", "onbuildcanceldialogok");
			pUIEnvironment->SetUIProperty("generaldialog.infobox.buttongroup.button2", "event", "onbuildcanceldialogcancel");
			pUIEnvironment->ActivateModalDialog("generaldialog");
		}

	}

};

class CEvent_CancelBuildFromPause : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "cancelbuildfrompause";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on Cancel Build");

		if (pUIEnvironment->GetMachineParameterAsBool("main", "ui", "build_canbecanceled")) {
			auto pSignal = pUIEnvironment->PrepareSignal("main", "signal_canceljob");
			pSignal->Trigger();
		}

		pUIEnvironment->CloseModalDialog ();


	}

};


class CEvent_ResumeBuild : public virtual CEvent {

public:

	static std::string getEventName()
	{
		return "resumebuild";
	}

	void Handle(LibMCEnv::PUIEnvironment pUIEnvironment) override
	{

		pUIEnvironment->LogMessage("Clicked on Resume Build");

	}

};


IEvent* CEventHandler::CreateEvent(const std::string& sEventName, LibMCEnv::PUIEnvironment pUIEnvironment)
{
	IEvent* pEventInstance = nullptr;
	if (createEventInstanceByName<CEvent_CancelPreview>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_StartBuild>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_ChangeManualValues>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnUploadFinished>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnSelectBuild>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnBuildCancelDialogOK>(sEventName, pEventInstance))
		return pEventInstance;	
	if (createEventInstanceByName<CEvent_OnBuildCancelDialogCancel>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnChangeSimulationParameterEvent>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_CancelBuild>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_CancelBuildFromPause>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_PauseBuild>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_ResumeBuild>(sEventName, pEventInstance))
		return pEventInstance;	
	if (createEventInstanceByName<CEvent_NewLayerStarted>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_Logout>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_TestJournal>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnFakeJob>(sEventName, pEventInstance))
		return pEventInstance;
	if (createEventInstanceByName<CEvent_OnViewIn3D>(sEventName, pEventInstance))
		return pEventInstance;
	

	throw ELibMCUIInterfaceException(LIBMCUI_ERROR_INVALIDEVENTNAME, "invalid event name: " + sEventName);
}




#ifdef _MSC_VER
#pragma warning(pop)
#endif
