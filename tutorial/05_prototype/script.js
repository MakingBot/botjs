// Create the shell
core.create("shell", "shell");

// Create agents
core.create("spy", "agent");

// Create the robot
var proteo = core.create("robot", "proteo");



// Create the viewer3D
core.create("viewer3d", "viewer3d");
viewer3d.visible = true;
// viewer3d.logTalking = true;


// Show spy
agent.show();

// Start shell
shell.start();


