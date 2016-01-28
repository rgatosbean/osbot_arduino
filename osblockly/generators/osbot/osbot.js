// generator

'use strict'

goog.provide('Blockly.OSBot.osbot');

goog.require('Blockly.OSBot');

Blockly.OSBot['osbot_bzsensor'] = function(block) {
  var sensorid = block.getFieldValue('BZSENSOR');
  var rj25id = block.getFieldValue('RJ25');
 
  var code = 'OSA.digitalRead(' + profile.default.sensorif[rj25id][sensorid] + ')';
  
  return [code, Blockly.OSBot.ORDER_ATOMIC];
};

Blockly.OSBot['osbot_xjsensor'] = function(block) {
  var sensorid = block.getFieldValue('XJSENSOR');
  var rj25id = block.getFieldValue('RJ25');
 
  var code = 'OSA.digitalRead(' + profile.default.sensorif[rj25id][sensorid] + ')';
  
  return [code, Blockly.OSBot.ORDER_ATOMIC];
};

Blockly.OSBot['osbot_face'] = function(block) {
  var rj25id = block.getFieldValue('RJ25');
  var eyeiconid = block.getFieldValue('EYE');
  var mouthiconid = block.getFieldValue('MOUTH');
  // ? 
  var code = 'OSA.SendArduino("OSW.01.' + rj25id + '.' + '?' + '.' + eyeiconid + '.' + mouthiconid + '");\n';
  
  return code;
};

Blockly.OSBot['osbot_textout'] = function(block) {
  var content = Blockly.OSBot.valueToCode(block, 'CONTENT', Blockly.OSBot.ORDER_ATOMIC);
  var x = Blockly.OSBot.valueToCode(block, 'X', Blockly.OSBot.ORDER_ATOMIC);
  var y = Blockly.OSBot.valueToCode(block, 'Y', Blockly.OSBot.ORDER_ATOMIC);
  var color = block.getFieldValue('COLOR');

  var style = '"OSW.02.' + color.colorRgb() + '.' + x + '.' + y + '"';
  var text = '"OSW.03.' + content.replace(/\'/g,"") + '"';
  
  var code = 'OSA.SendArduino("OSW.02.' + color.colorRgb() + '.' + x + '.' + y + '");\n' +
             'OSA.SendArduino("OSW.03.' + content.replace(/\'/g, "") + '");\n';
  
  return code;
};

Blockly.OSBot['osbot_motor'] = function(block) {
  var motor = block.getFieldValue('MOTOR');
  var direction = block.getFieldValue('DIRECTION');
  var speed = Blockly.OSBot.valueToCode(block, 'SPEED', Blockly.OSBot.ORDER_ATOMIC);
  
  var code = 'OSA.digitalWrite(' + profile.default.motorif[motor][0] + ', ' + direction + ');\n' +
             'OSA.analogWrite(' + profile.default.motorif[motor][1] + ', ' + speed + ');\n';
  return code;
};

Blockly.OSBot['osbot_delay'] = function(block) {
  var ms = Blockly.OSBot.valueToCode(block, 'MS', Blockly.OSBot.ORDER_ATOMIC);
  // TODO: Assemble OSBot into code variable.
  var code = 'setTimeout(";", ' + ms + ');\n';
  return code;
};
