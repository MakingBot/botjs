// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
// agent007.logTalking = true

// Create robot
core.create("robot", "proteo");
var body     = proteo.create("kinasm", "body"    );

var jointBeg = body.create  ("joint" , "jointBeg");

var link     = body.create  ("link"  , "link"    );
link.logTalking = true;

link.translation = [1,2,3];
link.rotation    = [0,90,0];

var jointEnd = body.create  ("joint" , "jointEnd");

core.create  ("link"  , "machin"    );

jointBeg.connect(link);
link.connect(jointEnd);


// Display spies
agent007.show();
agent008.show();

// Start shell
shell.start();
