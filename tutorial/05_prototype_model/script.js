// // Create the shell
// core.create("shell", "shell");

// // Create agents
// var agent = core.create("spy", "agent");
// agent.blockTalk = true;



// var ddata = core.create("distancesensordata", "distance_data");
// ddata.blockTalk = true;

// var controller = core.create("bjsushcsr04ctrl", "us_controller");
// controller.device = 1;
// controller.blockTalk = true;


// var interface1 = core.create("bjsserialarduino", "arduino_interface");



// controller.co(ddata);
// controller.co(interface1);




// arduino_interface.blockTalk = true;
// arduino_interface.frequency = 60;


// interface1.autoconfig();
// interface1.start();



// agent.co(ddata);


core.create("composer", "compoz");
compoz.visible = true;

// // Show spy
// agent.show();

// // Start shell
// shell.start();


