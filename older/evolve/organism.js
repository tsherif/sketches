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

var organism = ball.clone().share({
  move: function(delta) {
    if (this.state === "dead") return;
  
    if (this.state === "dying") {
      this.radius *= 0.9;
      
      if (this.radius < 1) {
        this.state = "dead";
      }
      
      return;
    }
    if (this.state === "born") {
      this.scale_x *= 1.1;
      this.scale_y *= 1.1;
      
      if (this.scale_x > 1) {
        this.scale_x = 1;
        this.scale_y = 1;
        this.state = "alive";
      }
      
      return;
    }
  
    var dx = this.tx - this.x;
    var dy = this.ty - this.y;
    var d = Math.sqrt(dx * dx + dy * dy);
    var scale_factor = 1 + utils.clamp(this.easing * d / 6, 0, 1);
    if (d < 5){
      this.newTarget();
                
      dx = this.tx - this.x;
      dy = this.ty - this.y;
    }
        
    this.scale_x = 1 * scale_factor;
    this.scale_y = 1 / scale_factor;     
    
    this.x += dx * this.easing * delta;
    this.y += dy * this.easing * delta;
  },
  
  newTarget: function() {
    var dx;
    var dy;
    
    this.tx = this.x + Math.random() * this.range - this.range / 2;
    this.ty = this.y + Math.random() * this.range - this.range / 2;
    
    this.tx = this.tx - this.radius < 0 ? this.radius :
              this.tx + this.radius > canvas.width ? canvas.width - this.radius :
              this.tx;
              
    this.ty = this.ty - this.radius < 0 ? this.radius :
              this.ty + this.radius  > canvas.height ? canvas.height - this.radius  :
              this.ty;
    
    dx = this.tx - this.x;
    dy = this.ty - this.y;
    
    // 90 degree rotation seems not to work in Chrome.
    if (Math.abs(dx) < 0.1) dx = 0.1;
    if (Math.abs(dy) < 0.1) dy = 0.1;
    
    this.rotation = Math.atan2(dy, dx);
  },
  
  reproduce: function() {
    var parent = this;
  
    return organism(function() {
      var radius_drift = parent.radius * 0.5;
      var range_drift = parent.range * 0.5;
      var easing_drift = parent.easing * 0.5;
      var reproduction_drift = parent.reproduction * 0.5;
      var death_drift = parent.death * 0.5;
    
      this.x = parent.x
      this.y = parent.y;
      this.color = utils.colorShift(parent.color, 75);
      this.radius = utils.clamp(parent.radius + (Math.random() * radius_drift - radius_drift / 2), 1, 1000);
      this.vx = 0;
      this.vy = 0;
      this.range = utils.clamp(parent.range + (Math.random() * range_drift - range_drift / 2), 10, 1000);
      this.newTarget();
      this.easing = utils.clamp(parent.easing + (Math.random() * easing_drift - easing_drift / 2), 0.001, 0.2);
      this.reproduction = utils.clamp(parent.reproduction + (Math.random() * reproduction_drift - reproduction_drift / 2), 0.00001, 0.003);
      this.death = utils.clamp(parent.death + (Math.random() * death_drift - death_drift / 2), 0.00001, 0.003);
      this.state = "born";
      this.scale_x = this.scale_y = 0.1;
    });
  }
}).mixin({alpha: 0.95});
