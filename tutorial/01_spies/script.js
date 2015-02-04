// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
core.create("spy", "agent009");

// Connect spies to robot
agent007.connect(agent008);
agent008.connect(agent009);
agent009.connect(agent007);

// Display spies
agent007.show();
agent008.show();
agent009.show();
