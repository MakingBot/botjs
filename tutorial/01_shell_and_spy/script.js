// Create the shell
core.create("shell", "shell");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");

agent007.logTalking = true

// Connect spies to robot
agent007.connect(agent008);
agent008.connect(core);

// Display spies
agent007.show();

// Start shell
shell.start();
