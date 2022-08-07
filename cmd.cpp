#include "command_handler.hpp"

namespace hnd {
  std::string request_get(const char* url) {
    try {
      http::Request req{url};
      http::Response response = req.send("GET");
      return std::move(std::string{ response.body.begin(), response.body.end() });
    } catch (const std::exception &e) {
      return std::move(std::string(e.what()));
    }
  }

  void meme(TgBot::Message::Ptr msg, TgBot::Bot &bot) {
    const std::string &res = request_get("https://meme-api.herokuapp.com/gimme");

    nlohmann::json j = nlohmann::json::parse(res);

    const std::string &meme = "\n" + std::string(j["url"]);
    const std::string &title = j["title"];

    bot.getApi().sendMessage(msg->chat->id, title + meme);
  }

  void inspire(TgBot::Message::Ptr msg, TgBot::Bot &bot) {
    const std::string &res = request_get("https://api--quote.herokuapp.com/quote");

    nlohmann::json j = nlohmann::json::parse(res);

    const std::string &quote = j["quote"];
    const std::string &author = "\n    by " + std::string(j["author"]);

    bot.getApi().sendMessage(msg->chat->id, quote + author);
  }

  void start(TgBot::Message::Ptr msg, TgBot::Bot &bot, TgBot::InlineKeyboardMarkup::Ptr &keyboard) {
    const char* docString = R"(
    A utility bot made by pranjal patel

    commands:
    /inspire
      Get an inspirational random quote.

    /meme
      Get a random meme from reddit.
    )";

    bot.getApi().sendMessage(msg->chat->id, docString, "false", 0, keyboard);
  }
}
