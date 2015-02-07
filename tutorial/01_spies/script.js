// Enable logging
// core.logTalking = true

// core.create("shell", "agent007");

// Create spies
core.create("spy", "agent007");
core.create("spy", "agent008");
// // core.create("spy", "agent009");

agent007.logTalking = true
agent008.logTalking = true

// Connect spies to robot
agent007.connect(core);
// agent008.connect(agent009);
// agent009.connect(agent007);

// Display spies
agent007.show();
// agent008.show();
// agent009.show();
