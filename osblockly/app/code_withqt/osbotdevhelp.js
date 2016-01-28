/*!
// (C) 2015 CHIV
//
// DESC : receive the signal of QT and invoke the Q_INVOKABLE function to complete
//        missions.
//
*/
//-----------------------------------------------------------------------------------------------------
//                                        SLOTS
//-----------------------------------------------------------------------------------------------------
function osbotdevhelp_open() {
  if ('OSBotDevHelp' in window) {
    var xml = Blockly.Xml.workspaceToDom(Code.workspace);
    var text = Blockly.Xml.domToText(xml);
    OSBotDevHelp.ON_OSBot_Open(text);
  }
}

function osbotdevhelp_load(text) {
  // clear firstly
  Code.workspace.clear();
  // load new blocks
  var xml = Blockly.Xml.textToDom(text);
  Blockly.Xml.domToWorkspace(Code.workspace, xml);
}

function osbotdevhelp_newf() {
  if ('OSBotDevHelp' in window) {
    var xml = Blockly.Xml.workspaceToDom(Code.workspace);
    var text = Blockly.Xml.domToText(xml);
    var ok = OSBotDevHelp.ON_OSBot_Newf(text);
    if (ok) {
      // ok, clear the workspace
      Code.workspace.clear();
    }
  }
  // the QT can't save that project, we do nothing
}

function osbotdevhelp_save() {
  if ('OSBotDevHelp' in window) {
    var xml = Blockly.Xml.workspaceToDom(Code.workspace);
    var text = Blockly.Xml.domToText(xml);
    OSBotDevHelp.ON_OSBot_Save(text);
  }
  // whether true or false, we do nothing.
}
//
/*!
  connect the signals from QT to slots defined by JavaScript
*/
function osbotdevhelp_connectSlots() {
  OSBotDevHelp.osbotdev_load.connect(this, osbotdevhelp_load);
}

/*!
  when you changed the language, the osbotdev will reset, so you must
  reload the project by reading the xml stored in QT-space.
*/
function osbotdevhelp_reloadProject() {
  if ('OSBotDevHelp' in window) {
    var xml = OSBotDevHelp.GetCachedXml();
    if (xml) {
      osbotdevhelp_load(xml);
    }
  }
}
/*!
  tell QT that we have connected the device.
*/
function osbotdevhelp_notifyDeviceConnected() {
  if ('OSBotDevHelp' in window) {
    OSBotDevHelp.ON_OSBot_DeviceConnected();
  }
}

function osbotdevhelp_notifyDeviceDisconnected() {
  if ('OSBotDevHelp' in window) {
    OSBotDevHelp.ON_OSBot_DeviceDisconnected();
  }
}

function osbotdevhelp_notifySerialDataReceived(msgcnt, str) {
  if ('OSBotDevHelp' in window) {
    OSBotDevHelp.ON_OSBot_SerialDataReceived(msgcnt, str);
  }
}
// save the xml to heap of QT
function osbotdevhelp_cacheProject()
{
  if ('OSBotDevHelp' in window) {
    var xml = Blockly.Xml.workspaceToDom(Code.workspace);
    var text = Blockly.Xml.domToText(xml);
    OSBotDevHelp.SetCachedXml(text);
  }
}

/*!
  connect the Device with serial
*/
var msgcnt = 0;

function osbotdevhelp_connectDevice(serialNo) {

  alert('devid = ' + serialNo);
	
  OSA.Init(null, serialNo, null);
  OSA.SetReconnect(true);

  OSA.on('dev_connect', function(m) {
	alert('connected');
    osbotdevhelp_notifyDeviceConnected();
  }).on('dev_disconnect', function(m) {
    osbotdevhelp_notifyDeviceDisconnected();
  }).on('serial', function(str) {
    osbotdevhelp_notifySerialDataReceived(msgcnt++, str);
  }).on('msg', function(p) {
    // TODO: what's this ?
  });
  OSA.Connect();
}

// tell the QT it should changeLanguage
function osbotdevhelp_changeLanguage(language) {
  if ('OSBotDevHelp' in window) {
    OSBotDevHelp.ON_OSBot_ChangeLanguage(language);
  }
}

function osbotdevhelp_init() {
  if ('OSBotDevHelp' in window) {
    osbotdevhelp_connectSlots();
  }
  else {
    alert('You must run this from OSBotShell!');
  }
}
