#include <iostream>
#include <vector>
#include <thread>
#include <tgbot/tgbot.h>

#include "cmd.hpp"

#define send_msg(x) bot.getApi().sendMessage(msg->chat->id, x)
typedef TgBot::Message::Ptr msg_ptr;

int main() {
  TgBot::Bot bot("TOKEN");

  TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
  std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

  TgBot::InlineKeyboardButton::Ptr memeButton(new TgBot::InlineKeyboardButton);
  memeButton->text = "meme";
  memeButton->callbackData = "meme";

  TgBot::InlineKeyboardButton::Ptr inspireButton(new TgBot::InlineKeyboardButton);
  inspireButton->text = "inspire";
  inspireButton->callbackData = "inspire";

  row0.push_back(memeButton);
  row0.push_back(inspireButton);

  keyboard->inlineKeyboard.push_back(row0);

  bot.getEvents().onCommand("start" ,[&bot, &keyboard](msg_ptr msg) {
    hnd::start(msg, bot, keyboard); 
  });
  bot.getEvents().onCommand("meme" ,[&](msg_ptr msg) { hnd::meme(msg, bot, keyboard); });
  bot.getEvents().onCommand("inspire" ,[&](msg_ptr msg) { hnd::inspire(msg, bot, keyboard); });
  bot.getEvents().onCallbackQuery([&bot, &keyboard](TgBot::CallbackQuery::Ptr query) {
    if (StringTools::startsWith(query->data, "meme"))
      hnd::meme(query->message, bot, keyboard);
    if (StringTools::startsWith(query->data, "inspire"))
      hnd::meme(query->message, bot, keyboard);
  });

  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true)
      longPoll.start();
  } catch (TgBot::TgException& e) {
    printf("error: %s\n", e.what());
  }

  printf("Program exited\n");
  std::cin.get();
  return 0;
}
