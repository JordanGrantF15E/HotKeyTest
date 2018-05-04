// -*- mode: c++ -*-
/****************************************************************************
*****                                                                  *****
*****                   Classification: UNCLASSIFIED                   *****
*****                    Classified By:                                *****
*****                    Declassify On:                                *****
*****                                                                  *****
****************************************************************************
*
*
* Developed by: Naval Research Laboratory, Tactical Electronic Warfare Div.
*               EW Modeling & Simulation, Code 5770
*               4555 Overlook Ave.
*               Washington, D.C. 20375-5339
*
* For more information please send email to simdis@enews.nrl.navy.mil
*
* March 30, 2004 - U.S. Naval Research Laboratory.
*
* The U.S. Government retains all rights to use, duplicate, distribute,
* disclose, or release this software.
****************************************************************************
*
*
*/
#include "HotKeyTest.h"
#include "HotKeyDialog.h"
#include "PIIncludes.h"

//#include "GUIDialog.h"
//#include "DataDialog.h"
//#include "CommonDialog.h"
//#include "SIMDISDialog.h"
//#include "PlotXYDialog.h"
//#include "MouseDialog.h"
//#include "TabsDialog.h"
#include <string>
#include <sstream>

using namespace PICommon;
using namespace PIGUI;

// Declare the application; target API version 1.20
PI_DECLARE_APPLICATION_V2(HotKeyDialog, 12000);

static const std::string REGISTRY_KEY = "CustomValue";
static const std::string MINI_MAP_ACTION_NAME = "Toggle Mini Map";
static const std::string SUPER_FORM_ACTION_NAME = "Super Form";
static const std::string PREF_RULES_ACTION_NAME = "Preference Rules";

// Create a local icon (GIF format) for testing with the right click context menu
const unsigned char g_TextWriteIcon[] = {
	0x47,0x49,0x46,0x38,0x39,0x61,0x20,0x00,0x20,0x00,0xa2,0x06,0x00,0xc8,0xb4,0xc8,
	0xff,0xff,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x99,0x99,0x99,0xcc,0xcc,0xcc,0xff,
	0xff,0x00,0x00,0x00,0x00,0x21,0xf9,0x04,0x01,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,
	0x00,0x00,0x20,0x00,0x20,0x00,0x42,0x03,0xcf,0x08,0xba,0xdc,0x1e,0x50,0x48,0x18,
	0x16,0x2c,0x18,0x8f,0x91,0x79,0xc6,0x82,0x61,0x08,0x1f,0x51,0x10,0x02,0x70,0x7d,
	0xdb,0xf6,0xbd,0x70,0x69,0x05,0x71,0x2c,0x65,0xf7,0xbb,0xd6,0x7c,0x11,0x8e,0x19,
	0x94,0x62,0x57,0xf0,0x74,0x5e,0x12,0x01,0x61,0xf9,0x12,0xaa,0x68,0xbd,0x0f,0x09,
	0x34,0x7d,0xcd,0xa2,0xbc,0xa5,0x76,0x49,0xe9,0x7a,0xbf,0x14,0xd0,0x66,0x2a,0x24,
	0xb2,0x5c,0x36,0x51,0x15,0x53,0x86,0x6a,0x5e,0x46,0x90,0xfa,0xa4,0x65,0xa7,0x88,
	0x71,0x0e,0xda,0xb7,0x86,0x11,0x86,0x6e,0x58,0x7c,0x39,0x4d,0x80,0x82,0x54,0x49,
	0x84,0x19,0x57,0x87,0x89,0x8a,0x18,0x16,0x5b,0x92,0x8e,0x94,0x29,0x0e,0x97,0x33,
	0x60,0x5d,0x02,0x2d,0x02,0x01,0x6d,0x9a,0x82,0x4a,0x28,0x76,0x4f,0x87,0x30,0x3f,
	0x55,0x6d,0x31,0x68,0x71,0x38,0x73,0x25,0x77,0x81,0x45,0x2c,0xa8,0xb0,0x75,0xab,
	0x47,0xb5,0x52,0x6a,0x5b,0x41,0xb2,0xbb,0x1d,0x71,0x49,0x26,0x31,0x7f,0x78,0x1e,
	0x7b,0x2d,0xae,0x7e,0x86,0xa7,0x51,0x7f,0xa6,0x8d,0x8e,0x31,0xce,0xa7,0x89,0xd5,
	0xd2,0xa2,0x55,0x8f,0x05,0x8c,0x58,0x95,0x30,0xdf,0xcf,0x35,0xe3,0x25,0x92,0xe8,
	0x95,0x0c,0x95,0x12,0x98,0xee,0x0a,0x09,0x00,0x3b
};

class HotKeyDialog::HotKeyCloseObserver : public PIGUI::PIDialogBox::CloseObserver
{
public:
	explicit HotKeyCloseObserver(HotKeyDialog* parent)
		:parent_(parent)
	{}

	virtual void onClose(PIGUI::PIDialogBox* dialog)
	{
		parent_->dialogClosed_(dialog);
	}
private:
	HotKeyDialog* parent_;
};

////////////////////////////////////////////////////////////////////
//
//class HotKeyDialog::RightClickObserver : public PISIMDIS::ContextMenuCallback
//{
//public:
//	explicit RightClickObserver(HotKeyDialog& dialog)
//		: dialog_(dialog),
//		sampleIcon_(new PIGUI::PIIcon)
//	{
//		sampleIcon_->loadGIFByArray(g_TextWriteIcon);
//	}
//
//	virtual ~RightClickObserver()
//	{
//		delete sampleIcon_;
//	}
//
//	/** Override ContextMenuCallback::menuRequested() to show some items */
//	virtual void menuRequested(PISIMDIS::WhatWasClicked whatWasClicked, PIData::UniqueID_t entityId, PISIMDIS::ContextMenu* menu)
//	{
//		dialog_.lastRightClickId_ = entityId;
//		if (whatWasClicked == PISIMDIS::CLICKED_MINIMAP)
//		{
//			// Add a mini title to the minimap right-click menu that does nothing
//			PISIMDIS::addContextMenuItem(menu, "SIMDIS MiniMap", NULL, -700, NULL, false);
//			PISIMDIS::addContextMenuSeparator(menu, -650);
//		}
//		else if (whatWasClicked == PISIMDIS::CLICKED_ENTITY && entityId != 0)
//		{
//			// For right-clicking on platform entities, show a new menu item
//			if (PIData::getObjectType(entityId) == PIData::PI_OBJECT_PLATFORM)
//			{
//				FunctorTwoParams__* method = CreateCallback(&dialog_, &HotKeyDialog::onCmdContextMenuPopup);
//				PISIMDIS::addContextMenuItem(menu, "Test-PI Popup...", method, 150);
//			}
//		}
//
//		// Regardless of what we click on, show an action to toggle the state of the mini map.  Note
//		// that we only show this if the action exists and is visible to the end user
//		if (PICommon::doesActionExist(MINI_MAP_ACTION_NAME) && PICommon::isActionShown(MINI_MAP_ACTION_NAME))
//		{
//			PISIMDIS::addContextMenuSeparator(menu, 1100);
//			const bool enableIt = PICommon::isActionEnabled(MINI_MAP_ACTION_NAME);
//			const bool isCurrentlyShown = PICommon::isActionChecked(MINI_MAP_ACTION_NAME);
//			if (isCurrentlyShown)
//				PISIMDIS::addContextMenuItem(menu, "Test-PI: Hide Mini Map", CreateCallback(&dialog_, &HotKeyDialog::onCmdHideMiniMap), 1101, sampleIcon_, enableIt);
//			else
//				PISIMDIS::addContextMenuItem(menu, "Test-PI: Show Mini Map", CreateCallback(&dialog_, &HotKeyDialog::onCmdShowMiniMap), 1101, sampleIcon_, enableIt);
//		}
//
//		// Add a sub-menu for Super Form and Pref Rules
//		PISIMDIS::ContextMenu* toolsMenu = PISIMDIS::addContextMenuSubMenu(menu, "Test-PI Tools", 450);
//		PISIMDIS::addContextMenuItem(toolsMenu, "Super Form", CreateCallback(&dialog_, &HotKeyDialog::onCmdSuperForm), 10, NULL, PICommon::isActionEnabled(SUPER_FORM_ACTION_NAME));
//		PISIMDIS::addContextMenuItem(toolsMenu, "Pref Rules", CreateCallback(&dialog_, &HotKeyDialog::onCmdPrefRules), 20, NULL, PICommon::isActionEnabled(PREF_RULES_ACTION_NAME));
//		PISIMDIS::addContextMenuSeparator(toolsMenu, 15);
//	}
//
//private:
//	HotKeyDialog& dialog_;
//	PIGUI::PIIcon* sampleIcon_;
//};

////////////////////////////////////////////////////////////////////

void HotKeyDialog::dialogClosed_(PIDialogBox* dialog)
{
	//eventTextField_->setValue("Dialog Closed: " + dialog->getValueText());
}

//int HotKeyDialog::ConfigureCommandLine(PIApp::CommandLineRegistration& reg) const
//{
//	reg.registerFlag("TestFlag1", "Documentation for TestFlag1");
//	reg.registerParameter("TestParam1", "Documentation for TestParam1");
//	reg.registerVector("TestVec", "Documentation for TestVec");
//	reg.registerFlag("TestFlag2", "Documentation for TestFlag2");
//	reg.registerParameter("file", "Documentation for file.  The -file param is a parameter with a long documentation string.");
//	return 0;
//}

/**
* Place all start up commands in this function.  Here, we are creating a
* dialog box to display many buttons.
* @return 0 on success
*/
int HotKeyDialog::StartUp(const PIApp::CommandLineArguments& args)
{
	/*cmdLineArguments_ = &args;*/

	// Creates hot key actions in SIMDIS for all numbers, plus functional actions
	PICommon::createAction("HotKey Test", "1", CreateCallback(this, &HotKeyDialog::onPress1));
	PICommon::createAction("HotKey Test", "2", CreateCallback(this, &HotKeyDialog::onPress2));
	PICommon::createAction("HotKey Test", "3", CreateCallback(this, &HotKeyDialog::onPress3));
	PICommon::createAction("HotKey Test", "4", CreateCallback(this, &HotKeyDialog::onPress4));
	PICommon::createAction("HotKey Test", "5", CreateCallback(this, &HotKeyDialog::onPress5));
	PICommon::createAction("HotKey Test", "6", CreateCallback(this, &HotKeyDialog::onPress6));
	PICommon::createAction("HotKey Test", "7", CreateCallback(this, &HotKeyDialog::onPress7));
	PICommon::createAction("HotKey Test", "8", CreateCallback(this, &HotKeyDialog::onPress8));
	PICommon::createAction("HotKey Test", "9", CreateCallback(this, &HotKeyDialog::onPress9));
	PICommon::createAction("HotKey Test", "0", CreateCallback(this, &HotKeyDialog::onPress0));
	PICommon::createAction("HotKey Test", "Kill", CreateCallback(this, &HotKeyDialog::onPressKill));

		// Create menu options
	new PIGUI::PIMenuItem(NULL, "Hot Key Dialog...", CreateCallback(this, &HotKeyDialog::onCmdShowDialog));

	// Create a dialog box with different buttons
	HotKeyDialog_ = new PIDialogBox("Hot Key Dialog");
	// Create a vertical frame to order the objects vertically
	PIVerticalFrame* vFrame = new PIVerticalFrame(HotKeyDialog_, PI_LAYOUT_FILL_X | PI_LAYOUT_FILL_Y);
	//// Create a horizontal matrix for the current host and version
	//PIHorizontalMatrix* programInfoMatrix = new PIHorizontalMatrix(vFrame, 4, PI_LAYOUT_FILL_X);
	//new PILabel(programInfoMatrix, "Host:", PI_LAYOUT_RIGHT);
	//PITextField* hostText = new PITextField(programInfoMatrix, 20, NULL, PI_LAYOUT_FILL_X);
	//new PILabel(programInfoMatrix, "Host Version:", PI_LAYOUT_RIGHT);
	//PITextField* hostVerText = new PITextField(programInfoMatrix, 4, NULL, PI_LAYOUT_FILL_X);
	//new PILabel(programInfoMatrix, "Host Plugin Version:", PI_LAYOUT_RIGHT);
	//PITextField* hostPlugVerText = new PITextField(programInfoMatrix, 4, NULL, PI_LAYOUT_FILL_X);
	//new PILabel(programInfoMatrix, "Local Plugin Version:", PI_LAYOUT_RIGHT);
	//PITextField* localVer = new PITextField(programInfoMatrix, 4, NULL, PI_LAYOUT_FILL_X);
	// Create a field for the most recent event

	PIHorizontalMatrix* hEventFrame = new PIHorizontalMatrix(vFrame, 1, PI_LAYOUT_FILL_X);
	//new PILabel(hEventFrame, "Most Recent Event:", PI_LAYOUT_RIGHT);
	hotkeydugoutTextField_ = new PITextField(hEventFrame, 30, NULL, PI_LAYOUT_FILL_X);

	//new PILabel(hEventFrame, "Registry Entry:", PI_LAYOUT_RIGHT);
	//PITextField* registryEntryTextField = new PITextField(hEventFrame, 20, CreateCallback(this, &HotKeyDialog::onCmdRegistryChanged), PI_LAYOUT_FILL_X);
	//new PILabel(hEventFrame, "Host Command Line:", PI_LAYOUT_RIGHT);
	//PITextField* commandLineText = new PITextField(hEventFrame, 20, NULL, PI_LAYOUT_FILL_X);
	//// Create the buttons
	//new PIButton(vFrame, "Data", CreateCallback(this, &HotKeyDialog::onCmdData), PI_LAYOUT_FILL_X);
	//new PIButton(vFrame, "GUI", CreateCallback(this, &HotKeyDialog::onCmdGUI), PI_LAYOUT_FILL_X);
	//new PIButton(vFrame, "Mouse", CreateCallback(this, &HotKeyDialog::onCmdMouse), PI_LAYOUT_FILL_X);
	//new PIButton(vFrame, "Common", CreateCallback(this, &HotKeyDialog::onCmdCommon), PI_LAYOUT_FILL_X);
	//PIButton* plotXyButton = new PIButton(vFrame, "Plot-XY", CreateCallback(this, &HotKeyDialog::onCmdPlotXY), PI_LAYOUT_FILL_X);
	//PIButton* simdisButton = new PIButton(vFrame, "SIMDIS", CreateCallback(this, &HotKeyDialog::onCmdSIMDIS), PI_LAYOUT_FILL_X);
	//new PIButton(vFrame, "Command Line", CreateCallback(this, &HotKeyDialog::onCmdCommandLine), PI_LAYOUT_FILL_X);
	//new PIButton(vFrame, "Tabs", CreateCallback(this, &HotKeyDialog::onCmdTabs), PI_LAYOUT_FILL_X);
	//// Create a close button
	//new PIButton(vFrame, "Close", CreateCallback(this, &HotKeyDialog::onCmdClose), PI_LAYOUT_RIGHT);
	//PIHorizontalFrame* hDockableFrame = new PIHorizontalFrame(vFrame, PI_LAYOUT_FILL_X | PI_LAYOUT_FILL_Y);
	//dockableCheck_ = new PICheckButton(hDockableFrame, "Dockable\tSet the dockable state of the dialog", CreateCallback(this, &HotKeyDialog::onCmdDockableChanged), PI_ALL_NORMAL | PI_LAYOUT_FILL_X);
	//PICheckButton* canBeDockable = new PICheckButton(hDockableFrame, "Can Be Dockable\tSet the ability of this dialog to be dockable", CreateCallback(this, &HotKeyDialog::onCmdCanBeDockableChanged), PI_ALL_NORMAL | PI_LAYOUT_FILL_X);
	//dockableCheck_->setCheck(HotKeyDialog_->isDockable());
	//canBeDockable->setCheck(HotKeyDialog_->canBeDockable());
	//if (!HotKeyDialog_->canBeDockable())
	//	dockableCheck_->disable();

	// Set up the event text field
	hotkeydugoutTextField_->disable();
	hotkeydugoutTextField_->setValue("");
	
	// Fill out the registry entry
	//std::string regEntry = PIRegistry::getValue(REGISTRY_KEY);
	//if (regEntry.size() > 0)
	//	registryEntryTextField->setValue(regEntry);
	//// Set the value for the version fields, and disable them
	//hostText->disable();
	//hostText->setValue(getApplicationName());
	//hostVerText->disable();
	//hostVerText->setValue(getApplicationVersion());
	//hostPlugVerText->disable();
	//hostPlugVerText->setValue(getApplicationPluginVersionBuildNumber());
	//commandLineText->disable();
	//std::stringstream cmdLineStr;
	//std::vector<std::string> allArgs = args.commandLine();
	//for (std::vector<std::string>::const_iterator argsIter = allArgs.begin(); argsIter != allArgs.end(); ++argsIter)
	//	cmdLineStr << *argsIter << " ";
	//commandLineText->setValue(cmdLineStr.str());
	//localVer->disable();
	//localVer->setValue(PIBase::buildNumber());
	//// Disable the buttons that are not valid, depending on our host
	//if (!PISIMDIS::runningInSIMDIS() && !PISIMDIS::runningInSIMDIS10())
	//	simdisButton->disable();
	//if (!PIPlotXY::runningInPlotXY() && !PIPlotXY::runningInPlotXY10())
	//	plotXyButton->disable();

	observer_ = new HotKeyCloseObserver(this);

	// Create the child dialog boxes
	//dataDialog_ = new DataDialog("PIData Sample", NULL);
	//guiDialog_ = new GUIDialog("PIGUI Sample", NULL);
	//mouseDialog_ = new MouseDialog("PIGUI::PIMouse.h Sample", NULL);
	//commonDialog_ = new CommonDialog("PICommon Sample", NULL);
	//plotXYDialog_ = new PlotXYDialog("PIPlotXY Sample", NULL);
	//simdisDialog_ = new SIMDISDialog("PISIMDIS Sample", NULL);
	//tabsDialog_ = new TabsDialog;

	// now register the close observer
	//dataDialog_->registerCloseObserver(observer_);
	//guiDialog_->registerCloseObserver(observer_);
	//mouseDialog_->registerCloseObserver(observer_);
	//commonDialog_->registerCloseObserver(observer_);
	//plotXYDialog_->registerCloseObserver(observer_);
	//simdisDialog_->registerCloseObserver(observer_);

	// Create and register our context menu observer
	/*lastRightClickId_ = 0;
	rightClickObserver_ = new RightClickObserver(*this);*/
	// Note that here we don't care about the return value, since SIMDIS 10 compatibility is automatic
	/*PISIMDIS::registerContextMenuCallback(rightClickObserver_);*/

	return 0;
}

/**
* Update all child dialogs here.  This function is called every loop
* by SIMDIS as possible
* @return 0 on success
*/
int HotKeyDialog::Callback()
{
	//if (guiDialog_)
	//	guiDialog_->doCallback();
	//if (commonDialog_)
	//	commonDialog_->doCallback();
	//if (simdisDialog_)
	//	simdisDialog_->doCallback();
	return 0;
}

/**
* Handles closing the application, called by SIMDIS automatically
* @return 0 on success
*/
int HotKeyDialog::Close()
{
	// Remove our right-click observer
	/*PISIMDIS::removeContextMenuCallback(rightClickObserver_);*/

	/*if (guiDialog_)
	{
		guiDialog_->unregisterCloseObserver(observer_);
		delete guiDialog_;
	}
	guiDialog_ = NULL;
	if (commonDialog_)
	{
		commonDialog_->unregisterCloseObserver(observer_);
		delete commonDialog_;
	}
	commonDialog_ = NULL;
	if (simdisDialog_)
	{
		simdisDialog_->unregisterCloseObserver(observer_);
		delete simdisDialog_;
	}
	simdisDialog_ = NULL;
	if (dataDialog_)
	{
		dataDialog_->unregisterCloseObserver(observer_);
		delete dataDialog_;
	}
	dataDialog_ = NULL;
	if (plotXYDialog_)
	{
		plotXYDialog_->unregisterCloseObserver(observer_);
		delete plotXYDialog_;
	}
	plotXYDialog_ = NULL;
	if (mouseDialog_)
	{
		mouseDialog_->unregisterCloseObserver(observer_);
		delete mouseDialog_;
	}
	mouseDialog_ = NULL;*/

	delete observer_;
	observer_ = NULL;

	return 0;
}

/**
* Show the dialog, this is called by our custom menu function
*/
long HotKeyDialog::onCmdShowDialog(PIObject*, void*)
{
	HotKeyDialog_->show();
	static const std::string PREFIX = "P5/HA-";
	std::string plat_name;
	plat_name = PREFIX + std::to_string(1);

	PIData::UniqueID_t entityID = PIData::findPlatform("P5/HA-1");
	hotkeydugoutTextField_->setValue(std::to_string(entityID)); 
	PIData::PICategoryDataPoint datapoint;
	datapoint.category = "DeadOrAlive";
	datapoint.value = "Dead";
	PIData::addCategoryData(entityID, &datapoint);
	return 0;
}
//
///**
//* Called when the user clicks Data
//*/
//long HotKeyDialog::onCmdData(PIObject*, void*)
//{
//	//dataDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks GUI
//*/
//long HotKeyDialog::onCmdGUI(PIObject*, void*)
//{
//	//guiDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks Mouse
//*/
//long HotKeyDialog::onCmdMouse(PIObject*, void*)
//{
//	//mouseDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks PlotXY
//*/
//long HotKeyDialog::onCmdPlotXY(PIObject*, void*)
//{
//	//plotXYDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks SIMDIS
//*/
//long HotKeyDialog::onCmdSIMDIS(PIObject*, void*)
//{
//	//simdisDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks Common
//*/
//long HotKeyDialog::onCmdCommon(PIObject*, void*)
//{
//	//commonDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks Tabs button
//*/
//long HotKeyDialog::onCmdTabs(PIObject*, void*)
//{
//	//tabsDialog_->show();
//	return 0;
//}
//
///**
//* Called when the user clicks Close
//*/
//long HotKeyDialog::onCmdClose(PIObject*, void*)
//{
//	HotKeyDialog_->hide();
//	return 0;
//}

/**
* Receives event update notifications
* @param eventType Type of event heard
* @param data Data associated with the event if any
*/
void HotKeyDialog::listenToEvents(PIApplicationEvents_t eventType, void* data)
{
	//switch (eventType)
	//{
	//case PI_APPEVENT_CRITEXIT:
	//	eventTextField_->setValue("Critical Exit");
	//	break;
	//case PI_APPEVENT_LOADFILE:
	//	eventTextField_->setValue("File loaded.");
	//	break;
	//case PI_APPEVENT_CLOSEFILE:
	//	eventTextField_->setValue("File closed.");
	//	break;
	//case PI_APPEVENT_REMOVEOBJECT:
	//	eventTextField_->setValue("Scenario object removed.");
	//	break;
	//case PI_APPEVENT_ADDPLATFORM:
	//	eventTextField_->setValue("Scenario platform added.");
	//	break;
	//case PI_APPEVENT_ADDBEAM:
	//	eventTextField_->setValue("Scenario beam added.");
	//	break;
	//case PI_APPEVENT_ADDGATE:
	//	eventTextField_->setValue("Scenario gate added.");
	//	break;
	//case PI_APPEVENT_ADDLASER:
	//	eventTextField_->setValue("Scenario laser added.");
	//	break;
	//case PI_APPEVENT_ADDLOB:
	//	eventTextField_->setValue("Scenario line of bearing added.");
	//	break;
	//case PI_APPEVENT_SERVERSTATUS:
	//	eventTextField_->setValue("Server Status changed.");
	//	break;
	//case PI_APPEVENT_MOTIONSTOP:
	//	eventTextField_->setValue("Motion frame/time finished for viewport.");
	//	break;
	//case PI_APPEVENT_DELETEVIEWPORT:
	//	eventTextField_->setValue("Viewport deleted.");
	//	break;
	//case PI_APPEVENT_FLUSHDATA:
	//	if (data == NULL || *static_cast<uint64_t*>(data) == 0)
	//		eventTextField_->setValue("Scenario flush event.");
	//	else
	//		eventTextField_->setValue("Entity flush event.");
	//	break;
	//case PI_APPEVENT_LIVETOFILE:
	//	eventTextField_->setValue("Scenario switched from live to file mode");
	//	break;
	//default:
	//	eventTextField_->setValue("Unknown event.");
	//	break;
	//}
}

///**
//* Saves the typed-in value to the registry; only applicable
//* when called by a PITextField sender object
//* @param sender Pointer to a PITextField that has just changed, which contains text to save to the registry
//* @param data Nothing
//* @return 0
//*/
//long HotKeyDialog::onCmdRegistryChanged(PIObject* sender, void* data)
//{
//	PITextField* textField = (PITextField*)sender;
//	if (sender != NULL)
//	{
//		// Fill out the registry entry
//		std::string oldValue = PIRegistry::getValue(REGISTRY_KEY);
//		std::string newValue = textField->getValueText();
//		if (oldValue != newValue)
//		{
//			PIRegistry::setValue(REGISTRY_KEY, textField->getValueText());
//			std::string textToShow = "Successfully saved value to registry: ";
//			textToShow += newValue;
//			debugMsgBox("Successful Save!", textToShow);
//		}
//	}
//	return 0;
//}
//
//long HotKeyDialog::onCmdDockableChanged(PIObject* sender, void* data)
//{
//	bool dockable = (static_cast<PICheckButton*>(sender)->getValueInt() != 0);
//	HotKeyDialog_->setDockable(dockable);
//	return 1;
//}
//
//long HotKeyDialog::onCmdCanBeDockableChanged(PIObject* sender, void* data)
//{
//	bool canBeDocked = (static_cast<PICheckButton*>(sender)->getValueInt() != 0);
//	HotKeyDialog_->setCanBeDockable(canBeDocked);
//	canBeDocked ? dockableCheck_->enable() : dockableCheck_->disable();
//	// Refresh the value of isDockable
//	dockableCheck_->setValue(HotKeyDialog_->isDockable());
//	return 1;
//}
//
///**
//* Processes mouse events from the host
//*/
//int HotKeyDialog::handleMouseEvent(PIGUI::PIMouseEventType_t eventType, const PIGUI::PIMouseEvent& eventData)
//{
//	//return mouseDialog_->handleMouseEvent(eventType, eventData);
//	return 0;
//}
//
//long HotKeyDialog::onCmdContextMenuPopup(PIObject*, void*)
//{
//	// This method gets called by the right-click menu when the item from RightClickObserver
//	// is pressed by the user.  RightClickObserver will have already set up at this point our
//	// lastRightClickId_, so we can just pull data out from SIMDIS and display it.
//	PIData::PIPlatformHeader hdr;
//	std::stringstream ss;
//	if (PIData::getHeader(lastRightClickId_, &hdr) != 0)
//	{
//		ss << "Unable to retrieve data for platform with ID " << lastRightClickId_;
//		PICommon::showToastNotification(ss.str(), PICommon::TOASTDURATION_LONG);
//	}
//	else
//	{
//		ss << "Right-clicked on \"" << hdr.callsign << "\", with ID " << lastRightClickId_;
//		PICommon::showToastNotification(ss.str(), PICommon::TOASTDURATION_LONG);
//	}
//	return 1;
//}
//
//long HotKeyDialog::onCmdShowMiniMap(PIObject*, void*)
//{
//	if (!PICommon::doesActionExist(MINI_MAP_ACTION_NAME))
//		return 1;
//	const bool isCurrentlyShown = PICommon::isActionChecked(MINI_MAP_ACTION_NAME);
//	if (!isCurrentlyShown)
//		PICommon::executeAction(MINI_MAP_ACTION_NAME);
//	return 1;
//}
//
//long HotKeyDialog::onCmdHideMiniMap(PIObject*, void*)
//{
//	if (!PICommon::doesActionExist(MINI_MAP_ACTION_NAME))
//		return 1;
//	const bool isCurrentlyShown = PICommon::isActionChecked(MINI_MAP_ACTION_NAME);
//	if (isCurrentlyShown)
//		PICommon::executeAction(MINI_MAP_ACTION_NAME);
//	return 1;
//}
//
//long HotKeyDialog::onCmdSuperForm(PIObject*, void*)
//{
//	if (PICommon::doesActionExist(SUPER_FORM_ACTION_NAME))
//		PICommon::executeAction(SUPER_FORM_ACTION_NAME);
//	return 1;
//}
//
//long HotKeyDialog::onCmdPrefRules(PIObject*, void*)
//{
//	if (PICommon::doesActionExist(PREF_RULES_ACTION_NAME))
//		PICommon::executeAction(PREF_RULES_ACTION_NAME);
//	return 1;
//}
//
//long HotKeyDialog::onCmdCommandLine(PIObject*, void*)
//{
//	if (cmdLineArguments_)
//		handleArgs_(*cmdLineArguments_);
//	return 1;
//}
//
//void HotKeyDialog::handleArgs_(const PIApp::CommandLineArguments& args)
//{
//	// Demonstrates the parsing of several command line arguments
//	std::stringstream argStream;
//	argStream << "This plug-in registers several command line arguments with the host application.\n"
//		<< "The following is a listing of command line arguments detected.\n\n";
//	argStream << "-TestFlag1 was " << (args.isFlagSet("TestFlag1") ? "set" : "not set") << "\n";
//	argStream << "-TestFlag2 was " << (args.isFlagSet("TestFlag2") ? "set" : "not set") << "\n";
//
//	if (!args.getParameter("TestParam1").empty())
//		argStream << "-TestParam1 => " << args.getParameter("TestParam1") << "\n";
//	else
//		argStream << "-TestParam1 was not set\n";
//
//	if (!args.getParameter("file").empty())
//		argStream << "-file => " << args.getParameter("file") << "\n";
//	else
//		argStream << "-file was not set\n";
//
//	if (args.getVector("TestVec").empty())
//		argStream << "-TestVec was not set\n";
//	else
//	{
//		// Note that the vector is copied, else iteration could segfault because getVector() returns a copy
//		std::vector<std::string> vec = args.getVector("TestVec");
//		argStream << "-TestVec has " << vec.size() << " items:\n";
//		for (size_t k = 0; k < vec.size(); ++k)
//		{
//			argStream << "  [" << k << "] => " << vec[k] << "\n";
//		}
//	}
//
//	// Show the message in a popup
//	PICommon::debugMsgBox("Test Plug-in Arguments", argStream.str());
//}

long HotKeyDialog::onPress1(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "1");
	PICommon::debugPrint("1");
	return 0;
}
long HotKeyDialog::onPress2(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "2");
	return 0;
}
long HotKeyDialog::onPress3(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "3");
	return 0;
}
long HotKeyDialog::onPress4(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "4");
	return 0;
}
long HotKeyDialog::onPress5(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "5");
	return 0;
}
long HotKeyDialog::onPress6(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "6");
	return 0;
}
long HotKeyDialog::onPress7(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "7");
	return 0;
}
long HotKeyDialog::onPress8(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "8");
	return 0;
}
long HotKeyDialog::onPress9(PIObject *, void *)
{
	std::string lastletter = std::string(1, (hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "9");
	return 0;
}
long HotKeyDialog::onPress0(PIObject *, void *)
{
	std::string lastletter = std::string(1,(hotkeydugoutTextField_->getValueText().back()));

	hotkeydugoutTextField_->setValue(lastletter + "0");
	return 0;
}
long HotKeyDialog::onPressKill(PIObject *, void *)
{
	//static const std::string PREFIX = "P5/HA-";
	std::string slotNum = hotkeydugoutTextField_->getValueText();
	//std::string plat_name;
	//plat_name = PREFIX + digits;

	//PIData::UniqueID_t entityID = PIData::findPlatform(plat_name);
	//
	//PIData::PICategoryDataPoint datapoint;
	//datapoint.category = "DeadOrAlive";
	//datapoint.value = "Dead";
	//PIData::addCategoryData(entityID, datapoint);


	std::string catToSearch = "Track Slot";

	PICommon::notify("find category match");
	PIData::UniqueID_t matchedPod =	findCategoryMatch(catToSearch, slotNum);
	PICommon::notify(std::to_string(matchedPod));
	if (matchedPod != 0)
	{
		PIData::PICategoryDataPoint datapoint;
		datapoint.category = "DeadOrAlive";
		datapoint.value = "Dead";
		PIData::addCategoryData(matchedPod, &datapoint);
	}
	else
	{
		PICommon::notify("No pod match");
	}
	
	hotkeydugoutTextField_->setValue("KILL " + slotNum);
	return 0;
}

PIData::UniqueID_t HotKeyDialog::findCategoryMatch(std::string category, std::string value)
{
	PICommon::notify("get platform list");
	std::vector<PIData::UniqueID_t> platList;
	PIData::getPlatformList(&platList);

	PIData::UniqueID_t matchedPlat;
	bool findMatch = false;

	PICommon::notify("platforms: " + std::to_string(platList.size()));
	for ( auto &it : platList)
	{
		PICommon::notify("get category data");
		std::map<std::string, std::string> catList;
		PIData::retrieveCurrentCategoryData(it, &catList);

		PICommon::notify(std::to_string(catList.size()));

		try
		{
			std::string v;
			v = catList.at(category);
			PICommon::notify(v + " " + value);
			if (v == value)
			{
				matchedPlat = it;
				findMatch = true;
				break;
			}
			
			
		}
		catch (const std::exception&)
		{
			PICommon::notify("did not find category " + category);
		}
		
		
	}
	if (!findMatch) matchedPlat = 0;

	return matchedPlat;
}


//void HotKeyDialog::dialogClosed_(PIGUI::PIDialogBox * dialog)
//{
//}
//
//void HotKeyDialog::listenToEvents(PIApplicationEvents_t eventType, void * data)
//{
//}