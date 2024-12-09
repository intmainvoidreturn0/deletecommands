#include <concord/discord.h>
#include <concord/log.h>

static void on_ready(struct discord *client,
                     const struct discord_ready *event) {
  struct discord_application_commands cmds;
  discord_get_global_application_commands(
      client, event->application->id,
      &(struct discord_ret_application_commands){
          .sync = &cmds,
      });
  for (int i = 0; i != cmds.size; ++i) {
    discord_delete_global_application_command(client, event->application->id,
                                              cmds.array[i].id, 0);
  }
  log_info("completed");
}

int main(void) {
  struct discord *client = discord_config_init("config.json");
  discord_set_on_ready(client, &on_ready);
  discord_run(client);
}
