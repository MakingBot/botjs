



class BrainBlock : public BotBlock
{



    void createLoop(const QString& name, QJSValue function, int frequency);
    
    void createEvent(const QString& name, QJSValue condition);
    
    void attachEvent(const QString& name, QJSValue action);


    void log(const QString& message);

};

