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

var lightning = oFactory().share(function(proto) {
  
  function addEndPoint(self, start) {
    var angle = self.min_angle + Math.random() * self.angle_range;
    var length = self.min_length + Math.random() * self.length_range;
    var end = {
      x: start.x + Math.cos(angle) * length,
      y: start.y + Math.sin(angle) * length,
      width: self.reduceWidth(start.width)
    };
    self.end_points.push(end)
    self.segments.push({
      start: start,
      end: end
    });
  }
  
  proto.hasNext = function() {
    return this.end_points.length > 0;
  };
  
  proto.next = function() {
    var self = this;
    var starts = self.end_points;
    self.end_points = [];
    starts.forEach(function(start) {
      if (start.width > 1) {
        addEndPoint(self, start);
        while (Math.random() < self.branching_prob) {
          addEndPoint(self, start);
        }
      }
    });
  };  
  
  proto.draw = function(context) {
    context.save();
    
    context.strokeStyle = this.color;
    context.globalAlpha = this.alpha;
    context.lineCap = "round";
    context.translate(this.x, this.y);
    context.scale(this.scale_x, this.scale_y);
    
    this.segments.forEach(function(s) {
      context.save();
      context.beginPath();
      context.moveTo(s.start.x, s.start.y);
      context.lineWidth = s.start.width;  
      context.lineTo(s.end.x, s.end.y);
      context.stroke();
      context.restore();
    });
    context.restore();
  };
}).mixin({
  color: "#ffffff",
  x: 0,
  y: 0,
  min_length: 60,
  length_range: 40,
  starting_width: 20,
  min_angle: 0,
  segments: [],
  end_points: [],
  alpha: 1,
  angle_range: Math.PI,
  branching_prob: 0.2,
  scale_x: 1,
  scale_y: 1,
  reduceWidth: function(width) {
    return (Math.random() * 0.2 + 0.7) * width;
  }
}).init(function() {
  this.end_points.push({
    y: 0,
    x: 0,
    width: this.starting_width
  })
});
