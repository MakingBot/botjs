// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
// agent007.logTalking = true

// Create robot
core.create("robot", "proteo");
core.create("kinasm", "body");
core.create("joint",  "joint1");
core.create("link",   "link1");


// Display spies
agent007.show();

// Start shell
shell.start();
