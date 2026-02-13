#include<stdio.h>
#include <concord/discord.h>


const char TOKEN[] = "";

int main() {
    struct discord *client = discord_init(TOKEN);
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES);
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);


    return 0;
}
