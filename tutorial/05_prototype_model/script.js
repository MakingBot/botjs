// Create the shell
core.create("shell", "shell");

// Create agents
//var agent = core.create("spy", "agent");




var ddata = core.create("bjsushcsr04ctrl", "distance_data");


var controller = core.create("bjsushcsr04ctrl", "us_controller");

var interface1 = core.create("bjsserialarduino", "arduino_interface");


var iii = interface1.blockNbSons;

arduino_interface.blockTalk = true;

arduino_interface.frequency = 50;

interface1.autoconfig();
//interface1.start();


// Create the viewer3D
// core.create("viewer3d", "viewer3d");
// viewer3d.visible = true;
// viewer3d.logTalking = true;

// viewer3d.connect(base)



// Show spy
// agent.show();

// Start shell
shell.start();


