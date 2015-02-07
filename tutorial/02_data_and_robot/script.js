// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
// agent007.logTalking = true

// Create robot
core.create("robot" , "proteo");
var body = proteo.create("kinasm", "body"  );
body.create("joint" , "jointBeg");
body.create("link"  , "link" );
body.create("joint" , "jointEnd");


// Display spies
agent007.show();
agent008.show();

// Start shell
shell.start();
