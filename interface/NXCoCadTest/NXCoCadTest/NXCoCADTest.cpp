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
#include "NXFunction.h"
#include "MainMenu.hpp"
#include "FileUtils.h"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;
using namespace std;


//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(NXCoCADTest::theSession) = NULL;
UI *(NXCoCADTest::theUI) = NULL;
static Features::PointFeature * CreatePointFeature( double coord[3] );
static Point * CreatePoint( double coord[3] );


//zuyuanzhang code
UI *myUI;// = UI::GetUI();
NXMessageBox *message;// = myUI->NXMessageBox();
static int taskNum = 1;
void createPoint(double x,double y,double z);
char task[100];
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


//Add lock while reading and writing
#define NUM_THREADS 5 //number of thread
DWORD WINAPI ThreadProc(LPVOID lpParameter);
class lockBase{  
protected:  

	friend class singleStance;  
	CRITICAL_SECTION cs;  

public :   
	lockBase(){  
		::InitializeCriticalSection(&cs);  
	}  
	void lock(){  
		::EnterCriticalSection(&cs);  
	}  
	void unlock(){  
		::LeaveCriticalSection(&cs);  
	}  
	~lockBase(){  
		::DeleteCriticalSection(&cs);  
	}  

}; 

double dCoordinate[3];
UINT g_timer_id = 0;

void timer_cb(HWND,UINT,UINT_PTR,DWORD)
{
	KillTimer(NULL,g_timer_id);

	int temp = 0;
	char buffer[300];
	//taskNum = 1;
	int num = 1;
	int currentNum = 0;
	int strLength = 0;
	UI *myUI = UI::GetUI();
	NXMessageBox *message = myUI->NXMessageBox();
	//Sleep(2000);
	//while(1)
	{
		currentNum = 0;
		lockBase* lockbase = new lockBase();  
		lockbase->lock();  
		ifstream in("Y:\\nxcocadapp\\data\\MessageQueue.log"); 
		lockbase->unlock(); 
		if (! in.is_open())  
		{ 
			message->Show("提示",NXMessageBox::DialogTypeQuestion,"failed");
		}  
		double x = 0,y = 0,z = 0;
		while (!in.eof() )  
		{  
			lockbase->lock();  
			in.getline (buffer,300);
			lockbase->unlock(); 
			/*message->Show("提示",NXMessageBox::DialogTypeQuestion,buffer);*/
			strLength = strlen(buffer);
			if (strLength > 0 && buffer[strLength - 1] == '#')
			{
				currentNum ++;
				if (currentNum == taskNum)
				{
					//sprintf(task,"%s",buffer);
					//message->Show("thread",NXMessageBox::DialogTypeQuestion,nn);
					//sprintf(nn,"%d",taskNum);
					//message->Show("读取出来的是",NXMessageBox::DialogTypeQuestion,buffer);
					
					realizeOperation(buffer);
					//message->Show("thread",NXMessageBox::DialogTypeQuestion,nn);
					//createPoint(x,y,z);
					//createSketch1();
					taskNum ++;
					break;
				}
			}
		}
		in.close();
		delete(lockbase);

		num ++;
		//Sleep(2000);
	}

	//message->Show("thread",NXMessageBox::DialogTypeQuestion,"aaaaaaa");


	g_timer_id = SetTimer(NULL,0,2000,timer_cb);
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
	taskNum = 1;
	char buffer[255];
	int temp;
	int i = 0;
	DWORD test = 0;    ///< 0 represents the first thread
	HANDLE handle;
	DWORD numThreadId = 0;
	myUI = UI::GetUI();
	message = myUI->NXMessageBox();

    try
    {
        //theNXCoCADTest = new NXCoCADTest();
		//handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)&test, 0, &numThreadId);

        // The following method shows the dialog immediately
        //theNXCoCADTest->Show();
        //if(bTimerEnable)
        //{
            //KillTimer(NULL, nTimerID);
        //}
		g_timer_id = SetTimer(NULL, 0 ,2000, timer_cb);
		if(!Initialize())
		{
			NXCoCADTest::theUI->NXMessageBox()->Show("Iniliazation Failed", NXOpen::NXMessageBox::DialogTypeError, "Iniliazation Failed");
			return;
		}
		 MainMenu *theMainMenu = NULL;
		 theMainMenu = new MainMenu();
		 theMainMenu->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        NXCoCADTest::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }


	if (handle)
	{
		message->Show("提示",NXMessageBox::DialogTypeQuestion,"delete subThread");
		CloseHandle(handle);
	}


    if(theNXCoCADTest != NULL)
    {
        delete theNXCoCADTest;
        theNXCoCADTest = NULL;
        //if(bTimerEnable)
        //{
        //    KillTimer(NULL, nTimerID);
        //}
        Terminate();
        //Terminate();
    }
	KillTimer(NULL,g_timer_id);
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
        //Terminate();
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
            
            //CreatePoint
            //Json::Value jCoordinate;
            //jCoordinate["CoordinateX"] = dCoordinate[0];
            //jCoordinate["CoordinateY"] = dCoordinate[1];
            //jCoordinate["CoordinateZ"] = dCoordinate[2];
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('CreatePoint', ";
            //cmd += json_writer.write(jCoordinate);

            //CreateRect
            //Json::Value jsonPara;
            //jsonPara["para1"] = dCoordinate[0];
            //jsonPara["para2"] = dCoordinate[1];
            //jsonPara["para3"] = dCoordinate[2];
            //jsonPara["para4"] = 4.4;
            //jsonPara["para5"] = 5.5;
            //jsonPara["overloadType"] = 1;
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('CreateRect', ";
            //cmd += json_writer.write(jsonPara);

            //CreateSketch
            //Json::Value jsonPara;
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('CreateSketch', ";
            //cmd += json_writer.write(jsonPara);

            //Extrude
            //Json::Value jsonPara;
            //jsonPara["height"] = dCoordinate[0];
            //jsonPara["lineNum"] = 2;
            //jsonPara["sketchNum"] = 3;
            //jsonPara["sketchID"] = 4;
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('Extrude', ";
            //cmd += json_writer.write(jsonPara);

            //CreatePlane
            //Json::Value jsonPara;
            //jsonPara["x"] = dCoordinate[0];
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('CreatePlane', ";
            //cmd += json_writer.write(jsonPara);

            //DrawCircle
            //Json::Value jsonPara;
            //jsonPara["x"] = dCoordinate[0];
            //jsonPara["y"] = dCoordinate[1];
            //jsonPara["z"] = dCoordinate[2];
            //jsonPara["r"] = dCoordinate[1];
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('DrawCircle', ";
            //cmd += json_writer.write(jsonPara);

            //CreateSketchOnExtrude
            //Json::Value jsonPara;
            //jsonPara["extrudeNum"] = 1;
            //jsonPara["str1"] = "How are you?";
            //jsonPara["str2"] = "I am fine thank you and you?";
            //Json::FastWriter json_writer;
            //string cmd = "websocket.Invoke('CreateSketchOnExtrude', ";
            //cmd += json_writer.write(jsonPara);

            //ReverseExtrude
            Json::Value jsonPara;
            jsonPara["sketchID"] = "11111111";
            jsonPara["sketchNum"] = "Howareyou?";
            jsonPara["extrudeLine"] = "Iamfinethankyouandyou?";
            jsonPara["targetExtrude"] = "you?";
            jsonPara["length"] = 1;
            Json::FastWriter json_writer;
            string cmd = "websocket.Invoke('ReverseExtrude', ";
            cmd += json_writer.write(jsonPara);

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
    //Activated Timer
    
	//if(!bTimerEnable)
    //{
        //bTimerEnable = true;
        //nTimerID = SetTimer(NULL, 0, nSampleTime, (TIMERPROC)TimerProc);
    //}
    //else
    //{
        //MessageBox(NULL, "SetTimer Failure!", "Error!", 0);
    //}

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



//Create Thread
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int temp = 0;
	char buffer[256];
	//taskNum = 1;
	int num = 1;
	int currentNum = 0;
	int strLength = 0;
	UI *myUI = UI::GetUI();
	NXMessageBox *message = myUI->NXMessageBox();
	Sleep(2000);
	while(1)
	{
		currentNum = 0;
		lockBase* lockbase = new lockBase();  
		ifstream in("Y:\\nxcocadapp\\data\\MessageQueue.log"); 
		if (! in.is_open())  
		{ 
			message->Show("提示",NXMessageBox::DialogTypeQuestion,"failed");
		}  
		double x = 0,y = 0,z = 0;
		while (!in.eof() )  
		{  

			in.getline (buffer,100);
			strLength = strlen(buffer);
			if (strLength > 0 && buffer[strLength - 1] == '#')
			{
				currentNum ++;
				char nn[12] = "";
				sprintf(nn,"%d",currentNum);
				x += 10;
				y += 10;
				if (currentNum == taskNum)
				{
					lockbase->lock();  
					sprintf(task,"%s",buffer);
					lockbase->unlock(); 
					//message->Show("thread",NXMessageBox::DialogTypeQuestion,nn);
					sprintf(nn,"%d",taskNum);
					//message->Show("thread",NXMessageBox::DialogTypeQuestion,nn);
					createPoint(x,y,z);
					taskNum ++;
					break;
				}
			}
		}
		in.close();
		delete(lockbase);

		num ++;
		Sleep(2000);
	}
	return 0;
}

//Create Point
void createPoint(double x,double y,double z)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Datum/Point->Point...
	// ----------------------------------------------

	Point3d p3d;
	Point* pp;
	Features::Feature *nullFeatures_Feature(NULL);
	Features::PointFeatureBuilder* pointFeatureBuilder1;
	NXObject *nXObject1;
	p3d=Point3d(x,y,z);
	pp=workPart->Points()->CreatePoint(p3d);
	//pp->SetName("point1");
	pp->SetVisibility(SmartObject::VisibilityOptionVisible);
	pointFeatureBuilder1=workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
	pointFeatureBuilder1->SetPoint(pp);
	nXObject1 = pointFeatureBuilder1->Commit();
	pointFeatureBuilder1->Destroy();

}

//void CALLBACK TimerProc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
//{
    //KillTimer(NULL, nTimerID);
    //MessageBox(NULL, "Timer!", "", 0);
    //nTimerID = SetTimer(NULL, 0, nSampleTime, (TIMERPROC)TimerProc);
//}
