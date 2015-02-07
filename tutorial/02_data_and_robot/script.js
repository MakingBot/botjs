// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
// agent007.logTalking = true

// Create robot
core.create("robot" , "proteo");
proteo.create("kinasm", "body"  );
core.create("joint" , "joint1");
core.create("link"  , "link1" );


// Display spies
agent007.show();
agent008.show();

// Start shell
shell.start();
