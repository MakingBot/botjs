// Create shell
core.create("shell", "shell");


core.create("joint", "motor");

// // Create robot
// core.create("robot", "bot");
// bot.name = 'robot test';


// bot.create("bodyasm", "body");


core.create("spy", "agent007");
core.create("spy", "agent008");
core.create("spy", "agent9");

// // Create viewer
core.create("viewer3d", "robot_viewer");
robot_viewer.show();


agent008.connect(agent007);
agent007.connect(motor);
agent9.connect(core);

agent007.show();
agent008.show();
agent9.show();

// Start shell
shell.start();
