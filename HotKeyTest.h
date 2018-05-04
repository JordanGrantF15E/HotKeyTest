/* -*- mode: c++ -*- */
/****************************************************************************
*****                                                                  *****
*****                   Classification: UNCLASSIFIED                   *****
*****                    Classified By:                                *****
*****                    Declassify On:                                *****
*****                                                                  *****
****************************************************************************
*
*
* Based on example Developed by: Naval Research Laboratory, Tactical Electronic Warfare Div.
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
#ifndef HOTKEYTEST_H
#define HOTKEYTEST_H

#include "PIIncludes.h"

// Forward declarations
//class GUIDialog;
//class DataDialog;
//class CommonDialog;
//class SIMDISDialog;
//class PlotXYDialog;
//class MouseDialog;
//class TabsDialog;

/**
* Class to serve as the central point for a sample
* plug-in application that will exemplify most function
* calls in the library
*/
class GeneralDialog : public PIApplication
{
protected:
	// PIDialogBox close observer for receiving close events
	class GeneralCloseObserver;

	// called by CloseObserver when a dialog is closed
	void dialogClosed_(PIGUI::PIDialogBox* dialog);

	///Local dialog box
	PIGUI::PIDialogBox* generalDialog_;
	///Contains the most recent system event
	PIGUI::PITextField* eventTextField_;
	///Pointer to the Dockable check box
	PIGUI::PICheckButton* dockableCheck_;

	///PIGUI namespace sample dialog
//	GUIDialog* guiDialog_;
	///PIData namespace sample dialog
//	DataDialog* dataDialog_;
	///PICommon namespace sample dialog
//	CommonDialog* commonDialog_;
	///PISIMDIS namespace sample dialog
//	SIMDISDialog* simdisDialog_;
	///PIPlotXY namespace sample dialog
//	PlotXYDialog* plotXYDialog_;
	///PIGUI::PIMouse.h sample dialog
//	MouseDialog* mouseDialog_;
	///Tabs demo sample dialog
//	TabsDialog* tabsDialog_;
	/// close event observer
	GeneralCloseObserver* observer_;

	/// Last entity ID selected with the context menu
	PIData::UniqueID_t lastRightClickId_;
	/// Observer for right-click context menu requests
	class RightClickObserver;
	RightClickObserver* rightClickObserver_;

	/// Passed at StartUp(), used to query command line arguments
	const PIApp::CommandLineArguments* cmdLineArguments_;

	/// Helper method to handle command line arguments from StartUp()
	void handleArgs_(const PIApp::CommandLineArguments& args);

public:
	///Constructor for our startup application
	GeneralDialog() :
		PIApplication(),
		generalDialog_(NULL),
		eventTextField_(NULL),
		dockableCheck_(NULL),
	//	guiDialog_(NULL),
	//	dataDialog_(NULL),
	//	commonDialog_(NULL),
	//	simdisDialog_(NULL),
	//	plotXYDialog_(NULL),
	//	mouseDialog_(NULL),
	//	tabsDialog_(NULL),
		observer_(NULL),
		lastRightClickId_(0),
		rightClickObserver_(NULL),
		cmdLineArguments_(NULL)
	{}
	///Virtual destructor
	virtual ~GeneralDialog() {}

	///Register some command line arguments for example's sake
	virtual int ConfigureCommandLine(PIApp::CommandLineRegistration& cmdLine) const;

	///Override StartUp() to provide constructor-esque functionality
	virtual int StartUp(const PIApp::CommandLineArguments& args);
	///Override Callback() for idle looping
	virtual int Callback();
	///Override Close() for destructor-esque functionality
	virtual int Close();
	///Return the name of the application
	virtual std::string Name() { return "Hot Key Test"; }

	virtual std::string Version() const { return "0.0"; }
	virtual std::string Author() const { return "Gadget"; }
	virtual std::string Description() const { return "Experimental."; }
	virtual std::string URL() const { return " "; }
	virtual std::string ContactInfo() const { return "jordangrantf15e@yahoo.com"; }

	//These are declarations for each number button
	long onPress1(PIObject*, void*);
	long onPress2(PIObject*, void*);
	long onPress3(PIObject*, void*);
	long onPress4(PIObject*, void*);
	long onPress5(PIObject*, void*);
	long onPress6(PIObject*, void*);
	long onPress7(PIObject*, void*);
	long onPress8(PIObject*, void*);
	long onPress9(PIObject*, void*);
	long onPress0(PIObject*, void*);
	long onPressKill(PIObject*, void*);

	///Handles menu item command
	long onCmdShowDialog(PIObject*, void*);
	///Handles button presses for Data button
	long onCmdData(PIObject*, void*);
	///Handles button presses for GUI button
	long onCmdGUI(PIObject*, void*);
	///Handles button presses for PlotXY button
	long onCmdPlotXY(PIObject*, void*);
	///Handles button presses for SIMDIS button
	long onCmdSIMDIS(PIObject*, void*);
	///Handles button presses for Mouse button
	long onCmdMouse(PIObject*, void*);
	///Handles button presses for Common button
	long onCmdCommon(PIObject*, void*);
	///Tabs demo
	long onCmdTabs(PIObject*, void*);
	///Handles button presses for Command Line Options button
	long onCmdCommandLine(PIObject*, void*);
	///Handles the "close" button
	long onCmdClose(PIObject*, void*);
	///Called when user changes the registry text field
	long onCmdRegistryChanged(PIObject*, void*);
	///Called when user hits dockable toggle
	long onCmdDockableChanged(PIObject*, void*);
	///Called when user hits dockable toggle
	long onCmdCanBeDockableChanged(PIObject*, void*);

	///Called by the right-click context menu, for SIMDIS 10
	long onCmdContextMenuPopup(PIObject*, void*);
	///Referred to by the right-click context menu for SIMDIS 10
	long onCmdShowMiniMap(PIObject*, void*);
	///Referred to by the right-click context menu for SIMDIS 10
	long onCmdHideMiniMap(PIObject*, void*);
	///Referred to by the right-click context menu for SIMDIS 10
	long onCmdSuperForm(PIObject*, void*);
	///Referred to by the right-click context menu for SIMDIS 10
	long onCmdPrefRules(PIObject*, void*);

	///Processes mouse events from the host
	int handleMouseEvent(PIGUI::PIMouseEventType_t eventType, const PIGUI::PIMouseEvent& eventData);

	///Listens to events from SIMDIS
	void listenToEvents(PIApplicationEvents_t eventType, void* data);
};

#endif /* GENERALDIALOG_H */
