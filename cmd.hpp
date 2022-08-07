#pragma once
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <tgbot/tgbot.h>

#include "json.hpp"
#include "HTTPRequest.hpp"

namespace hnd {
  std::string request_get(const char* url);
  void start(TgBot::Message::Ptr, TgBot::Bot&, TgBot::InlineKeyboardMarkup::Ptr&);
  void inspire(TgBot::Message::Ptr, TgBot::Bot&, TgBot::InlineKeyboardMarkup::Ptr&);
  void meme(TgBot::Message::Ptr, TgBot::Bot&, TgBot::InlineKeyboardMarkup::Ptr&);
}

#endif
