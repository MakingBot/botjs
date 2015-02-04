// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
core.create("spy", "agent009");
core.create("spy", "agent010");

// Connect spies to robot
agent008.connect(agent007);
agent010.connect(agent007);

// Display spies
agent007.show();
agent008.show();
agent009.show();
agent010.show();
