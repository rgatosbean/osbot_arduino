//
// (C) 2015 OSbot
//
'use strict'

goog.provide('Blockly.Blocks.osbot');

goog.require('Blockly.Blocks');

Blockly.Blocks['osbot_bzsensor'] = {
  init: function() {
    var rj25s = [
      [Blockly.Msg.OSBOT_RJ25_NAME + ':0', '0'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':1', '1'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':2', '2'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':3', '3'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':4', '4'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':5', '5']
    ];
    var bzsensors = [[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']];
    
    this.appendDummyInput()
        .appendField(Blockly.Msg.OSBOT_BZ_TITLE)
        .appendField(new Blockly.FieldDropdown(bzsensors), "BZSENSOR");
    this.appendDummyInput()
        .appendField(Blockly.Msg.OSBOT_RJ25_NAME)
        .appendField(new Blockly.FieldDropdown(rj25s), "RJ25");
    this.appendDummyInput()
        .appendField(new Blockly.FieldImage("http://cpro.baidu.com/cpro/ui/uijs.php?adclass=0&app_id=0&c=news&cf=19&ch=0&di=8&fv=0&is_app=0&jk=80e4d5c7bb2fbe81&k=c%D3%EF%D1%D4%C5%E0%D1%B5&k0=c%D3%EF%D1%D4%C5%E0%D1%B5&k1=%D3%CE%CF%B7%B1%E0%B3%CC%D1%A7%CF%B0&k2=web%C7%B0%B6%CB%D1%A7%CF%B0&k3=%CA%D6%BB%FAapp%BF%AA%B7%A2&k4=%C3%C0%B0%D7%B5%C4%B7%BD%B7%A8&k5=%CA%FD%BE%DD%BF%E2%D1%A7%CF%B0%C8%EB%C3%C5&kdi0=8&kdi1=8&kdi2=8&kdi3=8&kdi4=8&kdi5=8&luki=1&mcpm=714342&n=10&p=baidu&q=jb51_cpr&rb=1&rs=1&seller_id=1&sid=81be2fbbc7d5e480&ssp2=8&stid=50&t=tpclicked3_hc&td=336546&tu=u336546&u=http%3A%2F%2Fwww%2Ejb51%2Enet%2Farticle%2F27119%2Ehtm&urlid=0", 15, 15, "*"));
    this.setOutput(true, "Number");
    this.setColour(300);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_xjsensor'] = {
  init: function() {
    var rj25s = [
      [Blockly.Msg.OSBOT_RJ25_NAME + ':0', '0'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':1', '1'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':2', '2'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':3', '3'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':4', '4'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':5', '5']
    ];
    var xjsensors = [[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']];
    
    this.appendDummyInput()
        .appendField(Blockly.Msg.OSBOT_XJ_TITLE)
        .appendField(new Blockly.FieldDropdown(xjsensors), "XJSENSOR");
    this.appendDummyInput()
        .appendField(Blockly.Msg.OSBOT_RJ25_NAME)
        .appendField(new Blockly.FieldDropdown(rj25s), "RJ25");
    this.appendDummyInput()
        .appendField(new Blockly.FieldImage("http://cpro.baidu.com/cpro/ui/uijs.php?adclass=0&app_id=0&c=news&cf=19&ch=0&di=8&fv=0&is_app=0&jk=80e4d5c7bb2fbe81&k=c%D3%EF%D1%D4%C5%E0%D1%B5&k0=c%D3%EF%D1%D4%C5%E0%D1%B5&k1=%D3%CE%CF%B7%B1%E0%B3%CC%D1%A7%CF%B0&k2=web%C7%B0%B6%CB%D1%A7%CF%B0&k3=%CA%D6%BB%FAapp%BF%AA%B7%A2&k4=%C3%C0%B0%D7%B5%C4%B7%BD%B7%A8&k5=%CA%FD%BE%DD%BF%E2%D1%A7%CF%B0%C8%EB%C3%C5&kdi0=8&kdi1=8&kdi2=8&kdi3=8&kdi4=8&kdi5=8&luki=1&mcpm=714342&n=10&p=baidu&q=jb51_cpr&rb=1&rs=1&seller_id=1&sid=81be2fbbc7d5e480&ssp2=8&stid=50&t=tpclicked3_hc&td=336546&tu=u336546&u=http%3A%2F%2Fwww%2Ejb51%2Enet%2Farticle%2F27119%2Ehtm&urlid=0", 15, 15, "*"));
    this.setOutput(true, "Number");
    this.setColour(255);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_face'] = {
  init: function() {
    var rj25s = [
      [Blockly.Msg.OSBOT_RJ25_NAME + ':0', '0'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':1', '1'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':2', '2'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':3', '3'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':4', '4'],
      [Blockly.Msg.OSBOT_RJ25_NAME + ':5', '5']
    ];
    var eyeicons = [
        [Blockly.Msg.OSBOT_ICON_NAME + '0', '0'],
        [Blockly.Msg.OSBOT_ICON_NAME + '1', '1'],
        [Blockly.Msg.OSBOT_ICON_NAME + '2', '2'],
        [Blockly.Msg.OSBOT_ICON_NAME + '3', '3'],
        [Blockly.Msg.OSBOT_ICON_NAME + '4', '4'],
        [Blockly.Msg.OSBOT_ICON_NAME + '5', '5'],
        [Blockly.Msg.OSBOT_ICON_NAME + '6', '6'],
        [Blockly.Msg.OSBOT_ICON_NAME + '7', '7']
    ];
      
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.Msg.OSBOT_FACE_TITLE)
        .appendField(new Blockly.FieldDropdown(rj25s), "RJ25");
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.Msg.OSBOT_EYE_NAME)
        .appendField(new Blockly.FieldDropdown(eyeicons), "EYE")
        .appendField(new Blockly.FieldImage("https://www.gstatic.com/codesite/ph/images/star_on.gif", 15, 15, "*"));
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_textout'] = {
  init: function() {
    this.appendValueInput("CONTENT")
        .setCheck("String")
        .appendField(Blockly.Msg.OSBOT_TEXTOUT_TITLE)
        .appendField(Blockly.Msg.OSBOT_TEXTOUT_CONTENT_NAME);
    this.appendValueInput("X")
        .appendField("X");
    this.appendValueInput("Y")
        .appendField("Y");
    this.appendDummyInput()
        .appendField(new Blockly.FieldColour("#ff0000"), "COLOR");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(210);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_motor'] = {
  init: function() {
    var motors = [[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']];
    var directions = [[Blockly.Msg.OSBOT_CLOCKWISE_NAME, '0'], [Blockly.Msg.OSBOT_ANTICLOCKWISE_NAME, '1']];
    
    this.appendValueInput("SPEED")
        .setCheck("Number")
        .appendField(Blockly.Msg.OSBOT_MOTOR_TITLE)
        .appendField(new Blockly.FieldDropdown(motors), "MOTOR")
        .appendField(Blockly.Msg.OSBOT_MOTOR_DIRECTION_NAME)
        .appendField(new Blockly.FieldDropdown(directions), "DIRECTION")
        .appendField(Blockly.Msg.OSBOT_MOTOR_SPEED_NAME);
    this.appendDummyInput()
        .appendField(new Blockly.FieldImage("https://www.gstatic.com/codesite/ph/images/star_on.gif", 15, 15, "*"));
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(15);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_delay'] = {
  init: function() {
    this.appendValueInput("MS")
        .setCheck("Number")
        .appendField(Blockly.Msg.OSBOT_DELAY_TITLE);
    this.appendDummyInput()
        .appendField(Blockly.Msg.OSBOT_DELAY_UNIT_NAME);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(165);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};

Blockly.Blocks['osbot_voice'] = {
  init: function() {
    this.appendValueInput("SONGID")
        .setCheck("Number")
        .appendField(new Blockly.FieldImage("https://www.gstatic.com/codesite/ph/images/star_on.gif", 15, 15, "*"))
        .appendField(Blockly.Msg.OSBOT_VOICE_TITLE)
        .appendField(Blockly.Msg.OSBOT_TRACK_NAME);
    this.appendValueInput("VOLUME")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.Msg.OSBOT_VOLUME_NAME);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(285);
    this.setTooltip('');
    this.setHelpUrl('http://www.example.com/');
  }
};