Basketball Shooting Game 
Introduction
We design a basketball shooting game. The scene consist a simple basketball court with a basketball stand with a hoop on it. The player will move around its view on the court using ASDW and determine the angle for shooting using arrow keys. Then the player will press the SPACEBAR to determine the force it applies to the basketball. The basketball will then follow the physics to move and bounce with other objects ---- basketball stands or other basketballs. If the center of basketball got really close to the center of hoop, the basketball will fall down vertically. We add small bumps on the ground so that the basketball could be bounced to everywhere.

Technical Feature
Bump mapping:
The basketball itself is not a smooth surface, to model the bumped surface, we use Bump Mapping technique. According to http://en.wikipedia.org/wiki/Bump_mapping, it is a technique in computer graphics for simulating bumps and wrinkles on the surface of an object by perturbing the surface normals of the object and using the perturbed normal during lighting calculations. To achieve this, we may either perturb the surface normals randomly or following some patterns consistently.

Collision Detection:
In the basketball shooting game,  the basketball can hit the backboard, the nets and even other balls in the fields. So there will be collisions between the objects. Collision detection typically refers to the computational problem of detecting the intersection of two or more objects. It is a technique to simulate the world more accurately. Collision detection in 3D is many magnitudes more difficult to implement than a simple 2D. There are some basic collision detection algorithms like bounding-sphere\box check or custom point check. But these are computationally expensive if there are many objects. So some advanced collision detection algorithms involved with partition techniques might be used in this project. 

Basic Control:
Mouse Movement: controls the shooting angle
SPACEBAR: controls the power and thus the initial speed of the ball.
ASDW: controls the movement of person
Mouse click: shoot the ball.
Toggle on/off bump mapping: with/without applying bump mapping on the wall.


Design decisions:
  - We directly applied the shape code and cameratrans code, either to draw the sphere/torus or to control/setup the views.
  - We created a basketball class, storing the velocity, position, etc.
  - We also implemented some basic physics in the helper/physics, including momentum theory, and collision detection, in glwidget::processCollision(). In every frame, we'll perform collision detection and then update the velocities and positions of the balls, then draw them. 
  - For bump mapping, in vertex shader we transformed the light direction in object tangent space, and then in the fragment shader we use the normal map to compute the new normal, and the calculations of lights.


