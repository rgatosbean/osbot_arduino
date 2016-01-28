    function $(id){  
        return document.getElementById(id);  
    }  
    /** the main functionality of splitter **/  
    var Splitter = {  
        container: null,  
        lPanel: null,  
        rPanel: null,  
        bar: null,  
        movingBar: null,  
        //左面板初始，最大，最小宽度  
        lPanelInitWidth: '250px',  
        lPanelMaxWidth: '500px',  
        lPanelMinWidth: '200px',  
        rPanelInitWidth: '800px',  
        rPanelMaxWidth: '999px',  
        rPanelMinWidth: '500px',  
        //分隔线被拖动的时候的颜色  
        barActiveColor: '#165373',  
        //左面的面板是否设置最大/最小宽度  
        isWidthLimit: true,  
        init: function(config){  
            if(!config.id){  
                alert('Can not initialize splitter.');  
                return;  
            }  
            if($(config.id)){  
                this.container = $(config.id);  
                if(!($('splitter_left_panel')&&$('splitter_right_panel')&&$('splitter_bar'))){  
                    alert('Can not initialize splitter.');  
                    return;  
                }else{  
                    this.lPanel = $('splitter_left_panel');  
                    this.rPanel = $('splitter_right_panel');  
                    this.bar = $('splitter_bar');  
                }  
            }  
  
            if(config.lPanelMaxWidth){  
                this.lPanelMaxWidth = config.lPanelMaxWidth;  
            }  
            if(config.lPanelMinWidth){  
                this.lPanelMinWidth = config.lPanelMinWidth;  
            }  
            if(config.rPanelMaxWidth){  
                this.rPanelMaxWidth = config.rPanelMaxWidth;  
            }  
            if(config.rPanelMinWidth){  
                this.rPanelMinWidth = config.rPanelMinWidth;  
            }  
            if(config.lPanelInitWidth){  
                this.lPanelInitWidth = config.lPanelInitWidth;  
            }  
            if(config.rPanelInitWidth){  
                this.rPanelInitWidth = config.rPanelInitWidth;  
            }  
            if(config.barActiveColor){  
                this.barActiveColor = config.barActiveColor;  
            }  
            //alert(typeof(config.isWidthLimit));  
            if(config.isWidthLimit!=undefined){  
                this.isWidthLimit = config.isWidthLimit;  
            }  
            var mask = document.createElement('div');  
            document.body.appendChild(mask);  
            with(mask.style){  
                position = 'absolute';  
                left = '0px';  
                top = '0px';  
                zIndex = 900;  
                width = '100%';  
                height = '100%';  
                display = 'none';  
                backgroundColor = '#ccc';  
                filter = 'alpha(opacity=10)';  
            }  
            //background-color:red;filter:alpha(opacity=60)  
            Splitter.mask = mask;  
            this.bar.onmousedown = Splitter.start;  
        },  
        start: function(event){  
            var o = Splitter.container;  
            event = event || window.event;  
            o.lastMouseX = event.clientX;  
            if(document.all){  
                Splitter.mask.style.display = '';  
            }else{  
                // ff nothing;  
            }  
            var movingBar = document.createElement('div');  
            Splitter.container.appendChild(movingBar);  
            with(movingBar.style){  
                position = 'absolute';  
                left = Splitter.bar.offsetLeft + 'px';  
                top = '0px';  
                if(document.all){  
                    width = Splitter.bar.currentStyle.width;  
                }  
                else{  
                    width = window.getComputedStyle(Splitter.bar,null).getPropertyValue('width');  
                }  
                height = '100%';                          
                backgroundColor = Splitter.barActiveColor;  
                zIndex = 999;  
                cursor = 'col-resize';  
            }                                     
            movingBar.dx = 0;  
            Splitter.movingBar = movingBar;  
            document.onmousemove = Splitter.move;  
            document.onmouseup = Splitter.end;  
        },  
        move: function(event){  
            var o = Splitter.container;  
            event = event || window.event;  
            var dx = event.clientX - o.lastMouseX;  
            Splitter.movingBar.dx = Splitter.movingBar.dx + dx;  
            var left = parseInt(Splitter.movingBar.style.left) + dx;  
            Splitter.movingBar.style.left = left;  
            o.lastMouseX = event.clientX;  
        },  
        end: function(event){  
            event = event || window.event;  
            document.onmousemove = null;  
            document.onmouseup = null;  
            Splitter.mask.style.display = 'none';  
            var dx = Splitter.movingBar.dx;  
            Splitter.container.removeChild(Splitter.movingBar);  
            if(document.all){  
                width = Splitter.lPanel.currentStyle.width;  
            }  
            else{  
                width = window.getComputedStyle(Splitter.lPanel,null).getPropertyValue('width');  
            }  
            var w = parseInt(width) + dx;     
                          
            if(Splitter.isWidthLimit){  
                var _width = (w > parseInt(Splitter.lPanelMaxWidth) ? Splitter.lPanelMaxWidth : (w < parseInt(Splitter.lPanelMinWidth) ?  
                Splitter.lPanelMinWidth : w));  
                w = _width;  
            }  
            Splitter.lPanel.style.width = w;  
                                      
        }  
    };  