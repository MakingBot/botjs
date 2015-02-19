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
jointOrigine.logTalking = true;

var link1     = body.create  ("link"  , "link1"    );
link1.logTalking = true;


link1.translation = Type.vector3D([1,1,1]);

var jointMiddle = body.create  ("joint" , "jointMiddle");

// var link2     = body.create  ("link"  , "link2"    );

// link2.translation = Type.vector3D([0,1,0]);
// link2.logTalking = true;


/*
var link2     = body.create  ("link"  , "link2"    );
*/
// var jointEnd = body.create  ("joint" , "jointEnd");


jointOrigine.connect(link1);


 link1.connect(jointMiddle);
// jointMiddle.connect(link2);
// link2.connect(jointEnd);




core.create("viewer3d", "viewer3d");
viewer3d.visible = true
viewer3d.logTalking = true;

agent007.connect(viewer3d);

//viewer3d.connect(jointOrigine);
viewer3d.connect(link1);



// Display spies
//agent007.show();
agent008.show();

// Start shell
shell.start();
