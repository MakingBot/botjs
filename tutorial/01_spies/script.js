// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");

// Connect spies to robot
agent008.connect(agent007);
agent007.connect(agent008);

// Display spies
agent007.show();
agent008.show();
