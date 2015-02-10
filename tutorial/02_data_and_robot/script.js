// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
// agent007.logTalking = true

// Create robot
core.create("robot", "proteo");
var body     = proteo.create("kinasm", "body"    );


var jointOrigine = body.create  ("joint" , "jointOrigine");

var link     = body.create  ("link"  , "link1"    );

var jointBeg = body.create  ("joint" , "jointMiddle");

var link     = body.create  ("link"  , "link2"    );

var jointEnd = body.create  ("joint" , "jointEnd");



jointBeg.connect(link);
link.connect(jointEnd);



core.create("viewer3d", "viewer3d");
viewer3d.visible = true

// Display spies
agent007.show();
agent008.show();

// Start shell
shell.start();
