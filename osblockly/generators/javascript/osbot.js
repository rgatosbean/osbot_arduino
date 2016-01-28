// generator

'use strict'

goog.provide('Blockly.JavaScript.osbot');

goog.require('Blockly.JavaScript');

Blockly.JavaScript['osbot_bzsensor'] = function(block) {
  var sensorid = block.getFieldValue('BZSENSOR');
  var rj25id = block.getFieldValue('RJ25');
 
  var code = 'OSA.digitalRead(' + profile.default.sensorif[rj25id][sensorid] + ')';
  
  return [code, Blockly.JavaScript.ORDER_ATOMIC];
};

Blockly.JavaScript['osbot_xjsensor'] = function(block) {
  var sensorid = block.getFieldValue('XJSENSOR');
  var rj25id = block.getFieldValue('RJ25');
 
  var code = 'OSA.digitalRead(' + profile.default.sensorif[rj25id][sensorid] + ')';
  
  return [code, Blockly.JavaScript.ORDER_ATOMIC];
};

Blockly.JavaScript['osbot_face'] = function(block) {
  var rj25id = block.getFieldValue('RJ25');
  var eyeiconid = block.getFieldValue('EYE');
  
  var code = 'OSA.SendSerial("OSW.01.' + rj25id + '.' + '0' + '.' + eyeiconid + '.' + '0' + '");\n';
  
  return code;
};

Blockly.JavaScript['osbot_textout'] = function(block) {
  var content = Blockly.JavaScript.valueToCode(block, 'CONTENT', Blockly.JavaScript.ORDER_ATOMIC);
  var x = Blockly.JavaScript.valueToCode(block, 'X', Blockly.JavaScript.ORDER_ATOMIC);
  var y = Blockly.JavaScript.valueToCode(block, 'Y', Blockly.JavaScript.ORDER_ATOMIC);
  var color = block.getFieldValue('COLOR');

  var style = '"OSW.02.' + color.colorRgb() + '.' + x + '.' + y + '"';
  var text = '"OSW.03.' + content.replace(/\'/g,"") + '"';
  
  var code = 'OSA.SendSerial("OSW.02.' + color.colorRgb() + '.' + x + '.' + y + '");\n' +
             'OSA.SendSerial("OSW.03.' + content.replace(/\'/g, "") + '");\n';
  
  return code;
};

Blockly.JavaScript['osbot_motor'] = function(block) {
  var motor = block.getFieldValue('MOTOR');
  var direction = block.getFieldValue('DIRECTION');
  var speed = Blockly.JavaScript.valueToCode(block, 'SPEED', Blockly.JavaScript.ORDER_ATOMIC);
  
  var code = 'OSA.digitalWrite(' + profile.default.motorif[motor][0] + ', ' + direction + ');\n' +
             'OSA.analogWrite(' + profile.default.motorif[motor][1] + ', ' + speed + ');\n';
  return code;
};

Blockly.JavaScript['osbot_delay'] = function(block) {
  var ms = Blockly.JavaScript.valueToCode(block, 'MS', Blockly.JavaScript.ORDER_ATOMIC);
  
  var functionName = Blockly.JavaScript.provideFunction_(
      'osbot_delay',
      [ 'function ' + Blockly.JavaScript.FUNCTION_NAME_PLACEHOLDER_ +
          '(time) {',
        '  var start = new Date().getTime();',
        '  while (true) {',
        '    if (new Date().getTime() - start > time) {',
        '      break;',
        '    }',
        '  }',
        '}']);
  var code = functionName + '(' + ms + ');\n';
  
  return code;
};

Blockly.JavaScript['osbot_voice'] = function(block) {
  var value_songid = Blockly.JavaScript.valueToCode(block, 'SONGID', Blockly.JavaScript.ORDER_ATOMIC);
  var value_volume = Blockly.JavaScript.valueToCode(block, 'VOLUME', Blockly.JavaScript.ORDER_ATOMIC);
  var code = 'OSA.SendSerial("OSW.04.' + value_songid + '.' + value_volume + '");';
  return code;
};
