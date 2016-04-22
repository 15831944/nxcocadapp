/////////////////////////////////////////////////////////////////////////////////////////////////
// Please don't modified the following codes at any time.

var port = parseInt(process.argv[2]);
var debug = JSON.parse(process.argv[3]);
var home_dir = process.argv[4];
var root_dir = process.env['COMX_SDK'];
var runningLog = "Y:\\nxcocadapp\\data\\Running.log";//log file
var messageQueue = "Y:\\nxcocadapp\\data\\MessageQueue.log";//message queue

process.chdir(home_dir + 'js/');

var websocket = require(root_dir + 'js/socket.io/websocket.common.js');
var clientID = websocket.UUID();

//websocket.start(port, debug);

//Code from dksclient
//console.log(websocket);
var deamon = websocket.InitDeamon();
//console.log(deamon);
var is_init = false;
function OnInit()
{
    //test--------------------------------------------
    //comx.ui.InformationBox('dksclient websocket.js OnInit'); 
    if(!is_init)
    {
        is_init = true;
        websocket.InvokeLocal('OnWebsocketInit', {}, function(data){
        });
    }
}
websocket.start(port, debug, OnInit);
//Code from dksclient

websocket.on("exit", function(data){
    process.exit();
});

process.on('uncaughtException', function (err) {
    console.error(err.stack);
    //console.log("Node NOT Exiting...");
    websocket.InvokeLocal('error', {"message" : err.message});
});

/////////////////////////////////////////////////////////////////////////////////////////////////
// Append your codes here please.
websocket.on('TestConnection', function(data){

    data.parameters.ret = "TestConnection: Server has recieved and returned.";

    websocket.send(data);

    websocket.Invoke('InvokeTestConnection', {'res' : 'InvokeTestConnection:Client has received from Server.'}, function(data){
    });
    
    if(deamon.IsConnect())
    {
        deamon.Invoke('InvokeTestConnection', {'res' : 'InvokeTestConnection:Client has received from Server.'}, function(data){
       });
    }

});

//ConnectToDeamonMgr
websocket.on('ConnectToDeamonMgr', function(data){
    deamon.Open(data.parameters.ip, 
        '0x86d51be5-0x4254-0x4848-0x88-0xf2-0xb5-0x8a-0x62-0x04-0xfb-0x79', 
        true, 
        function(flag){
            data.parameters = {'flag' : flag, 'ip_address' : deamon.GetCurrentAddress()};
            websocket.send(data);
            //CoCADCreatePoint
            deamon.on('CoCADCreatePoint', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var dcoordinateX = parameters.CoordinateX;
                var dcoordinateY = parameters.CoordinateY;
                var dcoordinateZ = parameters.CoordinateZ;
                //console.log('1234567');
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received CreatePoint action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreatePoint and ignored";
                    appendFileSync(messageQueue, "CreatePoint:" + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received CreatePoint action from Server: sourceID: " + sourceID + " parameters: " + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreatePoint and accepted";
                    appendFileSync(messageQueue, "CreatePoint:" + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ + "#");
                }
                deamon.send(data);
            });
            //CoCADCreateRect
            deamon.on('CoCADCreateRect', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var dpara1 = parameters.para1;
                var dpara2 = parameters.para2;
                var dpara3 = parameters.para3;
                var dpara4 = parameters.para4;
                var dpara5 = parameters.para5;
                var nOverloadType = parameters.overloadType;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received CreateRect action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dpara1 + " " + dpara2 + " " + dpara3 + " " + dpara4 + " " + dpara5 + " " + nOverloadType);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateRect and ignored";
                    appendFileSync(messageQueue, "CreateRect:" + dpara1 + " " + dpara2 + " " + dpara3 + " " + dpara4 + " " + dpara5 + " " + nOverloadType + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received CreateRect action from Server: sourceID: " + sourceID + " parameters: " + dpara1 + " " + dpara2 + " " + dpara3 + " " + dpara4 + " " + dpara5 + " " + nOverloadType);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateRect and accepted";
                    appendFileSync(messageQueue, "CreateRect:" + dpara1 + " " + dpara2 + " " + dpara3 + " " + dpara4 + " " + dpara5 + " " + nOverloadType + "#");
                }
                deamon.send(data);
            });
            //CoCADCreateSketch
            deamon.on('CoCADCreateSketch', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received CreateSketch action from Server: sourceID: " + sourceID + " (ignored)parameters: null");
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateSketch and ignored";
                    appendFileSync(messageQueue, "CreateSketch:#");
                }
                else
                {
                    appendFileSync(runningLog, "Received CreateSketch action from Server: sourceID: " + sourceID + " parameters: null");
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateSketch and accepted";
                    appendFileSync(messageQueue, "CreateSketch:#");
                }
                deamon.send(data);
            });
            //CoCADExtrude
            deamon.on('CoCADExtrude', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var dHeight = parameters.height;
                var nLineNum = parameters.lineNum;
                var nSketchNum = parameters.sketchNum;
                var nSketchID = parameters.sketchID;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received Extrude action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dHeight + " " + nLineNum + " " + nSketchNum + " " + nSketchID);
                    data.parameters.ret = "Client id: " + clientID + "has received action: Extrude and ignored";
                    appendFileSync(messageQueue, "Extrude:" + dHeight + " " + nLineNum + " " + nSketchNum + " " + nSketchID + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received Extrude action from Server: sourceID: " + sourceID + " parameters: " + dHeight + " " + nLineNum + " " + nSketchNum + " " + nSketchID);
                    data.parameters.ret = "Client id: " + clientID + "has received action: Extrude and accepted";
                    appendFileSync(messageQueue, "Extrude:" + dHeight + " " + nLineNum + " " + nSketchNum + " " + nSketchID + "#");
                }
                deamon.send(data);
            });
            //CoCADCreatePlane
            deamon.on('CoCADCreatePlane', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var dX = parameters.x;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received CreatePlane action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dX);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreatePlane and ignored";
                    appendFileSync(messageQueue, "CreatePlane:" + dX + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received CreatePlane action from Server: sourceID: " + sourceID + " parameters: " + dX);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreatePlane and accepted";
                    appendFileSync(messageQueue, "CreatePlane:" + dX + "#");
                }
                deamon.send(data);
            });
            //CoCADDrawCircle
            deamon.on('CoCADDrawCircle', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var dX = parameters.x;
                var dY = parameters.y;
                var dZ = parameters.z;
                var dR = parameters.r;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received DrawCircle action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dX + " " + dY + " " + dZ + " " + dR);
                    data.parameters.ret = "Client id: " + clientID + "has received action: DrawCircle and ignored";
                    appendFileSync(messageQueue, "DrawCircle:" + dX + " " + dY + " " + dZ + " " + dR + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received DrawCircle action from Server: sourceID: " + sourceID + " parameters: " + dX + " " + dY + " " + dZ + " " + dR);
                    data.parameters.ret = "Client id: " + clientID + "has received action: DrawCircle and accepted";
                    appendFileSync(messageQueue, "DrawCircle:" + dX + " " + dY + " " + dZ + " " + dR + "#");
                }
                deamon.send(data);
            });
            //CoCADCreateSketchOnExtrude
            deamon.on('CoCADCreateSketchOnExtrude', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var nExtrudeNum = parameters.extrudeNum;
                var str1 = parameters.str1;
                var str2 = parameters.str2;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received CreateSketchOnExtrude action from Server: sourceID: " + sourceID + " (ignored)parameters: " + nExtrudeNum + " " + str1 + " " + str2);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateSketchOnExtrude and ignored";
                    appendFileSync(messageQueue, "CreateSketchOnExtrude:" + nExtrudeNum + " " + str1 + " " + str2 + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received CreateSketchOnExtrude action from Server: sourceID: " + sourceID + " parameters: " + nExtrudeNum + " " + str1 + " " + str2);
                    data.parameters.ret = "Client id: " + clientID + "has received action: CreateSketchOnExtrude and accepted";
                    appendFileSync(messageQueue, "CreateSketchOnExtrude:" + nExtrudeNum + " " + str1 + " " + str2 + "#");
                }
                deamon.send(data);
            });
            //CoCADReverseExtrude
            deamon.on('CoCADReverseExtrude', function(data){
                var sourceID = data.parameters.sourceID;
                var parameters = data.parameters.parameters;
                var strSketchID = parameters.sketchID;
                var strSketchNum = parameters.sketchNum;
                var strExtrudeLine = parameters.extrudeLine;
                var strTargetExtrude = parameters.targetExtrude;
                var dLength = parameters.length;
                if(sourceID == clientID)//Same source doesn't need to accept.
                {
                    appendFileSync(runningLog, "Received ReverseExtrude action from Server: sourceID: " + sourceID + " (ignored)parameters: " + strSketchID + " " + strSketchNum + " " + strExtrudeLine + " " + strTargetExtrude + " " + dLength);
                    data.parameters.ret = "Client id: " + clientID + "has received action: ReverseExtrude and ignored";
                    appendFileSync(messageQueue, "ReverseExtrude:" + strSketchID + " " + strSketchNum + " " + strExtrudeLine + " " + strTargetExtrude + " " + dLength + "#");
                }
                else
                {
                    appendFileSync(runningLog, "Received ReverseExtrude action from Server: sourceID: " + sourceID + " parameters: " + strSketchID + " " + strSketchNum + " " + strExtrudeLine + " " + strTargetExtrude + " " + dLength);
                    data.parameters.ret = "Client id: " + clientID + "has received action: ReverseExtrude and accepted";
                    appendFileSync(messageQueue, "ReverseExtrude:" + strSketchID + " " + strSketchNum + " " + strExtrudeLine + " " + strTargetExtrude + " " + dLength + "#");
                }
                deamon.send(data);
            });
        }
    ); 
});

//SearchDeamonMgr
function GetMinIP(ip_list)
{
    var ret = ip_list[0];
    for(var loop = 0; loop < ip_list.length; ++loop)
    {
        if(ip_list[loop] < ret)
        {
            ret = ip_list[loop];
        }
    }
    
    return ret;
}

websocket.on('SearchDeamonMgr', function(data){
    websocket.SearchDeamonManager(function(ip_list){
        if(ip_list)
        {
            data.parameters = {'ip' : GetMinIP(ip_list)};
        }
        else
        {
            data.parameters = {'ip' : false};
        }
        websocket.send(data);
    });
});

//CreatePoint
websocket.on('CreatePoint', function(data){
    var dcoordX = data.parameters.CoordinateX;
    var dcoordY = data.parameters.CoordinateY;
    var dcoordZ = data.parameters.CoordinateZ;
    appendFileSync(runningLog, "Action detected: CreatePoint:" + dcoordX + " " + dcoordY + " " + dcoordZ);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreatePoint', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//CreateRect
websocket.on('CreateRect', function(data){
    var dpara1 = data.parameters.para1;
    var dpara2 = data.parameters.para2;
    var dpara3 = data.parameters.para3;
    var dpara4 = data.parameters.para4;
    var dpara5 = data.parameters.para5;
    var nOverloadType = data.parameters.overloadType;
    appendFileSync(runningLog, "Action detected: CreateRect:" + dpara1 + " " + dpara2 + " " + dpara3 + " " + dpara4 + " " + dpara5 + " " + nOverloadType);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreateRect', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//CreateSketch
websocket.on('CreateSketch', function(data){
    data.parameters = null;
    appendFileSync(runningLog, "Action detected: CreateSketch: No parameters");
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreateSketch', 'clientID' : clientID, 'parameters' : null}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//Extrude
websocket.on('Extrude', function(data){
    var dheight = data.parameters.height;
    var nlineNum = data.parameters.lineNum;
    var nsketchNum = data.parameters.sketchNum;
    var nsketchID = data.parameters.sketchID;
    appendFileSync(runningLog, "Action detected: Extrude:" + dheight + " " + nlineNum + " " + nsketchNum + " " + nsketchID);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'Extrude', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//CreatePlane
websocket.on('CreatePlane', function(data){
    var nX = data.parameters.x;
    appendFileSync(runningLog, "Action detected: CreatePlane:" + nX);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreatePlane', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//DrawCircle
websocket.on('DrawCircle', function(data){
    var dX = data.parameters.x;
    var dY = data.parameters.y;
    var dZ = data.parameters.z;
    var dR = data.parameters.r;
    appendFileSync(runningLog, "Action detected: DrawCircle:" + dX + " " + dY + " " + dZ + " " + dR);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'DrawCircle', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//CreateSketchOnExtrude
websocket.on('CreateSketchOnExtrude', function(data){
    var nExtrudeNum = data.parameters.extrudeNum;
    var str1 = data.parameters.str1;
    var str2 = data.parameters.str2;
    appendFileSync(runningLog, "Action detected: CreateSketchOnExtrude:" + nExtrudeNum + " " + str1 + " " + str2);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreateSketchOnExtrude', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//ReverseExtrude
websocket.on('ReverseExtrude', function(data){
    var strSketchID = data.parameters.sketchID;
    var strSketchNum = data.parameters.sketchNum;
    var strExtrudeLine = data.parameters.extrudeLine;
    var strTargetExtrude = data.parameters.targetExtrude;
    var nLength = data.parameters.length;
    appendFileSync(runningLog, "Action detected: ReverseExtrude:" + strSketchID + " " + strSketchNum + " " + strExtrudeLine + " " + strTargetExtrude + " " + nLength);
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'ReverseExtrude', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                appendFileSync(runningLog, data.parameters.ret);
            });
    }
});

//Util
function sleep(n)
{
    var start=new Date().getTime();
    while(true) if(new Date().getTime()-start>n) break;
}

function appendFileSync(fileName, data)
{
    var logString = require('fs').readFileSync(fileName);
    require('fs').writeFileSync(fileName, logString + data + "\n");
}