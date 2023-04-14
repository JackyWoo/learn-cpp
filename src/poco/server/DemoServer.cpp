//
// Created by wujianchao5 on 2022/6/18.
//
#include <Poco/util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Task.h>
#include <Poco/TaskManager.h>
#include <Poco/DateTimeFormatter.h>
#include <iostream>
#include <Poco/NumberFormatter.h>


using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Task;
using Poco::TaskManager;
using Poco::DateTimeFormatter;

class SampleTask: public Task
{
public:
    SampleTask(): Task("SampleTask")
    {
    }
	
    void runTask()
    {
        Application& app = Application::instance();
        while (!sleep(5000))
        {
            Application::instance().logger().information("busy doing nothing... " + DateTimeFormatter::format(app.uptime()));
        }
    }
};


class DemoServer: public ServerApplication
{
public:
    DemoServer(): _helpRequested(false)
    {
    }
	
    ~DemoServer()
    {
    }

protected:

    void addSubsystem(Subsystem* pSubsystem)
    {
        Application::addSubsystem(pSubsystem);
    }

    const char* name() const override
    {
        return "DemoServer";
    }

    void initialize(Application& self)
    {
        loadConfiguration(); // load default configuration files, if present
        ServerApplication::initialize(self);
        logger().information("starting up");
    }
		
    void uninitialize()
    {
        logger().information("shutting down");
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options)
    {
        ServerApplication::defineOptions(options);
		
        options.addOption(
            Option("help", "h", "display help information on command line arguments")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<DemoServer>(this, &DemoServer::handleHelp)));

        options.addOption(
            Option("host", "h", "host address")
            .required(true));
    }


    void handleHelp(const std::string& name, const std::string& value)
    {
        _helpRequested = true;
        displayHelp();
        stopOptionsProcessing();
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A sample server application that demonstrates some of the features of the Util::ServerApplication class.");
        helpFormatter.format(std::cout);
    }

    int main(const ArgVec& args)
    {
        std::string sub_cmd = config().getString("application.argv[" + Poco::NumberFormatter::format(1) + "]", "");

        if (sub_cmd == "print")
        {
            /// execute print
        }
        else
        {
            /// execute default command
            if (!_helpRequested)
            {
                TaskManager tm;
                tm.start(new SampleTask);
                waitForTerminationRequest();
                tm.cancelAll();
                tm.joinAll();
            }
        }

        return Application::EXIT_OK;
    }
	
private:
    bool _helpRequested;
};

POCO_SERVER_MAIN(DemoServer)
