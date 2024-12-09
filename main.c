#include <concord/discord.h>

static void on_ready(struct discord *client,
                     const struct discord_ready *event) {
  struct discord_application_commands commands;
  discord_get_global_application_commands(
      client, event->application->id,
      &(struct discord_ret_application_commands){
          .sync = &commands,
      });
  for (int i = 0; i != commands.size; ++i) {
    discord_delete_global_application_command(client, event->application->id,
                                              commands.array[i].id, 0);
  }
}

int main(void) {
  struct discord *client = discord_config_init("config.json");
  discord_set_on_ready(client, &on_ready);
  discord_run(client);
}
