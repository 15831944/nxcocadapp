//==============================================================================
//  WARNING!!  This file is overwritten by the Block UI Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  D:\CollaborativeFramework_20160404\nxcocadapp\NXCoCADTest.cpp
//
//        This file was generated by the NX Block UI Styler
//        Created by: NicholasWang
//              Version: NX 8.5
//              Date: 04-12-2016  (Format: mm-dd-yyyy)
//              Time: 13:46 (Format: hh-mm)
//
//==============================================================================

//==============================================================================
//  Purpose:  This TEMPLATE file contains C++ source to guide you in the
//  construction of your Block application dialog. The generation of your
//  dialog file (.dlx extension) is the first step towards dialog construction
//  within NX.  You must now create a NX Open application that
//  utilizes this file (.dlx).
//
//  The information in this file provides you with the following:
//
//  1.  Help on how to load and display your Block UI Styler dialog in NX
//      using APIs provided in NXOpen.BlockStyler namespace
//  2.  The empty callback methods (stubs) associated with your dialog items
//      have also been placed in this file. These empty methods have been
//      created simply to start you along with your coding requirements.
//      The method name, argument list and possible return values have already
//      been provided for you.
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "NXCoCADTest.hpp"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(NXCoCADTest::theSession) = NULL;
UI *(NXCoCADTest::theUI) = NULL;
static Features::PointFeature * CreatePointFeature( double coord[3] );
static Point * CreatePoint( double coord[3] );
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
NXCoCADTest::NXCoCADTest()
{
    try
    {
        // Initialize the NX Open C++ API environment
        NXCoCADTest::theSession = NXOpen::Session::GetSession();
        NXCoCADTest::theUI = UI::GetUI();
        theDlxFileName = "NXCoCADTest.dlx";
        theDialog = NXCoCADTest::theUI->CreateDialog(theDlxFileName);
        // Registration of callback functions
        theDialog->AddApplyHandler(make_callback(this, &NXCoCADTest::apply_cb));
        theDialog->AddOkHandler(make_callback(this, &NXCoCADTest::ok_cb));
        theDialog->AddUpdateHandler(make_callback(this, &NXCoCADTest::update_cb));
        theDialog->AddInitializeHandler(make_callback(this, &NXCoCADTest::initialize_cb));
        theDialog->AddDialogShownHandler(make_callback(this, &NXCoCADTest::dialogShown_cb));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        throw;
    }
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
NXCoCADTest::~NXCoCADTest()
{
    if (theDialog != NULL)
    {
        delete theDialog;
        theDialog = NULL;
    }
}
//------------------------------- DIALOG LAUNCHING ---------------------------------
//
//    Before invoking this application one needs to open any part/empty part in NX
//    because of the behavior of the blocks.
//
//    Make sure the dlx file is in one of the following locations:
//        1.) From where NX session is launched
//        2.) $UGII_USER_DIR/application
//        3.) For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//            recommended. This variable is set to a full directory path to a file 
//            containing a list of root directories for all custom applications.
//            e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_ROOT_DIR\menus\custom_dirs.dat
//
//    You can create the dialog using one of the following way:
//
//    1. USER EXIT
//
//        1) Create the Shared Library -- Refer "Block UI Styler programmer's guide"
//        2) Invoke the Shared Library through File->Execute->NX Open menu.
//
//------------------------------------------------------------------------------
extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
    NXCoCADTest *theNXCoCADTest = NULL;
    try
    {
        theNXCoCADTest = new NXCoCADTest();
        // The following method shows the dialog immediately
        theNXCoCADTest->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    if(theNXCoCADTest != NULL)
    {
        delete theNXCoCADTest;
        theNXCoCADTest = NULL;
        //Terminate();
    }
}

//------------------------------------------------------------------------------
// This method specifies how a shared image is unloaded from memory
// within NX. This method gives you the capability to unload an
// internal NX Open application or user  exit from NX. Specify any
// one of the three constants as a return value to determine the type
// of unload to perform:
//
//
//    Immediately : unload the library as soon as the automation program has completed
//    Explicitly  : unload the library from the "Unload Shared Image" dialog
//    AtTermination : unload the library when the NX session terminates
//
//
// NOTE:  A program which associates NX Open applications with the menubar
// MUST NOT use this option since it will UNLOAD your NX Open application image
// from the menubar.
//------------------------------------------------------------------------------
extern "C" DllExport int ufusr_ask_unload()
{
    //return (int)Session::LibraryUnloadOptionExplicitly;
    return (int)Session::LibraryUnloadOptionImmediately;
    //return (int)Session::LibraryUnloadOptionAtTermination;
}

//------------------------------------------------------------------------------
// Following method cleanup any housekeeping chores that may be needed.
// This method is automatically called by NX.
//------------------------------------------------------------------------------
extern "C" DllExport void ufusr_cleanup(void)
{
    try
    {
        //---- Enter your callback code here -----
        Terminate();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

int NXCoCADTest::Show()
{
    try
    {
        theDialog->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//---------------------Block UI Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void NXCoCADTest::initialize_cb()
{
    try
    {
        group0 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group0"));
        double0 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("double0"));
        double01 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("double01"));
        double02 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("double02"));
        button0 = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("button0"));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void NXCoCADTest::dialogShown_cb()
{
    try
    {
        //---- Enter your callback code here -----
        if(!Initialize())
        {
            NXCoCADTest::theUI->NXMessageBox()->Show("Iniliazation Failed", NXOpen::NXMessageBox::DialogTypeError, "Iniliazation Failed");
            return;
        }
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int NXCoCADTest::apply_cb()
{
    int errorCode = 0;
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int NXCoCADTest::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
    try
    {
        if(block == double0)
        {
            //---------Enter your code here-----------
        }
        else if(block == double01)
        {
            //---------Enter your code here-----------
        }
        else if(block == double02)
        {
            //---------Enter your code here-----------
        }
        else if(block == button0)
        {
            //---------Enter your code here-----------
            dCoordinate[0] = double0->Value();
            dCoordinate[1] = double01->Value();
            dCoordinate[2] = double02->Value();
            //stringstream ss;
            //ss<<dcoord[0];
            //string strResult;
            //ss>>strResult;
            //NXCoCADTest::theUI->NXMessageBox()->Show("ReadBlock", NXOpen::NXMessageBox::DialogTypeInformation, NXString(strResult.c_str()));
            Features::PointFeature *pPointFeature = NULL;
            pPointFeature = CreatePointFeature(dCoordinate);
            //vector<NXObject*> points = pPointFeature->GetEntities();
            //tag_t pointTag1 = NULL_TAG;
            //pointTag1 = points[0]->GetTag();
            //Point * testPoint = NULL;
            //testPoint = CreatePoint(dcoord);
            //tag_t pointTag2 = NULL_TAG;
            //pointTag2 = testPoint->GetTag();
            Json::Value jCoordinate;
            jCoordinate["CoordinateX"] = dCoordinate[0];
            jCoordinate["CoordinateY"] = dCoordinate[1];
            jCoordinate["CoordinateZ"] = dCoordinate[2];
            Json::FastWriter json_writer;
            string cmd = "websocket.Invoke('Test', ";
            cmd += json_writer.write(jCoordinate);
            cmd += ", function(){});";
            RunScript(cmd.c_str());
            
        }
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int NXCoCADTest::ok_cb()
{
    int errorCode = 0;
    try
    {
        errorCode = apply_cb();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Function Name: GetBlockProperties
//Description: Returns the propertylist of the specified BlockID
//------------------------------------------------------------------------------
PropertyList* NXCoCADTest::GetBlockProperties(const char *blockID)
{
    return theDialog->GetBlockProperties(blockID);
}

static Features::PointFeature * CreatePointFeature(double coord[3])
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());

    Point3d coordinates( coord[0], coord[1], coord[2]);
    Point *thePoint = NULL;
    thePoint = workPart->Points()->CreatePoint(coordinates);
    thePoint->SetVisibility(SmartObject::VisibilityOptionVisible);

    Features::Feature *nullFeatures_Feature(NULL);
    Features::PointFeatureBuilder *thePointFeatureBuilder = NULL;
    thePointFeatureBuilder = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
    thePointFeatureBuilder->SetPoint(thePoint);

    NXObject *theNXObject = NULL;
    theNXObject = thePointFeatureBuilder->Commit();

    thePointFeatureBuilder->Destroy();
    return (Features::PointFeature*)theNXObject;
}
static Point * CreatePoint( double coord[3] )
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());

    Point3d coordinates( coord[0], coord[1], coord[2]);
    Point *thePoint = NULL;
    thePoint = workPart->Points()->CreatePoint(coordinates);
    thePoint->SetVisibility(SmartObject::VisibilityOptionVisible);
    return thePoint;
}

bool Initialize(void)
{
    CHAR szMoudlePath[MAX_PATH];
    DWORD dwCurDirPathLen = GetModuleFileName(GetModuleHandle("NXCoCadTest_d.dll"), szMoudlePath, MAX_PATH);//para_opt.dll

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath_s( szMoudlePath, drive, dir, fname, ext );
    
    string JS_HOME_DIR = string(drive) + dir;

	string js_ext_dir = JS_HOME_DIR + "/js.ext";

	SetCurrentDirectory(js_ext_dir.c_str());

    bool bResult = Initialize(JS_HOME_DIR.c_str());//js_parse64.dll
    if(!bResult)
    {
        return false;
    }

    string ret = RunScript("comx.shell.IsWebSocketPortValid(30000);");
    //cout << szPortValid << endl;
    
    if (ret == "false")
    {
        return false;
    }

    ExecuteScriptFile("js/NXCoCADClient.js");

    Sleep(500);

   /* ret = RunScript("IsServiceConnected();");
    if (ret == "false")
    {
        Terminate();
        return false;
    }*/

    return true;
}

bool Terminate(void)
{
    Dispose();
    return true;
}