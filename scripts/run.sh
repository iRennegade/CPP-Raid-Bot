#/bin/bash
echo -e "\n######## BOT OPTIONS #########\n";
echo "Bot Token -> "
read bot_token
echo "Channel Name -> "
read channel_name
echo "Message -> "
read message_content
export RBOT_TOKEN=$bot_token
export RBOT_MESSAGE=$message_content
export RBOT_CHANNEL_NAME=$channel_name
echo -e "\n"
./../dist/bot