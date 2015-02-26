// Create the shell
core.create("shell", "shell");

// Create agents
// core.create("spy", "agent");

// // Create the robot
// var proteo = core.create("robot", "proteo");
// proteo.logTalking = true;

// // Create the leg as a child of the robot
// var leg = proteo.create("kinasm", "leg");
// leg.logTalking = true;

// Create the origine fixe joint
// var base = leg.create("joint", "base");
//var base = core.create("joint", "base");

var interface1 = core.create("bjsserialarduino", "arduino_interface");


var iii = interface1.blockNbSons;

arduino_interface.blockTalk = true;

interface1.doli();

// Create the viewer3D
// core.create("viewer3d", "viewer3d");
// viewer3d.visible = true;
// viewer3d.logTalking = true;

// viewer3d.connect(base)



// Show spy
// agent.show();

// Start shell
shell.start();


