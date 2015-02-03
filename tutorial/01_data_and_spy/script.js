// Create shell
block.createBlock("shell", "shell");

// Create robot
block.createBlock("robot", "bot");
bot.name = 'name of the bot';

// Create spies
block.createBlock("spy", "agent007");
block.createBlock("spy", "agent008");
block.createBlock("spy", "agent009");
block.createBlock("spy", "agent010");

// Connect spies to robot
agent007.connect(bot);
agent008.connect(agent007);
agent009.connect(bot);
agent010.connect(agent007);

// Display spies
agent007.show();
agent008.show();
agent009.show();
agent010.show();

// Start shell
shell.start();
