var p;

function setup()  {
  createCanvas(windowWidth,windowHeight);
  // Make a new Pendulum with an origin position and armlength
  p = new Pendulum(createVector(width/2,0),217.51*2);
  p2 = new Pendulum(createVector(width/2,0),224.94*2);
  p3 = new Pendulum(createVector(width/2,0),232.76*2);
  p4 = new Pendulum(createVector(width/2,0),241*2);
  p5 = new Pendulum(createVector(width/2,0),249.69*2);
  p6 = new Pendulum(createVector(width/2,0),258.85*2);
  p7 = new Pendulum(createVector(width/2,0),268.53*2);
  p8 = new Pendulum(createVector(width/2,0),278.75*2);
  p9 = new Pendulum(createVector(width/2,0),289.58*2);
  p10 = new Pendulum(createVector(width/2,0),301.05*2);

}

function draw() {
  background(51);
  p.go();
  p2.go();
  p3.go();
  p4.go();
  p5.go();
  p6.go();
  p7.go();
  p8.go();
  p9.go();
  p10.go();
}

function Pendulum(origin_, r_) {
  // Fill all variables
  this.origin = origin_.copy();
  this.position = createVector();
  this.r = r_;
  this.angle = PI/4;

  this.aVelocity = 0.0;
  this.aAcceleration = 0.0;
  this.damping = 1;   // Arbitrary damping
  this.ballr = 40.0;      // Arbitrary ball radius

  this.go = function() {
    this.update();
    this.display();
  };

  // Function to update position
  this.update = function() {
    var gravity = 0.9;                                               // Arbitrary constant
    this.aAcceleration = (-1 * gravity / this.r) * sin(this.angle);  // Calculate acceleration (see: http://www.myphysicslab.com/pendulum1.html)
    this.aVelocity += this.aAcceleration;                            // Increment velocity
    this.aVelocity *= this.damping;                                  // Arbitrary damping
    this.angle += this.aVelocity;                                    // Increment angle
  };

  this.display = function() {
    this.position.set(this.r*sin(this.angle), this.r*cos(this.angle), 0);         // Polar to cartesian conversion
    this.position.add(this.origin);                                               // Make sure the position is relative to the pendulum's origin

    stroke('white');
    strokeWeight(1);
    // Draw the arm
    line(this.origin.x, this.origin.y, this.position.x, this.position.y);
    ellipseMode(CENTER);
    stroke('black');
    strokeWeight(2);
    fill(0,255,0,100);
    // Draw the ball
    ellipse(this.position.x, this.position.y, this.ballr, this.ballr);
  };
}