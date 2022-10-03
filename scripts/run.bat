@ECHO OFF
echo \n######## BOT OPTIONS #########\n
set /P token=Bot Token: 
set /P channel_name=Channel Name: 
set /P message_content=Message: 
set RBOT_TOKEN=%token%
set RBOT_CHANNEL_NAME=%channel_name%
set RBOT_MESSAGE=%message_content%
start bot.exe