/////////////////////////////////////////////////////////////////////////////////////////////////
// Please don't modified the following codes at any time.

var port = parseInt(process.argv[2]);
var debug = JSON.parse(process.argv[3]);
var home_dir = process.argv[4];
var root_dir = process.env['COMX_SDK'];
var runningLog = "Y:\\nxcocadapp\\data\\Running.log";

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

    data.parameters.ret = "Callback of TestConnection";

    websocket.send(data);

    websocket.Invoke('InvokeTestConnection', {'res' : 'Res Received from nxcocadapp'}, function(data){

    });
    
    if(deamon.IsConnect())
    {
        deamon.Invoke('InvokeTestConnection', {'res' : 'Res Received from nxcocadapp'}, function(data){

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
                console.log('1234567');
                if(sourceID == clientID)
                {
                    //appendFileSync(runningLog, "Received CreatePoint action from Server: sourceID: " + sourceID + " (ignored)parameters: " + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ);
                    data.parameters.ret = "Received and ignored";
                }
                else
                {
                    //appendFileSync(runningLog, "Received CreatePoint action from Server: sourceID: " + sourceID + " parameters: " + dcoordinateX + " " + dcoordinateY + " " + dcoordinateZ);
                    data.parameters.ret = "Received and accepted";
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
    appendFileSync(runningLog, "CreatePoint:" + dcoordX + " " + dcoordY + " " + dcoordZ + "#");
    if(deamon.IsConnect())
    {
        deamon.Invoke('OnActionFire', {'actionID' : 'CreatePoint', 'clientID' : clientID, 'parameters' : data.parameters}, function(data)
            {
                //appendFileSync(runningLog, data.parameters.ret);
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