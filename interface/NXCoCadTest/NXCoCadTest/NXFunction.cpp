#include "stdafx.h"
#include <strstream>
using namespace NXOpen;
using std::ostrstream;
using std::endl;    
using std::ends;
using std::cerr;

// void lashen(int height,int lineNum,int sketchNum,int sketchId)
// {
// 	Session *theSession = Session::GetSession();
// 	Part *workPart(theSession->Parts()->Work());
// 	Part *displayPart(theSession->Parts()->Display());
// 	// ----------------------------------------------
// 	//   Menu: Insert->Design Feature->Extrude...
// 	// ----------------------------------------------
// 	// Session::UndoMarkId markId1;
// 	//markId1 = theSession->SetUndoMark(Session::MarkVisibilityVisible, "Start");
// 
// 	Features::Feature *nullFeatures_Feature(NULL);
// 
// 	if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
// 	{
// 		throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
// 	}
// 
// 	Features::ExtrudeBuilder *extrudeBuilder1;
// 	extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(nullFeatures_Feature);
// 
// 	Section *section1;
// 
// 	UI *plmHomeUI = UI::GetUI();
// 	NXMessageBox *messageBox = plmHomeUI->NXMessageBox();
// 
// 	section1 = workPart->Sections()->CreateSection(0,0,0);
// 
// 	extrudeBuilder1->SetSection(section1);
// 
// 	extrudeBuilder1->AllowSelfIntersectingSection(true);
// 
// 	Unit *unit1;
// 	unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();
// 
// 
// 	extrudeBuilder1->SetDistanceTolerance(0.001);
// 
// 	extrudeBuilder1->BooleanOperation()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeCreate);
// 
// 	std::vector<Body *> targetBodies1(1);
// 	Body *nullBody(NULL);
// 	targetBodies1[0] = nullBody;
// 	//messageBox->Show("1",NXMessageBox::DialogTypeQuestion,"3");
// 	extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies1);
// 
// 
// 	char str[10];
// 	sprintf(str,"%d",height);
// 
// 
// 	extrudeBuilder1->Limits()->StartExtend()->Value()->SetRightHandSide("0");
// 
// 	extrudeBuilder1->Limits()->EndExtend()->Value()->SetRightHandSide(str);
// 
// 	extrudeBuilder1->Draft()->FrontDraftAngle()->SetRightHandSide("2");
// 
// 	extrudeBuilder1->Draft()->BackDraftAngle()->SetRightHandSide("2");
// 
// 	extrudeBuilder1->Offset()->StartOffset()->SetRightHandSide("0");
// 
// 	extrudeBuilder1->Offset()->EndOffset()->SetRightHandSide("5");
// 
// 	GeometricUtilities::SmartVolumeProfileBuilder *smartVolumeProfileBuilder1;
// 	smartVolumeProfileBuilder1 = extrudeBuilder1->SmartVolumeProfile();
// 
// 	smartVolumeProfileBuilder1->SetOpenProfileSmartVolumeOption(false);
// 
// 	smartVolumeProfileBuilder1->SetCloseProfileRule(GeometricUtilities::SmartVolumeProfileBuilder::CloseProfileRuleTypeFci);
// 
// 	section1->SetDistanceTolerance(0.001);
// 
// 	section1->SetChainingTolerance(0.00095);
// 
// 	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);
// 
// 
// 	std::vector<Features::Feature *> features1(1);
// 
// 	char sketch[20] = "SKETCH(";
// 	sketch[7] = (sketchId + '0');
// 	sketch[8] = ')';
// 	//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,sketch);
// 	Features::SketchFeature *sketchFeature1(dynamic_cast<Features::SketchFeature *>(workPart->Features()->FindObject(sketch)));
// 	features1[0] = sketchFeature1;
// 	CurveFeatureRule *curveFeatureRule1;
// 	curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);
// 
// 	section1->AllowSelfIntersection(true);
// 
// 	std::vector<SelectionIntentRule *> rules1(1);
// 	rules1[0] = curveFeatureRule1;
// 	//找到草图1
// 	try
// 	{
// 		char str[20] = "SKETCH_00";
// 		str[9] = (sketchNum + '0');
// 		Sketch *sketch1(dynamic_cast<Sketch *>(workPart->Sketches()->FindObject(str)));
// 		//拉伸圆用Curve ArcX 拉伸矩形用Curve LineX x代表矩形线编号
// 		sprintf(str,"%s", "Curve Line");//= "Curve Line";
// 		char temp[3];
// 		sprintf(temp,"%d",lineNum);
// 		strcat(str,temp);
// 
// 		//messageBox->Show("提示",NXMessageBox::DialogTypeQuestion,str);
// 		Line *line1(dynamic_cast<Line *>(sketch1->FindObject(str)));
// 		NXObject *nullNXObject(NULL);
// 		Point3d helpPoint1(0, 0, 0.0);
// 		section1->AddToSection(rules1, line1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);
// 
// 
// 		Direction *direction1;
// 		direction1 = workPart->Directions()->CreateDirection(sketch1, SenseForward, SmartObject::UpdateOptionWithinModeling);
// 
// 		extrudeBuilder1->SetDirection(direction1);
// 	}
// 	catch (NXException &ex)
// 	{
// 		messageBox->Show("错误",NXMessageBox::DialogTypeQuestion,ex.GetMessage());
// 	}
// 
// 
// 
// 	extrudeBuilder1->SetParentFeatureInternal(false);
// 
// 	Features::Feature *feature1;
// 	feature1 = extrudeBuilder1->CommitFeature();
// 
// 	extrudeBuilder1->Destroy();
// }

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
	sketch1->Activate(Sketch::ViewReorientTrue);
	feature1->SetName("mainSketch");
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

//在平面上建矩形，要求同y id为重载标志 无意义
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
//在平面上建矩形，要求同y id为重载标志 无意义
void createRect(double leftUpY,double leftUpZ,double rightDownY,double rightDownZ,double x,int id,int id2)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Part *displayPart(theSession->Parts()->Display());

	// ----------------------------------------------
	// Creating rectangle using By 2 Points method 
	// ----------------------------------------------

	Point3d startPoint1(x, leftUpY, leftUpZ);
	Point3d endPoint1(x,rightDownY,leftUpZ);
	Line *line1;
	line1 = workPart->Curves()->CreateLine(startPoint1, endPoint1);

	Point3d startPoint2(x, leftUpY, leftUpZ);
	Point3d endPoint2(x,leftUpY, rightDownZ);
	Line *line2;

	line2 = workPart->Curves()->CreateLine(startPoint2, endPoint2);

	Point3d startPoint3(x,rightDownY,rightDownZ);
	Point3d endPoint3(x,rightDownY,leftUpZ);
	Line *line3;
	line3 = workPart->Curves()->CreateLine(startPoint3, endPoint3);

	Point3d startPoint4(x,rightDownY,rightDownZ);
	Point3d endPoint4(x,leftUpY,rightDownZ);
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
// void createSketchOnExtrude(int extrudeNum,const char *str1,const char *str2)
// {
// 	Session *theSession = Session::GetSession();
// 	Part *workPart(theSession->Parts()->Work());
// 	Part *displayPart(theSession->Parts()->Display());
// 	// ----------------------------------------------
// 	//   Menu: Insert->Sketch...
// 	// ----------------------------------------------
// 
// 	Sketch *nullSketch(NULL);
// 	SketchInPlaceBuilder *sketchInPlaceBuilder1;
// 	sketchInPlaceBuilder1 = workPart->Sketches()->CreateNewSketchInPlaceBuilder(nullSketch);
// 
// 	SketchAlongPathBuilder *sketchAlongPathBuilder1;
// 	sketchAlongPathBuilder1 = workPart->Sketches()->CreateSketchAlongPathBuilder(nullSketch);
// 
// 	sketchAlongPathBuilder1->PlaneLocation()->Expression()->SetRightHandSide("0");
// 
// 	Scalar *scalar1;
// 	scalar1 = workPart->Scalars()->CreateScalar(1.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
// 
// 	char str[20] = "EXTRUDE(";
// 	str[8] = (extrudeNum + '0');
// 	str[9] = ')';
// 
// 	Features::Extrude *extrude1(dynamic_cast<Features::Extrude *>(workPart->Features()->FindObject(str)));
// 	Edge *edge1(dynamic_cast<Edge *>(extrude1->FindObject(str1)));
// 
// 
// 	Face *face1(dynamic_cast<Face *>(extrude1->FindObject(str2)));
// 	Point3d point2(6.07069932873057, -4.5, 0.54146852704205);
// 	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(face1, workPart->ModelingViews()->WorkView(), point2);
// 
// 
// 	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(NULL);
// 
// 	sketchInPlaceBuilder1->PlaneOrFace()->SetValue(face1);
// 
// 	sketchInPlaceBuilder1->Axis()->SetValue(edge1);
// 
// 	theSession->Preferences()->Sketch()->SetCreateInferredConstraints(true);
// 
// 	theSession->Preferences()->Sketch()->SetContinuousAutoDimensioning(true);
// 
// 	theSession->Preferences()->Sketch()->SetDimensionLabel(Preferences::SketchPreferences::DimensionLabelTypeExpression);
// 
// 	theSession->Preferences()->Sketch()->SetTextSizeFixed(true);
// 
// 	theSession->Preferences()->Sketch()->SetFixedTextSize(3.0);
// 
// 	theSession->Preferences()->Sketch()->SetConstraintSymbolSize(3.0);
// 
// 	theSession->Preferences()->Sketch()->SetDisplayObjectColor(false);
// 
// 	NXObject *nXObject1;
// 	nXObject1 = sketchInPlaceBuilder1->Commit();
// 
// 	Sketch *sketch1(dynamic_cast<Sketch *>(nXObject1));
// 	Features::Feature *feature1;
// 	feature1 = sketch1->Feature();
// 
// 	sketch1->Activate(Sketch::ViewReorientTrue);
// 
// 	//sketchInPlaceBuilder1->Destroy();
// 
// 	//sketchAlongPathBuilder1->Destroy();
// 
// 	//drawCircle(-3.67140699961652, 0.31469202853856, 8.0);
// 	//theSession->ActiveSketch()->Deactivate(Sketch::ViewReorientFalse, Sketch::UpdateLevelModel);
// }


// void fanxianglashen(const char *sketchId,const char *sketchNum,const char *lashenLine,const char *targetExtrue,int length)
// {
// 	Session *theSession = Session::GetSession();
// 	Part *workPart(theSession->Parts()->Work());
// 	Part *displayPart(theSession->Parts()->Display());
// 	// ----------------------------------------------
// 	//   Menu: Insert->Design Feature->Extrude...
// 	// ----------------------------------------------
// 	Features::Feature *nullFeatures_Feature(NULL);
// 
// 
// 	if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
// 	{
// 		throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
// 	}
// 
// 	Features::ExtrudeBuilder *extrudeBuilder1;
// 	extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(nullFeatures_Feature);
// 
// 	Section *section1;
// 	section1 = workPart->Sections()->CreateSection(0.00095, 0.001, 0.05);
// 
// 	extrudeBuilder1->SetSection(section1);
// 
// 	extrudeBuilder1->AllowSelfIntersectingSection(true);
// 
// 	extrudeBuilder1->SetDistanceTolerance(0.001);
// 
// 	extrudeBuilder1->Limits()->StartExtend()->Value()->SetRightHandSide("0");
// 
// 	char changdu[3] = "";
// 	sprintf(changdu,"%d",length);
// 	extrudeBuilder1->Limits()->EndExtend()->Value()->SetRightHandSide(changdu);
// 
// 	extrudeBuilder1->Draft()->FrontDraftAngle()->SetRightHandSide("2");
// 
// 	extrudeBuilder1->Draft()->BackDraftAngle()->SetRightHandSide("2");
// 
// 	extrudeBuilder1->Offset()->StartOffset()->SetRightHandSide("0");
// 
// 	extrudeBuilder1->Offset()->EndOffset()->SetRightHandSide("5");
// 
// 	section1->SetDistanceTolerance(0.001);
// 
// 	section1->SetChainingTolerance(0.00095);
// 
// 	section1->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);
// 
// 	std::vector<Features::Feature *> features1(1);
// 	Features::SketchFeature *sketchFeature1(dynamic_cast<Features::SketchFeature *>(workPart->Features()->FindObject(sketchId)));//"SKETCH(4)"
// 	features1[0] = sketchFeature1;
// 	CurveFeatureRule *curveFeatureRule1;
// 	curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);
// 
// 	section1->AllowSelfIntersection(true);
// 
// 	std::vector<SelectionIntentRule *> rules1(1);
// 	rules1[0] = curveFeatureRule1;
// 	Sketch *sketch1(dynamic_cast<Sketch *>(workPart->Sketches()->FindObject(sketchNum)));//"SKETCH_001"
// 	Arc *arc1(dynamic_cast<Arc *>(sketch1->FindObject(lashenLine)));//"Curve Arc2"
// 	NXObject *nullNXObject(NULL);
// 	Point3d helpPoint1(-1.99886248178789, 2.66552710079727, 8.0);
// 	section1->AddToSection(rules1, arc1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);
// 
// 	Direction *direction1;
// 	direction1 = workPart->Directions()->CreateDirection(sketch1, SenseForward, SmartObject::UpdateOptionWithinModeling);
// 
// 	Body *body1(dynamic_cast<Body *>(workPart->Bodies()->FindObject(targetExtrue)));//"EXTRUDE(2)"
// 
// 	bool success1;
// 	success1 = direction1->ReverseDirection();
// 
// 	extrudeBuilder1->SetDirection(direction1);
// 
// 
// 	std::vector<Body *> targetBodies(1);
// 	targetBodies[0] = body1;
// 	extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies);
// 
// 	extrudeBuilder1->BooleanOperation()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeSubtract);
// 
// 	extrudeBuilder1->SetParentFeatureInternal(false);
// 
// 	Features::Feature *feature1;
// 	feature1 = extrudeBuilder1->CommitFeature();
// 
// 	extrudeBuilder1->Destroy();
// }

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
    //need to add NXOpen::
    NXOpen::Arc *arc1;
	try
	{

		nXMatrix1 = theSession->ActiveSketch()->Orientation();
		arc1 = workPart->Curves()->CreateArc(center1, nXMatrix1, r, 0.0, ( 360.0 * DEGRA ));
		theSession->ActiveSketch()->AddGeometry(arc1, Sketch::InferConstraintsOptionInferNoConstraints);
	}
	catch(NXException &ex)
	{
        //change ex.GetMessage to ex.what
        message->Show("提示",NXMessageBox::DialogTypeQuestion,ex.what());
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
	extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies1);


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
        //change ex.GetMessage to ex.what
		messageBox->Show("错误",NXMessageBox::DialogTypeQuestion,ex.what());
	}



	extrudeBuilder1->SetParentFeatureInternal(false);

	Features::Feature *feature1;
	feature1 = extrudeBuilder1->CommitFeature();
	feature1->SetName(setName);

	extrudeBuilder1->Destroy();
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
    //need to add NXOpen::
    NXOpen::Arc *arc1(dynamic_cast<NXOpen::Arc *>(sketch1->FindObject(lineName)));//"Curve Arc2"
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
        //change ex.GetMessage to ex.what
		NXOpen::UI::GetUI()->NXMessageBox()->Show("fanxiang",NXMessageBox::DialogTypeWarning,ex.what());
	}
	feature1->SetName(setName);

	extrudeBuilder1->Destroy();
}
