///////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2013 Tarek Sherif
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////

utils = {
  // CaptureMouse code from Foundation HTML5 Animation with JavaScript
  // by Billy Lamberta and Keith Peters
  captureMouse: function(canvas) {
    var mouse = {x: 0, y: 0};
    
    canvas.addEventListener("mousemove", function(e) {
      var x, y;
      
      if (e.pageX !== undefined) {
        x = e.pageX;
        y = e.pageY;
      } else {
        x = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;
        y = e.clientY + document.body.scrollTop + document.documentElement.scrollTop;
      }
      
      x -= canvas.offsetLeft;
      y -= canvas.offsetTop;
      
      mouse.x = x;
      mouse.y = y;
    }, false);
    
    return mouse;
  },
  
  // CaptureTouch code from Foundation HTML5 Animation with JavaScript
  // by Billy Lamberta and Keith Peters
  captureTouch: function(canvas) {
    var touch = {x: null, y: null, touching: false};
    
    canvas.addEventListener("touchstart", function(e) {
      touch.touching = true;
    }, false);
    
    canvas.addEventListener("touchend", function(e) {
      touch.x = null;
      touch.y = null;
      touch.touching = false;
    }, false);
    
    canvas.addEventListener("touchmove", function(event) {
      var x, y;
      var e = event.touches[0];
      
      if (e.pageX !== undefined) {
        x = e.pageX;
        y = e.pageY;
      } else {
        x = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;
        y = e.clientY + document.body.scrollTop + document.documentElement.scrollTop;
      }
      
      x -= canvas.offsetLeft;
      y -= canvas.offsetTop;
      
      touch.x = x;
      touch.y = y;
    }, false);
    
    return touch;
  },
  
  clamp: function(value, min, max) {
    return value < min ? min :
           value > max ? max :
           value;
  },
  
  colorShift: function(color, shift_range) {
    color = utils.parseColor(color, true);
    shift_range = shift_range || 0;
    
    var r = color >> 16 & 0xFF;
    var g = color >> 8 & 0xFF;
    var b = color & 0xFF;
            
    r = utils.clamp(r + Math.floor(Math.random() * shift_range - shift_range / 2), 0, 255);
    b = utils.clamp(b + Math.floor(Math.random() * shift_range - shift_range / 2), 0, 255);
    g = utils.clamp(g + Math.floor(Math.random() * shift_range - shift_range / 2), 0, 255);
    
    return utils.parseColor(r << 16 | b << 8 | g);
  },
  
  parseColor: function(color, to_number) {
    if (to_number) {
      if (typeof color === "number") {
        return color |= 0;
      }
      if (typeof color === "string" && color[0] === "#") {
        color = color.slice(1);
      }
      return parseInt(color, 16);
    } else {
      if (typeof color === "number") {
        color = "#" + ("00000" + color.toString(16)).slice(-6);
      }
      return color;
    }
  },
  
  drawDot: function(context, x, y, color) {
    color = color || "#ff0000";
    utils.withContext(context, function() {
      context.fillStyle = color;
      context.fillRect(x - 2, y - 2, 4, 4);
    });
  },
  
  withContext: function(context, callback) {
    context.save();
    callback();
    context.restore();
  },
  
  randomColor: function() {
    return "rgb(" + Math.floor(Math.random() * 255) + ","
                  + Math.floor(Math.random() * 255) + ","
                  + Math.floor(Math.random() * 255) + ")";
  },
  
  colorToRGB: function(r, g, b, a) {
    a = a === undefined ? 1.0 : a;
    return "rgba(" + r + ","
                   + g + ","
                   + b + ","
                   + a +")";
  },
  
  multiplyColor: function(color, alpha) {
    color = utils.parseColor(color, true);
    var r = Math.floor(alpha * (color >> 16 & 0xFF));
    var g = Math.floor(alpha * (color >> 8 & 0xFF));
    var b = Math.floor(alpha * (color & 0xFF));
    
    return utils.parseColor(r << 16 | g << 8 | b);
  }
};
