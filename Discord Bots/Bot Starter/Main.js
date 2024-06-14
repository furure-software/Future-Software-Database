var { Bot_Token } = require("./Info.json");
var { Client, Events, GatewayIntentBits, SlashCommandBuilder } = require("discord.js");
var Bot_Client = new Client({intents: [GatewayIntentBits.Guilds]});

Bot_Client.login(Bot_Token);
