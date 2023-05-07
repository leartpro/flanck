

class CMDInterpreterObserver : public virtual InterpreterObserver {
public:

    std::mutex readMutex_;
    std::string read_;
    atomic_bool endReadLoop_;

    void startReadLoop() {
        while(!endReadLoop_) {
            string c;
            getline(std::cin, c);
            reverse(c.begin(), c.end());
            readMutex_.lock();
            read_ = c + read_;
            readMutex_.unlock();
        }
    }

    void start(Interpreter *interpreter) override {
        endReadLoop_ = false;
        std::thread t(&CMDInterpreterObserver::startReadLoop, this);
        t.detach();
    }

    void end(Interpreter *interpreter) override {
        endReadLoop_ = true;
    }


    void inputAsk(Interpreter *interpreter) override {
        if(readMutex_.try_lock()) {
            if(!read_.empty()) {
                auto stack = interpreter->getStack(0);
                auto newStack = Stack::fromString(read_);
                read_ = "";
                newStack.push(stack);
                interpreter->replaceStack(0, newStack);
            }
            readMutex_.unlock();
        }
    }

    void change(Interpreter *interpreter) override {
        if(interpreter->getStackChange().changeMap[1]) {
            std::cout << interpreter->getStackChange().byteAddChangeMap[1].toString();
        }
    }
};

