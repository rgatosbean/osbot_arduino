/*!
// DESC:
//       OSBot
//
// mostly from generators/javascript.js
*/

'use strict';

goog.provide('Blockly.OSBot');

goog.require('Blockly.Generator');

Blockly.OSBot = new Blockly.Generator('OSBot');

Blockly.OSBot.addReservedWords(
    'Blockly,' +  // In case JS is evaled in the current window.
    // https://developer.mozilla.org/en/JavaScript/Reference/Reserved_Words
    'break,case,catch,continue,debugger,default,delete,do,else,finally,for,function,if,in,instanceof,new,return,switch,this,throw,try,typeof,var,void,while,with,' +
    'class,enum,export,extends,import,super,implements,interface,let,package,private,protected,public,static,yield,' +
    'const,null,true,false,' +
    // https://developer.mozilla.org/en/JavaScript/Reference/Global_Objects
    'Array,ArrayBuffer,Boolean,Date,decodeURI,decodeURIComponent,encodeURI,encodeURIComponent,Error,eval,EvalError,Float32Array,Float64Array,Function,Infinity,Int16Array,Int32Array,Int8Array,isFinite,isNaN,Iterator,JSON,Math,NaN,Number,Object,parseFloat,parseInt,RangeError,ReferenceError,RegExp,StopIteration,String,SyntaxError,TypeError,Uint16Array,Uint32Array,Uint8Array,Uint8ClampedArray,undefined,uneval,URIError,' +
    // https://developer.mozilla.org/en/DOM/window
    'applicationCache,closed,Components,content,_content,controllers,crypto,defaultStatus,dialogArguments,directories,document,frameElement,frames,fullScreen,globalStorage,history,innerHeight,innerWidth,length,location,locationbar,localStorage,menubar,messageManager,mozAnimationStartTime,mozInnerScreenX,mozInnerScreenY,mozPaintCount,name,navigator,opener,outerHeight,outerWidth,pageXOffset,pageYOffset,parent,performance,personalbar,pkcs11,returnValue,screen,screenX,screenY,scrollbars,scrollMaxX,scrollMaxY,scrollX,scrollY,self,sessionStorage,sidebar,status,statusbar,toolbar,top,URL,window,' +
    'addEventListener,alert,atob,back,blur,btoa,captureEvents,clearImmediate,clearInterval,clearTimeout,close,confirm,disableExternalCapture,dispatchEvent,dump,enableExternalCapture,escape,find,focus,forward,GeckoActiveXObject,getAttention,getAttentionWithCycleCount,getComputedStyle,getSelection,home,matchMedia,maximize,minimize,moveBy,moveTo,mozRequestAnimationFrame,open,openDialog,postMessage,print,prompt,QueryInterface,releaseEvents,removeEventListener,resizeBy,resizeTo,restore,routeEvent,scroll,scrollBy,scrollByLines,scrollByPages,scrollTo,setCursor,setImmediate,setInterval,setResizable,setTimeout,showModalDialog,sizeToContent,stop,unescape,updateCommands,XPCNativeWrapper,XPCSafeJSObjectWrapper,' +
    'onabort,onbeforeunload,onblur,onchange,onclick,onclose,oncontextmenu,ondevicemotion,ondeviceorientation,ondragdrop,onerror,onfocus,onhashchange,onkeydown,onkeypress,onkeyup,onload,onmousedown,onmousemove,onmouseout,onmouseover,onmouseup,onmozbeforepaint,onpaint,onpopstate,onreset,onresize,onscroll,onselect,onsubmit,onunload,onpageshow,onpagehide,' +
    'Image,Option,Worker,' +
    // https://developer.mozilla.org/en/Gecko_DOM_Reference
    'Event,Range,File,FileReader,Blob,BlobBuilder,' +
    'Attr,CDATASection,CharacterData,Comment,console,DocumentFragment,DocumentType,DomConfiguration,DOMError,DOMErrorHandler,DOMException,DOMImplementation,DOMImplementationList,DOMImplementationRegistry,DOMImplementationSource,DOMLocator,DOMObject,DOMString,DOMStringList,DOMTimeStamp,DOMUserData,Entity,EntityReference,MediaQueryList,MediaQueryListListener,NameList,NamedNodeMap,Node,NodeFilter,NodeIterator,NodeList,Notation,Plugin,PluginArray,ProcessingInstruction,SharedWorker,Text,TimeRanges,Treewalker,TypeInfo,UserDataHandler,Worker,WorkerGlobalScope,' +
    'HTMLDocument,HTMLElement,HTMLAnchorElement,HTMLAppletElement,HTMLAudioElement,HTMLAreaElement,HTMLBaseElement,HTMLBaseFontElement,HTMLBodyElement,HTMLBRElement,HTMLButtonElement,HTMLCanvasElement,HTMLDirectoryElement,HTMLDivElement,HTMLDListElement,HTMLEmbedElement,HTMLFieldSetElement,HTMLFontElement,HTMLFormElement,HTMLFrameElement,HTMLFrameSetElement,HTMLHeadElement,HTMLHeadingElement,HTMLHtmlElement,HTMLHRElement,HTMLIFrameElement,HTMLImageElement,HTMLInputElement,HTMLKeygenElement,HTMLLabelElement,HTMLLIElement,HTMLLinkElement,HTMLMapElement,HTMLMenuElement,HTMLMetaElement,HTMLModElement,HTMLObjectElement,HTMLOListElement,HTMLOptGroupElement,HTMLOptionElement,HTMLOutputElement,HTMLParagraphElement,HTMLParamElement,HTMLPreElement,HTMLQuoteElement,HTMLScriptElement,HTMLSelectElement,HTMLSourceElement,HTMLSpanElement,HTMLStyleElement,HTMLTableElement,HTMLTableCaptionElement,HTMLTableCellElement,HTMLTableDataCellElement,HTMLTableHeaderCellElement,HTMLTableColElement,HTMLTableRowElement,HTMLTableSectionElement,HTMLTextAreaElement,HTMLTimeElement,HTMLTitleElement,HTMLTrackElement,HTMLUListElement,HTMLUnknownElement,HTMLVideoElement,' +
    'HTMLCanvasElement,CanvasRenderingContext2D,CanvasGradient,CanvasPattern,TextMetrics,ImageData,CanvasPixelArray,HTMLAudioElement,HTMLVideoElement,NotifyAudioAvailableEvent,HTMLCollection,HTMLAllCollection,HTMLFormControlsCollection,HTMLOptionsCollection,HTMLPropertiesCollection,DOMTokenList,DOMSettableTokenList,DOMStringMap,RadioNodeList,' +
    'SVGDocument,SVGElement,SVGAElement,SVGAltGlyphElement,SVGAltGlyphDefElement,SVGAltGlyphItemElement,SVGAnimationElement,SVGAnimateElement,SVGAnimateColorElement,SVGAnimateMotionElement,SVGAnimateTransformElement,SVGSetElement,SVGCircleElement,SVGClipPathElement,SVGColorProfileElement,SVGCursorElement,SVGDefsElement,SVGDescElement,SVGEllipseElement,SVGFilterElement,SVGFilterPrimitiveStandardAttributes,SVGFEBlendElement,SVGFEColorMatrixElement,SVGFEComponentTransferElement,SVGFECompositeElement,SVGFEConvolveMatrixElement,SVGFEDiffuseLightingElement,SVGFEDisplacementMapElement,SVGFEDistantLightElement,SVGFEFloodElement,SVGFEGaussianBlurElement,SVGFEImageElement,SVGFEMergeElement,SVGFEMergeNodeElement,SVGFEMorphologyElement,SVGFEOffsetElement,SVGFEPointLightElement,SVGFESpecularLightingElement,SVGFESpotLightElement,SVGFETileElement,SVGFETurbulenceElement,SVGComponentTransferFunctionElement,SVGFEFuncRElement,SVGFEFuncGElement,SVGFEFuncBElement,SVGFEFuncAElement,SVGFontElement,SVGFontFaceElement,SVGFontFaceFormatElement,SVGFontFaceNameElement,SVGFontFaceSrcElement,SVGFontFaceUriElement,SVGForeignObjectElement,SVGGElement,SVGGlyphElement,SVGGlyphRefElement,SVGGradientElement,SVGLinearGradientElement,SVGRadialGradientElement,SVGHKernElement,SVGImageElement,SVGLineElement,SVGMarkerElement,SVGMaskElement,SVGMetadataElement,SVGMissingGlyphElement,SVGMPathElement,SVGPathElement,SVGPatternElement,SVGPolylineElement,SVGPolygonElement,SVGRectElement,SVGScriptElement,SVGStopElement,SVGStyleElement,SVGSVGElement,SVGSwitchElement,SVGSymbolElement,SVGTextElement,SVGTextPathElement,SVGTitleElement,SVGTRefElement,SVGTSpanElement,SVGUseElement,SVGViewElement,SVGVKernElement,' +
    'SVGAngle,SVGColor,SVGICCColor,SVGElementInstance,SVGElementInstanceList,SVGLength,SVGLengthList,SVGMatrix,SVGNumber,SVGNumberList,SVGPaint,SVGPoint,SVGPointList,SVGPreserveAspectRatio,SVGRect,SVGStringList,SVGTransform,SVGTransformList,' +
    'SVGAnimatedAngle,SVGAnimatedBoolean,SVGAnimatedEnumeration,SVGAnimatedInteger,SVGAnimatedLength,SVGAnimatedLengthList,SVGAnimatedNumber,SVGAnimatedNumberList,SVGAnimatedPreserveAspectRatio,SVGAnimatedRect,SVGAnimatedString,SVGAnimatedTransformList,' +
    'SVGPathSegList,SVGPathSeg,SVGPathSegArcAbs,SVGPathSegArcRel,SVGPathSegClosePath,SVGPathSegCurvetoCubicAbs,SVGPathSegCurvetoCubicRel,SVGPathSegCurvetoCubicSmoothAbs,SVGPathSegCurvetoCubicSmoothRel,SVGPathSegCurvetoQuadraticAbs,SVGPathSegCurvetoQuadraticRel,SVGPathSegCurvetoQuadraticSmoothAbs,SVGPathSegCurvetoQuadraticSmoothRel,SVGPathSegLinetoAbs,SVGPathSegLinetoHorizontalAbs,SVGPathSegLinetoHorizontalRel,SVGPathSegLinetoRel,SVGPathSegLinetoVerticalAbs,SVGPathSegLinetoVerticalRel,SVGPathSegMovetoAbs,SVGPathSegMovetoRel,ElementTimeControl,TimeEvent,SVGAnimatedPathData,' +
    'SVGAnimatedPoints,SVGColorProfileRule,SVGCSSRule,SVGExternalResourcesRequired,SVGFitToViewBox,SVGLangSpace,SVGLocatable,SVGRenderingIntent,SVGStylable,SVGTests,SVGTextContentElement,SVGTextPositioningElement,SVGTransformable,SVGUnitTypes,SVGURIReference,SVGViewSpec,SVGZoomAndPan');

// Codes below are from BlockArduino
/**
 * Visual Blocks Language
 *
 * Copyright 2012 Google Inc.
 * http://code.google.com/p/blockly/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
Blockly.OSBot.ORDER_ATOMIC = 0;         // 0 "" ...
Blockly.OSBot.ORDER_MEMBER = 1;         // . []
Blockly.OSBot.ORDER_NEW = 1;            // new
Blockly.OSBot.ORDER_FUNCTION_CALL = 2;  // ()
Blockly.OSBot.ORDER_INCREMENT = 3;      // ++
Blockly.OSBot.ORDER_DECREMENT = 3;      // --
Blockly.OSBot.ORDER_LOGICAL_NOT = 4;    // !
Blockly.OSBot.ORDER_BITWISE_NOT = 4;    // ~
Blockly.OSBot.ORDER_UNARY_PLUS = 4;     // +
Blockly.OSBot.ORDER_UNARY_NEGATION = 4; // -
Blockly.OSBot.ORDER_TYPEOF = 4;         // typeof
Blockly.OSBot.ORDER_VOID = 4;           // void
Blockly.OSBot.ORDER_DELETE = 4;         // delete
Blockly.OSBot.ORDER_MULTIPLICATION = 5; // *
Blockly.OSBot.ORDER_DIVISION = 5;       // /
Blockly.OSBot.ORDER_MODULUS = 5;        // %
Blockly.OSBot.ORDER_ADDITION = 6;       // +
Blockly.OSBot.ORDER_SUBTRACTION = 6;    // -
Blockly.OSBot.ORDER_BITWISE_SHIFT = 7;  // << >> >>>
Blockly.OSBot.ORDER_RELATIONAL = 8;     // < <= > >=
Blockly.OSBot.ORDER_IN = 8;             // in
Blockly.OSBot.ORDER_INSTANCEOF = 8;     // instanceof
Blockly.OSBot.ORDER_EQUALITY = 9;       // == != === !==
Blockly.OSBot.ORDER_BITWISE_AND = 10;   // &
Blockly.OSBot.ORDER_BITWISE_XOR = 11;   // ^
Blockly.OSBot.ORDER_BITWISE_OR = 12;    // |
Blockly.OSBot.ORDER_LOGICAL_AND = 13;   // &&
Blockly.OSBot.ORDER_LOGICAL_OR = 14;    // ||
Blockly.OSBot.ORDER_CONDITIONAL = 15;   // ?:
Blockly.OSBot.ORDER_ASSIGNMENT = 16;    // = += -= *= /= %= <<= >>= ...
Blockly.OSBot.ORDER_COMMA = 17;         // ,
Blockly.OSBot.ORDER_NONE = 99;          // (...)

/*
 * Arduino Board profiles
 *
 */
var profile = {
  osbot1: {
      description: "OSBOT version1 ?",
      // RJ25 for sensors
      // RJ25ID, #1, #2
      // RJ25可以外挂的设备, 避障传感器, 循迹传感器, LCD?
      // 传感器接口列表
      sensorif: [
          ['D11', 'D8'],
          ["A2", "A3"],
          ["D10", "D9"],
          ["A0", "A1"],
          ["D3", "D2"],
          ["D14", "D15"]
      ],
      // 可用的端口列表
      rj25s: [
        [Blockly.Msg.OSBOT_RJ25_NAME + ':0', '0'],
        [Blockly.Msg.OSBOT_RJ25_NAME + ':1', '1'],
        [Blockly.Msg.OSBOT_RJ25_NAME + ':2', '2'],
        [Blockly.Msg.OSBOT_RJ25_NAME + ':3', '3'],
        [Blockly.Msg.OSBOT_RJ25_NAME + ':4', '4'],
        [Blockly.Msg.OSBOT_RJ25_NAME + ':5', '5'],
      ],
      // 不知道英文怎么写, 简单粗暴了
      bzsensors:[[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']],
      // 循迹传感器
      xjsensors:[[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']],
      // 电机接口 DIR, SPEED
      motorif:[["4", "5"], ["6", "7"]],
      // 可用的电机列表
      motors:[[Blockly.Msg.OSBOT_LEFT_NAME, '0'], [Blockly.Msg.OSBOT_RIGHT_NAME, '1']],
      // 可用的方向
      motordirections:[[Blockly.Msg.OSBOT_CLOCKWISE_NAME, '0'], [Blockly.Msg.OSBOT_ANTICLOCKWISE_NAME, '1']],
      //
      eyeicons:[
        [Blockly.Msg.OSBOT_ICON_NAME + '0', '0'],
        [Blockly.Msg.OSBOT_ICON_NAME + '1', '1'],
        [Blockly.Msg.OSBOT_ICON_NAME + '2', '2'],
        [Blockly.Msg.OSBOT_ICON_NAME + '3', '3'],
        [Blockly.Msg.OSBOT_ICON_NAME + '4', '4'],
        [Blockly.Msg.OSBOT_ICON_NAME + '5', '5'],
        [Blockly.Msg.OSBOT_ICON_NAME + '6', '6'],
        [Blockly.Msg.OSBOT_ICON_NAME + '7', '7'],
        [Blockly.Msg.OSBOT_ICON_NAME + '8', '8'],
        [Blockly.Msg.OSBOT_ICON_NAME + '9', '9']
      ],
      mouthicons:[
        [Blockly.Msg.OSBOT_ICON_NAME + '0', '0'],
        [Blockly.Msg.OSBOT_ICON_NAME + '1', '1'],
        [Blockly.Msg.OSBOT_ICON_NAME + '2', '2'],
        [Blockly.Msg.OSBOT_ICON_NAME + '3', '3'],
        [Blockly.Msg.OSBOT_ICON_NAME + '4', '4']
      ],
      // baudrate
      serial: 57600
  }
};
//set default profile for osbot
profile["default"] = profile["osbot1"];

/**
 * Initialise the database of variable names.
 * @param {!Blockly.Workspace} workspace Workspace to generate code from.
 */
Blockly.OSBot.init = function(workspace) {
  // Create a dictionary of definitions to be printed before the code.
  Blockly.OSBot.definitions_ = Object.create(null);
  // Create a dictionary mapping desired function names in definitions_
  // to actual function names (to avoid collisions with user functions).
  Blockly.OSBot.functionNames_ = Object.create(null);

  if (!Blockly.OSBot.variableDB_) {
    Blockly.OSBot.variableDB_ =
        new Blockly.Names(Blockly.OSBot.RESERVED_WORDS_);
  } else {
    Blockly.OSBot.variableDB_.reset();
  }

  var defvars = [];
  var variables = Blockly.Variables.allVariables(workspace);
  for (var i = 0; i < variables.length; i++) {
    defvars[i] = 'var ' +
        Blockly.OSBot.variableDB_.getName(variables[i],
        Blockly.Variables.NAME_TYPE) + ';';
  }
  Blockly.OSBot.definitions_['variables'] = defvars.join('\n');
};

/**
 * Prepend the generated code with the variable definitions.
 * @param {string} code Generated code.
 * @return {string} Completed code.
 */
Blockly.OSBot.finish = function(code) {
  // Convert the definitions dictionary into a list.
  var definitions = [];
  for (var name in Blockly.OSBot.definitions_) {
    definitions.push(Blockly.OSBot.definitions_[name]);
  }
  // Clean up temporary data.
  delete Blockly.OSBot.definitions_;
  delete Blockly.OSBot.functionNames_;
  Blockly.OSBot.variableDB_.reset();
  return definitions.join('\n\n') + '\n\n\n' + code;
};

/**
 * Naked values are top-level blocks with outputs that aren't plugged into
 * anything.  A trailing semicolon is needed to make this legal.
 * @param {string} line Line of generated code.
 * @return {string} Legal line of code.
 */
Blockly.OSBot.scrubNakedValue = function(line) {
  return line + ';\n';
};

/**
 * Encode a string as a properly escaped JavaScript string, complete with
 * quotes.
 * @param {string} string Text to encode.
 * @return {string} JavaScript string.
 * @private
 */
Blockly.OSBot.quote_ = function(string) {
  // TODO: This is a quick hack.  Replace with goog.string.quote
  string = string.replace(/\\/g, '\\\\')
                 .replace(/\n/g, '\\\n')
                 .replace(/'/g, '\\\'');
  return '\'' + string + '\'';
};

/**
 * Common tasks for generating JavaScript from blocks.
 * Handles comments for the specified block and any connected value blocks.
 * Calls any statements following this block.
 * @param {!Blockly.Block} block The current block.
 * @param {string} code The JavaScript code created for this block.
 * @return {string} JavaScript code with comments and subsequent blocks added.
 * @private
 */
Blockly.OSBot.scrub_ = function(block, code) {
  var commentCode = '';
  // Only collect comments for blocks that aren't inline.
  if (!block.outputConnection || !block.outputConnection.targetConnection) {
    // Collect comment for this block.
    var comment = block.getCommentText();
    if (comment) {
      commentCode += Blockly.OSBot.prefixLines(comment, '// ') + '\n';
    }
    // Collect comments for all value arguments.
    // Don't collect comments for nested statements.
    for (var x = 0; x < block.inputList.length; x++) {
      if (block.inputList[x].type == Blockly.INPUT_VALUE) {
        var childBlock = block.inputList[x].connection.targetBlock();
        if (childBlock) {
          var comment = Blockly.OSBot.allNestedComments(childBlock);
          if (comment) {
            commentCode += Blockly.OSBot.prefixLines(comment, '// ');
          }
        }
      }
    }
  }
  var nextBlock = block.nextConnection && block.nextConnection.targetBlock();
  var nextCode = Blockly.OSBot.blockToCode(nextBlock);
  return commentCode + code + nextCode;
};
