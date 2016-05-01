/*****************************************************************************
**
** zuobanbian.cpp
**
** Description:
**     Contains Unigraphics entry points for the application.
**
*****************************************************************************/

/* Include files */
#if ! defined ( __hp9000s800 ) && ! defined ( __sgi ) && ! defined ( __sun )
#   include <strstream>
#   include <iostream>
    using std::ostrstream;
    using std::endl;    
    using std::ends;
    using std::cerr;
#else
#   include <strstream.h>
#   include <iostream.h>
#endif
#include <uf.h>
#include <uf_ui.h>
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/GeometricUtilities_OnPathDimensionBuilder.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/Preferences_SessionPreferences.hxx>
#include <NXOpen/Preferences_SessionSketch.hxx>
#include <NXOpen/ScCollector.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SelectIReferenceAxis.hxx>
#include <NXOpen/SelectISurface.hxx>
#include <NXOpen/SelectObject.hxx>
#include <NXOpen/Sketch.hxx>
#include <NXOpen/SketchAlongPathBuilder.hxx>
#include <NXOpen/SketchCollection.hxx>
#include <NXOpen/SketchInPlaceBuilder.hxx>
#include <NXOpen/TaggedObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <NXOpen/Update.hxx>
#include <NXOpen/Annotations_Dimension.hxx>
#include <NXOpen/Arc.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/CurveCollection.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/Features_DatumCsys.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/NXMatrix.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/Sketch.hxx>
#include <NXOpen/SketchDimensionalConstraint.hxx>
#include <NXOpen/SketchGeometricConstraint.hxx>

#include <NXOpen/Scalar.hxx>
#include <NXOpen/ScalarCollection.hxx>

#include <NXOpen/BasePart.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/CurveFeatureRule.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/DirectionCollection.hxx>
#include <NXOpen/DisplayableObject.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_ExtrudeBuilder.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_SketchFeature.hxx>
#include <NXOpen/GeometricUtilities_BooleanOperation.hxx>
#include <NXOpen/GeometricUtilities_Extend.hxx>
#include <NXOpen/GeometricUtilities_FeatureOffset.hxx>
#include <NXOpen/GeometricUtilities_FeatureOptions.hxx>
#include <NXOpen/GeometricUtilities_Limits.hxx>
#include <NXOpen/GeometricUtilities_MultiDraft.hxx>
#include <NXOpen/GeometricUtilities_SimpleDraft.hxx>
#include <NXOpen/GeometricUtilities_SmartVolumeProfileBuilder.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SectionCollection.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <NXOpen/Sketch.hxx>
#include <NXOpen/SketchCollection.hxx>
#include <NXOpen/Unit.hxx>

#include <NXOpen/DatumPlane.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/Features_DatumPlaneBuilder.hxx>
#include <NXOpen/Features_DatumPlaneFeature.hxx>
#include <NXOpen/Features_Extrude.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/IPlane.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/Edge.hxx>
#include <NXOpen/DatumCollection.hxx>
#include <NXOpen/DatumPlane.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/Edge.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_Extrude.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/GeometricUtilities_OnPathDimensionBuilder.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_SessionPreferences.hxx>
#include <NXOpen/Preferences_SessionSketch.hxx>
#include <NXOpen/ScCollector.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SelectIReferenceAxis.hxx>
#include <NXOpen/SelectISurface.hxx>
#include <NXOpen/SelectObject.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Sketch.hxx>
#include <NXOpen/SketchAlongPathBuilder.hxx>
#include <NXOpen/SketchCollection.hxx>
#include <NXOpen/SketchInPlaceBuilder.hxx>
#include <NXOpen/TaggedObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <NXOpen/UnitCollection.hxx>

#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>

#include <NXOpen/BasePart.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/BodyCollection.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/CurveFeatureRule.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/DirectionCollection.hxx>
#include <NXOpen/DisplayableObject.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_ExtrudeBuilder.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_SketchFeature.hxx>
#include <NXOpen/GeometricUtilities_BooleanOperation.hxx>
#include <NXOpen/GeometricUtilities_Extend.hxx>
#include <NXOpen/GeometricUtilities_FeatureOffset.hxx>
#include <NXOpen/GeometricUtilities_FeatureOptions.hxx>
#include <NXOpen/GeometricUtilities_Limits.hxx>
#include <NXOpen/GeometricUtilities_MultiDraft.hxx>
#include <NXOpen/GeometricUtilities_SimpleDraft.hxx>
#include <NXOpen/GeometricUtilities_SmartVolumeProfileBuilder.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SectionCollection.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Sketch.hxx>
#include <NXOpen/SketchCollection.hxx>
#include <NXOpen/Unit.hxx>
#include <uf_exit.h>
using namespace NXOpen;

#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

static int report_error( char *file, int line, char *call, int irc)
{
    if (irc)
    {
        char err[133],
             msg[133];

        sprintf(msg, "*** ERROR code %d at line %d in %s:\n+++ ",
            irc, line, file);
        UF_get_fail_message(irc, err);

        UF_print_syslog(msg, FALSE);
        UF_print_syslog(err, FALSE);
        UF_print_syslog("\n", FALSE);
        UF_print_syslog(call, FALSE);
        UF_print_syslog(";\n", FALSE);

        if (!UF_UI_open_listing_window())
        {
            UF_UI_write_listing_window(msg);
            UF_UI_write_listing_window(err);
            UF_UI_write_listing_window("\n");
            UF_UI_write_listing_window(call);
            UF_UI_write_listing_window(";\n");
        }
    }

    return(irc);
}


/*****************************************************************************
**  Activation Methods
*****************************************************************************/
/*  Unigraphics Startup
**      This entry point activates the application at Unigraphics startup */
char* getJournalId(char name[]);
char* getFeatureName(char name[]);
void createRect(double leftUpX,double leftUpY,double rightDownX,double rightDownY,double z);
void createSketch();
//void lashen(int height,int lineNum,int sketchNum,int sketchId,char name[]);
void createRect(double leftUpX,double leftUpZ,double rightDownX,double rightDownZ,double y,int id);
void createPlane(int x);
void drawCircle(double x,double y,double z,double r);
// void createSketchOnExtrude(int extrudeNum,char *str1,char *str2);
// void fanxianglashen(char *sketchId,char *sketchNum,char *lashenLine,char *targetExtrue,int length);
void unDo();



void lashen(int height,char targetSketchName[],char setName[]);
void fanxianglashen(char targetSketchName[],char targetExtrueName[],int length,char setName[]);
void createSketchOnExtrude(char targetExtrude[],char *str1,char *str2,char setName[]);



extern DllExport void ufsta( char *param, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    if( UF_CALL(UF_initialize()) ) 
    {
        /* Failed to initialize */
        return;
    }
	Session *theSession = Session::GetSession();

	createSketch();
	createRect(-50,20,50,-20,0);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	//lashen(5,1,0,1,"sanyuan1");
    lashen(5,"mainSketch","extrude1");
	//createSketchOnExtrude(2,"EDGE * 130 * 140 {(-9.5,-4.5,5)(-0,-4.5,5)(9.5,-4.5,5) EXTRUDE(2)}","FACE 130 {(-0,-4.5,0) EXTRUDE(2)}");
	createSketchOnExtrude("extrude1","EDGE * 130 * 140 {(50,20,5)(0,20,5)(-50,20,5) EXTRUDE(2)}","FACE 130 {(0,0,5) EXTRUDE(2)}","sketch1");
	createRect(-50,20,50,15,5);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	createSketchOnExtrude("extrude1","EDGE * 130 * 140 {(50,20,5)(0,20,5)(-50,20,5) EXTRUDE(2)}","FACE 130 {(0,0,5) EXTRUDE(2)}","sketch2");
	createRect(-50,-15,50,-20,5);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	//lashen(40,5,1,3,"zuyuan2");
	lashen(40,"sketch1","extrude2");
	lashen(40,"sketch2","extrude3");
	//createSketchOnExtrude(4,"EDGE * 150 * 210 {(-50,-20,45)(0,-20,45)(50,-20,45) EXTRUDE(4)}","FACE 210 {(0,-20,25) EXTRUDE(4)}");
	createSketchOnExtrude("extrude2","EDGE * 150 * 160 {(-50,20,45)(-50,20,25)(-50,20,5) EXTRUDE(5)}","FACE 160 {(0,20,25) EXTRUDE(5)}","sketch3");
	createRect(-25,45,50,15,20,1);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	//fanxianglashen("SKETCH(5)","SKETCH_002","Curve Line15","EXTRUDE(4)",5);FACE 160 {(0,20,25) EXTRUDE(5)}

	fanxianglashen("sketch3","extrude2",5,"fanxiang1");

	//createSketchOnExtrude(4,"EDGE * 120 * 160 {(50,20,5)(0,20,5)(-50,20,5) EXTRUDE(4)1}","FACE 160 {(0,20,25) EXTRUDE(4)1}");
	createSketchOnExtrude("extrude3","EDGE * 130 * 140 {(-50,-20,45)(0,-20,45)(50,-20,45) EXTRUDE(6)}","FACE 140 {(0,-20,25) EXTRUDE(6)}","sketch4");
	
	createRect(-25,45,50,15,-20,1);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	//fanxianglashen("SKETCH(7)","SKETCH_003","Curve Line19","EXTRUDE(4)1",5);

	fanxianglashen("sketch4","extrude3",5,"fanxiang2");

	//画圆
	//createSketchOnExtrude(4,"EDGE * 150 * 210 {(-50,-20,45)(0,-20,45)(50,-20,45) EXTRUDE(4)}","FACE 210 {(0,-20,25) EXTRUDE(4)}");

	createSketchOnExtrude("extrude3","EDGE * 130 * 140 {(-50,-20,45)(-37.5,-20,45)(-25,-20,45) EXTRUDE(6)}","FACE 140 {(0,-20,25) EXTRUDE(6)}","sketch5");

	drawCircle(-38.3834013613238, -20.0, 33.4279639846066,4);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);

	//createSketchOnExtrude(4,"EDGE * 120 * 160 {(50,20,5)(0,20,5)(-50,20,5) EXTRUDE(4)1}","FACE 160 {(0,20,25) EXTRUDE(4)1}");
	createSketchOnExtrude("extrude2","EDGE * 120 * 150","FACE 150","sketch6");

	drawCircle(-38.3834013613238, 20.0, 33.4279639846066,4);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);

	//fanxianglashen("SKETCH(9)","SKETCH_004","Curve Arc1","EXTRUDE(4)",5);
	//fanxianglashen("SKETCH(10)","SKETCH_005","Curve Arc2","EXTRUDE(4)1",5);
	fanxianglashen("sketch5","extrude3",5,"fanxiang3");
	fanxianglashen("sketch6","extrude2",5,"fanxiang4");

	//createSketchOnExtrude(2,"EDGE * 130 * 140 {(-9.5,-4.5,5)(-0,-4.5,5)(9.5,-4.5,5) EXTRUDE(2)}","FACE 130 {(-0,-4.5,0) EXTRUDE(2)}");
	createSketchOnExtrude("extrude1","EDGE * 130 * 140 {(50,20,5)(0,20,5)(-50,20,5) EXTRUDE(2)}","FACE 130 {(0,0,5) EXTRUDE(2)}","sketch7");

	drawCircle(22, 0, 5,4);
	drawCircle(36, 0.0, 5,4);
	theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
	//fanxianglashen("SKETCH(13)","SKETCH_006","Curve Arc3","EXTRUDE(2)",5);
	fanxianglashen("sketch7","extrude1",5,"fanxiang5");
	//fanxianglashen("SKETCH(13)","SKETCH_006","Curve Arc4","EXTRUDE(2)",5);
	//lashen(5,9,1,3);
	//createPlane(2);

	//unDo();
    
    /* TODO: Add your application code here */

    /* Terminate the API environment */
    UF_CALL(UF_terminate());
}

/*****************************************************************************
**  Utilities
*****************************************************************************/

/* Unload Handler
**     This function specifies when to unload your application from Unigraphics.
**     If your application registers a callback (from a MenuScript item or a
**     User Defined Object for example), this function MUST return
**     "UF_UNLOAD_UG_TERMINATE". */
extern "C" DllExport int ufusr_ask_unload()
{
	return (int)Session::LibraryUnloadOptionImmediately;
}


void lashen(int height,char targetSketchName[],char setName[])
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Design Feature->Extrude...
	// ----------------------------------------------
	// Session::UndoMarkId markId1;
	//markId1 = theSession->SetUndoMark(Session::MarkVisibilityVisible, "Start");

	Features::Feature *nullFeatures_Feature(NULL);

	if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
	{
		throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
	}

	Features::ExtrudeBuilder *extrudeBuilder1;
	extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(nullFeatures_Feature);

	Section *section1;

	UI *plmHomeUI = UI::GetUI();
	NXMessageBox *messageBox = plmHomeUI->NXMessageBox();

	section1 = workPart->Sections()->CreateSection(0,0,0);

	extrudeBuilder1->SetSection(section1);

	extrudeBuilder1->AllowSelfIntersectingSection(true);

	Unit *unit1;
	unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();


	extrudeBuilder1->SetDistanceTolerance(0.001);

	extrudeBuilder1->BooleanOperation()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeCreate);

    std::vector<Body *> targetBodies1(1);
	Body *nullBody(NULL);
	targetBodies1[0] = nullBody;
	//messageBox->Show("1",NXMessageBox::DialogTypeQuestion,"3");
    try
    {
        extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies1);
    }
    catch(std::exception& ex)
    {
        messageBox->Show("错误",NXMessageBox::DialogTypeQuestion,ex.what());
    }



	char str[10];
	sprintf(str,"%d",height);


	extrudeBuilder1->Limits()->StartExtend()->Value()->SetRightHandSide("0");

	extrudeBuilder1->Limits()->EndExtend()->Value()->SetRightHandSide(str);

	extrudeBuilder1->Draft()->FrontDraftAngle()->SetRightHandSide("2");

	extrudeBuilder1->Draft()->BackDraftAngle()->SetRightHandSide("2");

	extrudeBuilder1->Offset()->StartOffset()->SetRightHandSide("0");

	extrudeBuilder1->Offset()->EndOffset()->SetRightHandSide("5");

	GeometricUtilities::SmartVolumeProfileBuilder *smartVolumeProfileBuilder1;
	smartVolumeProfileBuilder1 = extrudeBuilder1->SmartVolumeProfile();

	smartVolumeProfileBuilder1->SetOpenProfileSmartVolumeOption(false);

	smartVolumeProfileBuilder1->SetCloseProfileRule(GeometricUtilities::SmartVolumeProfileBuilder::CloseProfileRuleTypeFci);

	section1->SetDistanceTolerance(0.001);

	section1->SetChainingTolerance(0.00095);

	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);


	std::vector<Features::Feature *> features1(1);

	char* sketch = getJournalId(targetSketchName);
	//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,sketch);
	Features::SketchFeature *sketchFeature1(dynamic_cast<Features::SketchFeature *>(workPart->Features()->FindObject(sketch)));
	features1[0] = sketchFeature1;
	CurveFeatureRule *curveFeatureRule1;
	curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);

	section1->AllowSelfIntersection(true);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = curveFeatureRule1;


	//找到草图1
	try
	{
		char* str = getFeatureName(targetSketchName);
		Sketch *sketch1(dynamic_cast<Sketch *>(workPart->Sketches()->FindObject(str)));
		//拉伸圆用Curve ArcX 拉伸矩形用Curve LineX x代表矩形线编号
		std::vector<NXOpen::NXObject *>s = sketch1->GetAllGeometry();

		const char* temp;
		if (s.size() > 0)
		{
			temp = s[0]->Name().getText();
		}

		char lineName[50] = "Curve ";
		strcat(lineName,temp);

		//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,str);
		//NXOpen::UI::GetUI()->NXMessageBox()->Show("str",NXMessageBox::DialogTypeInformation,lineName);
		Line *line1(dynamic_cast<Line *>(sketch1->FindObject(lineName)));
		NXObject *nullNXObject(NULL);
		Point3d helpPoint1(0, 0, 0.0);
		section1->AddToSection(rules1, line1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);


		Direction *direction1;
		direction1 = workPart->Directions()->CreateDirection(sketch1, SenseForward, SmartObject::UpdateOptionWithinModeling);

		extrudeBuilder1->SetDirection(direction1);
	}
	catch (NXException &ex)
	{
		messageBox->Show("错误",NXMessageBox::DialogTypeQuestion,ex.GetMessage());
	}



	extrudeBuilder1->SetParentFeatureInternal(false);

	Features::Feature *feature1;
	feature1 = extrudeBuilder1->CommitFeature();
	feature1->SetName(setName);

	extrudeBuilder1->Destroy();
}

char* getJournalId(char name[])
{
	char res[100];
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	Part *thePart = theSession->Parts()->Work();

	NXOpen::Features::FeatureCollection::iterator i;

	for (i =thePart->Features()->begin(); i!=thePart->Features()->end(); i++)
	{
		//NXOpen::UI::GetUI()->NXMessageBox()->Show("hhahahhaha",NXMessageBox::DialogTypeInformation,(*i)->Name().GetText());
		if (strstr((*i)->Name().GetText(),name))
		{
			char extrudeName[100];
			strcpy(extrudeName,(*i)->JournalIdentifier().GetText());
			//NXOpen::UI::GetUI()->NXMessageBox()->Show("hhahahhaha",NXMessageBox::DialogTypeInformation,extrudeName);
			//Features::Extrude *extrude(dynamic_cast<Features::Extrude *>(workPart->Features()->FindObject(extrudeName)));
			//extrude1->SetName("zuyuanzhang");
			strcpy(res,(*i)->JournalIdentifier().GetText());
			//break;;
		}

	}
	return res;

}

char* getFeatureName(char name[])
{

	char res[100];
	char temp[50];
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	Part *thePart = theSession->Parts()->Work();

	NXOpen::Features::FeatureCollection::iterator i;

	for (i =thePart->Features()->begin(); i!=thePart->Features()->end(); i++)
	{
		//NXOpen::UI::GetUI()->NXMessageBox()->Show("hhahahhaha",NXMessageBox::DialogTypeInformation,(*i)->Name().GetText());
		if (strstr((*i)->Name().GetText(),name))
		{
			strcpy(temp,(*i)->GetFeatureName().getText());
			//break;;
		}

	}

	int length = strlen(temp);
	memset(res,0,sizeof(res));
	for (int i=0; i<length; i++)
	{
		if (temp[i] != ':')
		{
			res[i] = temp[i];
		}
		else
		{
			break;
		}
	}

	return res;

}


//建立开始草图
void createSketch()
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());

	UI *myUI = UI::GetUI();
	NXMessageBox *messageBox = myUI->NXMessageBox();


	// ----------------------------------------------
	//   Menu: Insert->Sketch...
	// ----------------------------------------------

	Sketch *nullSketch(NULL);
	SketchInPlaceBuilder *sketchInPlaceBuilder1;
	sketchInPlaceBuilder1 = workPart->Sketches()->CreateNewSketchInPlaceBuilder(nullSketch);

	Unit *unit1(dynamic_cast<Unit *>(workPart->UnitCollection()->FindObject("MilliMeter")));
	SketchAlongPathBuilder *sketchAlongPathBuilder1;
	sketchAlongPathBuilder1 = workPart->Sketches()->CreateSketchAlongPathBuilder(nullSketch);

	sketchAlongPathBuilder1->PlaneLocation()->Expression()->SetRightHandSide("0");


	theSession->Preferences()->Sketch()->SetCreateInferredConstraints(true);

	theSession->Preferences()->Sketch()->SetContinuousAutoDimensioning(true);

	theSession->Preferences()->Sketch()->SetDimensionLabel(Preferences::SketchPreferences::DimensionLabelTypeExpression);

	theSession->Preferences()->Sketch()->SetTextSizeFixed(true);

	theSession->Preferences()->Sketch()->SetFixedTextSize(3.0);

	theSession->Preferences()->Sketch()->SetConstraintSymbolSize(3.0);

	theSession->Preferences()->Sketch()->SetDisplayObjectColor(false);

	NXObject *nXObject1;
	nXObject1 = sketchInPlaceBuilder1->Commit();

	Sketch *sketch1(dynamic_cast<Sketch *>(nXObject1));
	Features::Feature *feature1;
	feature1 = sketch1->Feature();
	feature1->SetName("mainSketch");
	sketch1->Activate(Sketch::ViewReorientTrue);
	//drawCircle(0,0,0);

	sketchInPlaceBuilder1->Destroy();
	sketchAlongPathBuilder1->Destroy();
}

//在平面上建矩形，要求同一高度 ，即z相同
void createRect(double leftUpX,double leftUpY,double rightDownX,double rightDownY,double z)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());

	// ----------------------------------------------
	// Creating rectangle using By 2 Points method 
	// ----------------------------------------------

	Point3d startPoint1(leftUpX, leftUpY, z);
	Point3d endPoint1(rightDownX, leftUpY,z);
	Line *line1;
	line1 = workPart->Curves()->CreateLine(startPoint1, endPoint1);

	Point3d startPoint2(leftUpX, leftUpY, z);
	Point3d endPoint2(leftUpX, rightDownY, z);
	Line *line2;

	line2 = workPart->Curves()->CreateLine(startPoint2, endPoint2);

	Point3d startPoint3(rightDownX,rightDownY,z);
	Point3d endPoint3(leftUpX,rightDownY,z);
	Line *line3;
	line3 = workPart->Curves()->CreateLine(startPoint3, endPoint3);

	Point3d startPoint4(rightDownX,rightDownY,z);
	Point3d endPoint4(rightDownX,leftUpY,z);
	Line *line4;
	line4 = workPart->Curves()->CreateLine(startPoint4, endPoint4);

	theSession->ActiveSketch()->AddGeometry(line1, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line2, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line3, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line4, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->Update();

	theSession->Preferences()->Sketch()->SetAutoDimensionsToArcCenter(true);
}

//在平面上建矩形，要求同y 
void createRect(double leftUpX,double leftUpZ,double rightDownX,double rightDownZ,double y,int id)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());

	// ----------------------------------------------
	// Creating rectangle using By 2 Points method 
	// ----------------------------------------------

	Point3d startPoint1(leftUpX, y, leftUpZ);
	Point3d endPoint1(rightDownX,y, leftUpZ);
	Line *line1;
	line1 = workPart->Curves()->CreateLine(startPoint1, endPoint1);

	Point3d startPoint2(leftUpX, y, leftUpZ);
	Point3d endPoint2(leftUpX, y, rightDownZ);
	Line *line2;

	line2 = workPart->Curves()->CreateLine(startPoint2, endPoint2);

	Point3d startPoint3(rightDownX,y,rightDownZ);
	Point3d endPoint3(leftUpX,y,rightDownZ);
	Line *line3;
	line3 = workPart->Curves()->CreateLine(startPoint3, endPoint3);

	Point3d startPoint4(rightDownX,y,rightDownZ);
	Point3d endPoint4(rightDownX,y,leftUpZ);
	Line *line4;
	line4 = workPart->Curves()->CreateLine(startPoint4, endPoint4);

	theSession->ActiveSketch()->AddGeometry(line1, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line2, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line3, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->AddGeometry(line4, Sketch::InferConstraintsOptionInferNoConstraints);

	theSession->ActiveSketch()->Update();

	theSession->Preferences()->Sketch()->SetAutoDimensionsToArcCenter(true);
}

//在拉伸体上建立平面 x表示拉伸体序号

void createPlane(int x)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Datum/Point->Datum Plane...
	// ----------------------------------------------

	Features::Feature *nullFeatures_Feature(NULL);

	if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
	{
		throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
	}

	Features::DatumPlaneBuilder *datumPlaneBuilder1;
	datumPlaneBuilder1 = workPart->Features()->CreateDatumPlaneBuilder(nullFeatures_Feature);

	Plane *plane1;
	plane1 = datumPlaneBuilder1->GetPlane();

	plane1->SetUpdateOption(SmartObject::UpdateOptionWithinModeling);

	plane1->SetMethod(PlaneTypes::MethodTypeDistance);

	//只需要修改EXTRUDE(X)就可以 X代表数字
	char s[11] = "EXTRUDE(";
	s[8] = (x + '0');
	s[9] = ')';
	char temp[36] = "FACE 130 {(11.5,-11,8) EXTRUDE(";
	temp[31] = (x + '0');
	temp[32] = ')';
	temp[33] = '}';

	Features::Extrude *extrude1(dynamic_cast<Features::Extrude *>(workPart->Features()->FindObject(s)));
	Face *face1(dynamic_cast<Face *>(extrude1->FindObject(temp)));

	std::vector<NXObject *> geom2(1);
	geom2[0] = face1;
	plane1->SetGeometry(geom2);

	plane1->SetFlip(false);

	plane1->SetReverseSide(false);

	plane1->SetAlternate(PlaneTypes::AlternateTypeOne);

	plane1->RemoveOffsetData();

	plane1->Evaluate();

	datumPlaneBuilder1->SetResizeDuringUpdate(true);

	UI *plmHomeUI = UI::GetUI();

	NXMessageBox *messageBox = plmHomeUI->NXMessageBox();

	//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,"1");

	Features::Feature *feature1;
	feature1 = datumPlaneBuilder1->CommitFeature();
	//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,"222");

	datumPlaneBuilder1->Destroy();
}

//在一个拉伸体上建立草图
//120 130 140分别代表不同的面 要注意
void createSketchOnExtrude(char targetExtrude[],char *str1,char *str2,char setName[])
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Sketch...
	// ----------------------------------------------

	Sketch *nullSketch(NULL);
	SketchInPlaceBuilder *sketchInPlaceBuilder1;
	sketchInPlaceBuilder1 = workPart->Sketches()->CreateNewSketchInPlaceBuilder(nullSketch);

	SketchAlongPathBuilder *sketchAlongPathBuilder1;
	sketchAlongPathBuilder1 = workPart->Sketches()->CreateSketchAlongPathBuilder(nullSketch);

	sketchAlongPathBuilder1->PlaneLocation()->Expression()->SetRightHandSide("0");

	Scalar *scalar1;
	scalar1 = workPart->Scalars()->CreateScalar(1.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	// 	char str[20] = "EXTRUDE(";
	// 	str[8] = (extrudeNum + '0');
	// 	str[9] = ')';
	char* sketch = getJournalId(targetExtrude);

	Features::Extrude *extrude1(dynamic_cast<Features::Extrude *>(workPart->Features()->FindObject(sketch)));
	Edge *edge1(dynamic_cast<Edge *>(extrude1->FindObject(str1)));


	Face *face1(dynamic_cast<Face *>(extrude1->FindObject(str2)));
	Point3d point2(6.07069932873057, -4.5, 0.54146852704205);
	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(face1, workPart->ModelingViews()->WorkView(), point2);


	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(NULL);

	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(face1);

	sketchInPlaceBuilder1->Axis()->SetValue(edge1);

	theSession->Preferences()->Sketch()->SetCreateInferredConstraints(true);

	theSession->Preferences()->Sketch()->SetContinuousAutoDimensioning(true);

	theSession->Preferences()->Sketch()->SetDimensionLabel(Preferences::SketchPreferences::DimensionLabelTypeExpression);

	theSession->Preferences()->Sketch()->SetTextSizeFixed(true);

	theSession->Preferences()->Sketch()->SetFixedTextSize(3.0);

	theSession->Preferences()->Sketch()->SetConstraintSymbolSize(3.0);

	theSession->Preferences()->Sketch()->SetDisplayObjectColor(false);

	NXObject *nXObject1;
	nXObject1 = sketchInPlaceBuilder1->Commit();

	Sketch *sketch1(dynamic_cast<Sketch *>(nXObject1));
	//sketch1->SetName(setName);
	Features::Feature *feature1;
	feature1 = sketch1->Feature();
	feature1->SetName(setName);

	sketch1->Activate(Sketch::ViewReorientTrue);

	sketchInPlaceBuilder1->Destroy();

	sketchAlongPathBuilder1->Destroy();

	//drawCircle(-3.67140699961652, 0.31469202853856, 8.0);
	//theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
}


void fanxianglashen(char targetSketchName[],char targetExtrueName[],int length,char setName[])
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Design Feature->Extrude...
	// ----------------------------------------------

	Features::Feature *nullFeatures_Feature(NULL);

	if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
	{
		throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
	}

	Features::ExtrudeBuilder *extrudeBuilder1;
	extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(nullFeatures_Feature);

	Section *section1;
	section1 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);

	extrudeBuilder1->SetSection(section1);

	extrudeBuilder1->AllowSelfIntersectingSection(true);

	extrudeBuilder1->SetDistanceTolerance(0.001);

	extrudeBuilder1->Limits()->StartExtend()->Value()->SetRightHandSide("0");

	char changdu[3] = "";
	sprintf(changdu,"%d",length);
	extrudeBuilder1->Limits()->EndExtend()->Value()->SetRightHandSide(changdu);

	extrudeBuilder1->Draft()->FrontDraftAngle()->SetRightHandSide("2");

	extrudeBuilder1->Draft()->BackDraftAngle()->SetRightHandSide("2");

	extrudeBuilder1->Offset()->StartOffset()->SetRightHandSide("0");

	extrudeBuilder1->Offset()->EndOffset()->SetRightHandSide("5");

	section1->SetDistanceTolerance(0.001);

	section1->SetChainingTolerance(0.00095);

	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	std::vector<Features::Feature *> features1(1);
	char* sketch = getJournalId(targetSketchName);
	//NXOpen::UI::GetUI()->NXMessageBox()->Show("hhahahhaha",NXMessageBox::DialogTypeInformation,extrudeName);
	Features::SketchFeature *sketchFeature1(dynamic_cast<Features::SketchFeature *>(workPart->Features()->FindObject(sketch)));//"SKETCH(4)"
	features1[0] = sketchFeature1;
	CurveFeatureRule *curveFeatureRule1;
	curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);

	section1->AllowSelfIntersection(true);

	std::vector<SelectionIntentRule *> rules1(1);
	rules1[0] = curveFeatureRule1;
	char* str = getFeatureName(targetSketchName);
	Sketch *sketch1(dynamic_cast<Sketch *>(workPart->Sketches()->FindObject(str)));//"SKETCH_001"
	//拉伸圆用Curve ArcX 拉伸矩形用Curve LineX x代表矩形线编号
	std::vector<NXOpen::NXObject *>s = sketch1->GetAllGeometry();

	const char* temp;
	if (s.size() > 0)
	{
		temp = s[0]->Name().getText();
	}

	char lineName[50] = "Curve ";
	strcat(lineName,temp);
	Arc *arc1(dynamic_cast<Arc *>(sketch1->FindObject(lineName)));//"Curve Arc2"
	NXObject *nullNXObject(NULL);
	Point3d helpPoint1(-1.99886248178789, 2.66552710079727, 8.0);
	section1->AddToSection(rules1, arc1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);

	Direction *direction1;
	direction1 = workPart->Directions()->CreateDirection(sketch1, SenseForward, SmartObject::UpdateOptionWithinModeling);
	char* sketch2 = getJournalId(targetExtrueName);
	Body *body1(dynamic_cast<Body *>(workPart->Bodies()->FindObject(sketch2)));//"EXTRUDE(2)"

	bool success1;
	success1 = direction1->ReverseDirection();

	extrudeBuilder1->SetDirection(direction1);


	std::vector<Body *> targetBodies(1);
	targetBodies[0] = body1;
	extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies);

	extrudeBuilder1->BooleanOperation()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeSubtract);

	extrudeBuilder1->SetParentFeatureInternal(false);

	Features::Feature *feature1;
	try{

		feature1 = extrudeBuilder1->CommitFeature();
	}
	catch(NXException &ex)
	{

		NXOpen::UI::GetUI()->NXMessageBox()->Show("fanxiang",NXMessageBox::DialogTypeWarning,ex.GetMessage());
	}
	feature1->SetName(setName);

	extrudeBuilder1->Destroy();
}


void drawCircle(double x,double y,double z,double r)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: Insert->Sketch Curve->Circle...
	// ----------------------------------------------

	UI *myUi = UI::GetUI();
	NXMessageBox *message = myUi->NXMessageBox();

	NXMatrix *nXMatrix1;

	Point3d center1(x, y,z);
	Arc *arc1;
	try
	{

		nXMatrix1 = theSession->ActiveSketch()->Orientation();
		arc1 = workPart->Curves()->CreateArc(center1, nXMatrix1, r, 0.0, ( 360.0 * DEGRA ));
		theSession->ActiveSketch()->AddGeometry(arc1, Sketch::InferConstraintsOptionInferNoConstraints);
	}
	catch(NXException &ex)
	{
		message->Show("提示",NXMessageBox::DialogTypeQuestion,ex.GetMessage());
	}

	


	theSession->ActiveSketch()->Update();
}

//撤销
void unDo()
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());
	UI *myUI = UI::GetUI();
	NXMessageBox * message = myUI->NXMessageBox();
	message->Show("提示",NXMessageBox::DialogTypeQuestion,"撤销？");

	bool marksRecycled1;
	bool undoUnavailable1;
	theSession->UndoLastNVisibleMarks(1, &marksRecycled1, &undoUnavailable1);
}